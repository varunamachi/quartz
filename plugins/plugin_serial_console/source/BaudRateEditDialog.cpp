
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

#include "BaudRateEditDialog.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct BaudRateEditDialog::Data
{
    explicit Data( QWidget *parent )
        : m_standardRates{ new QListWidget{ parent }}
        , m_customRates{ new QListWidget{ parent }}
        , m_addButton{ new QPushButton{ tr( "Add" ), parent }}
        , m_removeButton{ new QPushButton{ tr( "Remove" ), parent }}
        , m_clearButton{ new QPushButton{ tr( "Clear" ), parent }}
        , m_addField{ new QLineEdit{ parent }}
        , m_okButton{ new QPushButton{ tr( "Ok" ), parent }}
    {
        m_addField->setValidator( new QIntValidator{ parent });
    }

    QListWidget *m_standardRates;

    QListWidget *m_customRates;

    QPushButton *m_addButton;

    QPushButton *m_removeButton;

    QPushButton *m_clearButton;

    QLineEdit *m_addField;

    QPushButton *m_okButton;
};

BaudRateEditDialog::BaudRateEditDialog( QWidget *parent )
    : QDialog{ parent }
    , m_data{ new Data{ this }}
{
    auto stdLayout = new QVBoxLayout{  };
    stdLayout->addWidget( m_data->m_standardRates );
    auto stdGroup = new QGroupBox{ tr("Standard buad rates"), this };
    stdGroup->setLayout( stdLayout );

    auto cstLayout = new QGridLayout{  };
    cstLayout->addWidget( m_data->m_addField, 0, 0 );
    cstLayout->addWidget( m_data->m_addButton, 0, 1 );
    cstLayout->addWidget( m_data->m_customRates, 1, 0, 2, 1 );
    cstLayout->addWidget( m_data->m_removeButton, 1, 1 );
    cstLayout->addWidget( m_data->m_clearButton, 2, 1 );
    m_data->m_customRates->setMinimumSize( QSize{ 100, 100 });
    auto cstGroup = new QGroupBox{ tr( "Custom baud rates" ), this };
    cstGroup->setLayout( cstLayout );

    auto btnLayout = new QHBoxLayout{  };
    btnLayout->addStretch();
    btnLayout->addWidget( m_data->m_okButton );

    auto layout = new QVBoxLayout{  };
    layout->addWidget( cstGroup );
    layout->addWidget( stdGroup );
    layout->addLayout( btnLayout );

    this->setLayout( layout );

    connect( m_data->m_okButton,
             &QPushButton::released,
             this,
             &QDialog::accept );
}

BaudRateEditDialog::~BaudRateEditDialog()
{

}

void BaudRateEditDialog::persist()
{

}


} } }
