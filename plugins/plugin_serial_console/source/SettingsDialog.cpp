
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

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
    paramLayout->addWidget( m_data->m_dataBitsCombo, row, 1 );
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

    auto mainLayout = new QVBoxLayout{ };
    mainLayout->addWidget( m_data->m_nameCombo );
    mainLayout->addLayout( infoLayout );
    mainLayout->addLayout( paramLayout );
    this->setLayout( mainLayout );
}

SettingsDialog::~SettingsDialog()
{

}

std::unique_ptr<SerialSettings> SettingsDialog::settings() const
{
    return nullptr;
}

void SettingsDialog::setSettings( std::unique_ptr< SerialSettings > settings )
{

}

void SettingsDialog::refresh()
{

}

void SettingsDialog::Data::setupUI()
{
    m_baudRateCombo->addItem( QStringLiteral( "9600" ),
                              QSerialPort::Baud9600);
    m_baudRateCombo->addItem( QStringLiteral( "19200" ),
                              QSerialPort::Baud19200);
    m_baudRateCombo->addItem( QStringLiteral( "38400" ),
                              QSerialPort::Baud38400);
    m_baudRateCombo->addItem( QStringLiteral( "115200" ),
                              QSerialPort::Baud115200 );
    m_baudRateCombo->addItem( tr("Custom"));

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
