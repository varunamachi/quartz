
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QSerialPortInfo>
#include <QIntValidator>

#include "SettingsDialog.h"
#include "SerialSettings.h"

//Some information is adapted from Qt's serial terminal example
//Under BSD License - check License.txt in the same directory

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct SettingsDialog::Data
{
    explicit Data( QWidget *parent )
        : m_nameCombo{ new QComboBox{ parent }}
        , m_baudRateCombo{ new QComboBox{ parent }}
        , m_dataBitsCombo{ new QComboBox{ parent }}
        , m_parityCombo{ new QComboBox{ parent }}
        , m_stopBitsCombo{ new QComboBox{ parent }}
        , m_flowControlCombo{ new QComboBox{ parent }}
        , m_desc{ new QLineEdit{ parent }}
        , m_manufacturer{ new QLineEdit{ parent }}
        , m_serialNum{ new QLineEdit{ parent }}
        , m_location{ new QLineEdit{ parent }}
        , m_vid{ new QLineEdit{ parent }}
        , m_pid{ new QLineEdit{ parent }}
        , m_okButton{ new QPushButton{ tr( "Ok" ), parent }}
        , m_cancelButton{ new QPushButton{ tr( "Cancel" ), parent }}
        , m_intValidator{ new QIntValidator{ 0, 40000000, parent }}
    {

    }

    void setupUI();

    QComboBox *m_nameCombo;

    QComboBox *m_baudRateCombo;

    QComboBox *m_dataBitsCombo;

    QComboBox *m_parityCombo;

    QComboBox *m_stopBitsCombo;

    QComboBox *m_flowControlCombo;

    QLineEdit *m_desc;

    QLineEdit *m_manufacturer;

    QLineEdit *m_serialNum;

    QLineEdit *m_location;

    QLineEdit *m_vid;

    QLineEdit *m_pid;

    QPushButton *m_okButton;

    QPushButton *m_cancelButton;

    QIntValidator *m_intValidator;

    QHash< QString, QSerialPortInfo > m_available;
};


SettingsDialog::SettingsDialog( QWidget *parent )
    : QDialog{ parent }
    , m_data{ new Data{ this }}
{
    auto paramLayout = new QGridLayout{};
    auto row = 0;

    paramLayout->addWidget( new QLabel{ tr( "Baud Rate" ), this }, row, 0 );
    paramLayout->addWidget( m_data->m_baudRateCombo, row, 1 );
    ++ row;

    paramLayout->addWidget( new QLabel{ tr( "Data Bits" ), this }, row, 0 );
    paramLayout->addWidget( m_data->m_dataBitsCombo, row, 1 );
    ++ row;

    paramLayout->addWidget( new QLabel{ tr( "Parity" ), this }, row, 0 );
    paramLayout->addWidget( m_data->m_parityCombo, row, 1 );
    ++ row;

    paramLayout->addWidget( new QLabel{ tr( "Stop Bits" ), this }, row, 0 );
    paramLayout->addWidget( m_data->m_stopBitsCombo, row, 1 );
    ++ row;

    paramLayout->addWidget( new QLabel{ tr( "Flow Control" ), this }, row, 0 );
    paramLayout->addWidget( m_data->m_flowControlCombo, row, 1 );
    ++ row;

    auto infoLayout = new QGridLayout{};
    row = 0;

    infoLayout->addWidget( new QLabel{ tr( "Description" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_desc, row, 1 );
    ++ row;

    infoLayout->addWidget( new QLabel{ tr( "Manufacturer" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_manufacturer, row, 1 );
    ++ row;

    infoLayout->addWidget( new QLabel{ tr( "Serial Number" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_serialNum, row, 1 );
    ++ row;

    infoLayout->addWidget( new QLabel{ tr( "Location" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_location, row, 1 );
    ++ row;

    infoLayout->addWidget( new QLabel{ tr( "Vendor ID" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_vid, row, 1 );
    ++ row;

    infoLayout->addWidget( new QLabel{ tr( "Product ID" ), this }, row, 0 );
    infoLayout->addWidget( m_data->m_pid, row, 1 );
    ++ row;

    auto infoGroup = new QGroupBox{ tr( "Device Information"), this };
    infoGroup->setLayout( infoLayout );
    auto paramGroup = new QGroupBox{ tr( "Configuration" ), this };
    paramGroup->setLayout( paramLayout );

    auto groupLayout = new QHBoxLayout{ };
    groupLayout->addWidget( infoGroup );
    groupLayout->addWidget( paramGroup );

    auto btnLayout = new QHBoxLayout{ };
    btnLayout->addStretch();
    btnLayout->addWidget( m_data->m_cancelButton );
    btnLayout->addWidget( m_data->m_okButton );
    m_data->m_okButton->setDefault( true );

    auto mainLayout = new QVBoxLayout{ };
    mainLayout->addWidget( m_data->m_nameCombo );
    mainLayout->addLayout( groupLayout );
    mainLayout->addLayout( btnLayout );

    this->setLayout( mainLayout );
    m_data->setupUI();

    using ComboIdxFunc = void ( QComboBox::* )( int );
    connect( m_data->m_nameCombo,
             SIGNAL( currentIndexChanged( int ) ),
             this,
             SLOT( showPortDetails()));
    connect( m_data->m_okButton,
             &QPushButton::released,
             this,
             &QDialog::accept );
    connect( m_data->m_cancelButton,
             &QPushButton::released,
             this,
             &QDialog::reject );

    connect( m_data->m_baudRateCombo,
            static_cast< ComboIdxFunc >( &QComboBox::currentIndexChanged ),
             [ this ]( int index ) {
        auto isCustomBaudRate = !
                m_data->m_baudRateCombo->itemData( index ).isValid();
        m_data->m_baudRateCombo->setEditable( isCustomBaudRate );
        if( isCustomBaudRate ) {
            m_data->m_baudRateCombo->clearEditText();
            QLineEdit *edit = m_data->m_baudRateCombo->lineEdit();
            edit->setValidator( m_data->m_intValidator );
        }

    });

    connect( m_data->m_nameCombo,
            static_cast< ComboIdxFunc >( &QComboBox::currentIndexChanged ),
             [ this ]( int /*index*/ ) {
        auto custom = ( m_data->m_nameCombo->currentText() == "Custom" );
        m_data->m_nameCombo->setEditable( custom );
        if( custom ) {
            m_data->m_nameCombo->clearEditText();
        }
    });
}

SettingsDialog::~SettingsDialog()
{

}

template< typename T >
T param( QComboBox *box )
{
    return static_cast< T >(
        box->itemData( box->currentIndex() ).toInt() );
}

std::unique_ptr<SerialSettings> SettingsDialog::settings() const
{
    auto brate = param< qint32 >( m_data->m_baudRateCombo );
    if( brate == 0 ) {
        brate = m_data->m_baudRateCombo->currentText().toInt();
    }
    return std::unique_ptr< SerialSettings >( new SerialSettings {
        m_data->m_nameCombo->currentText(),
        brate,
        param< QSerialPort::DataBits >( m_data->m_dataBitsCombo ),
        param< QSerialPort::Parity >( m_data->m_parityCombo ),
        param< QSerialPort::StopBits >( m_data->m_stopBitsCombo ),
        param< QSerialPort::FlowControl >( m_data->m_flowControlCombo ),
        m_data->m_available.value( m_data->m_nameCombo->currentText() )
    });
}

void SettingsDialog::setSettings( std::unique_ptr< SerialSettings > settings )
{

}

void SettingsDialog::open()
{
    refresh();
    QDialog::open();
}

void SettingsDialog::showPortDetails()
{
    auto selected = m_data->m_nameCombo->currentText();
    if( m_data->m_available.contains( selected )) {
        const auto &info = m_data->m_available.value( selected );
        m_data->m_desc->setText( info.description() );
        m_data->m_manufacturer->setText( info.manufacturer() );
        m_data->m_serialNum->setText( info.serialNumber() );
        m_data->m_location->setText( info.systemLocation() );
        m_data->m_vid->setText( QString::number( info.vendorIdentifier() ));
        m_data->m_pid->setText( QString::number( info.productIdentifier() ));
    }
}

void SettingsDialog::refresh()
{
    auto selected = m_data->m_nameCombo->currentText();
    auto selectedIndex = 0;
    m_data->m_available.clear();
    m_data->m_nameCombo->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for( int i = 0; i < ports.size(); ++ i ) {
        const auto &port = ports.at( i );
        if( ! port.isBusy() ) {
            m_data->m_nameCombo->addItem( port.portName() );
            m_data->m_available.insert( port.portName(), port );
            if( port.portName() == selected) {
                selectedIndex = i;
            }
        }
    }
    m_data->m_nameCombo->addItem( "Custom" );
    if( m_data->m_nameCombo->count() != 0 ) {
        m_data->m_nameCombo->setCurrentIndex( selectedIndex );
        showPortDetails();
    }
}

void SettingsDialog::Data::setupUI()
{
    m_baudRateCombo->addItem( QStringLiteral( "9600" ),
                              QSerialPort::Baud9600 );
    m_baudRateCombo->addItem( QStringLiteral( "19200" ),
                              QSerialPort::Baud19200 );
    m_baudRateCombo->addItem( QStringLiteral( "38400" ),
                              QSerialPort::Baud38400 );
    m_baudRateCombo->addItem( QStringLiteral( "115200" ),
                              QSerialPort::Baud115200 );
    m_baudRateCombo->addItem( tr( "Custom" ));

    m_dataBitsCombo->addItem( QStringLiteral( "5" ), QSerialPort::Data5 );
    m_dataBitsCombo->addItem( QStringLiteral( "6" ), QSerialPort::Data6 );
    m_dataBitsCombo->addItem( QStringLiteral( "7" ), QSerialPort::Data7 );
    m_dataBitsCombo->addItem( QStringLiteral( "8" ), QSerialPort::Data8 );
    m_dataBitsCombo->setCurrentIndex(3);

    m_parityCombo->addItem( tr( "None" ), QSerialPort::NoParity );
    m_parityCombo->addItem( tr( "Even" ), QSerialPort::EvenParity );
    m_parityCombo->addItem( tr( "Odd" ), QSerialPort::OddParity );
    m_parityCombo->addItem( tr( "Mark" ), QSerialPort::MarkParity );
    m_parityCombo->addItem( tr( "Space" ), QSerialPort::SpaceParity );

    m_stopBitsCombo->addItem( QStringLiteral( "1" ), QSerialPort::OneStop );
#ifdef Q_OS_WIN
    m_stopBitsCombo->addItem( tr("1.5"), QSerialPort::OneAndHalfStop );
#endif
    m_stopBitsCombo->addItem(QStringLiteral("2"), QSerialPort::TwoStop );

    m_flowControlCombo->addItem( tr("None"), QSerialPort::NoFlowControl );
    m_flowControlCombo->addItem( tr("RTS/CTS"), QSerialPort::HardwareControl );
    m_flowControlCombo->addItem( tr("XON/XOFF"), QSerialPort::SoftwareControl );

    m_desc->setEnabled( false );
    m_manufacturer->setEnabled( false );
    m_serialNum->setEnabled( false );
    m_location->setEnabled( false );
    m_vid->setEnabled( false );
    m_pid->setEnabled( false );
}


} } }
