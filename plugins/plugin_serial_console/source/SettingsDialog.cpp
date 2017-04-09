
#include <QComboBox>

#include "SettingsDialog.h"
#include "SerialSettings.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

struct SettingsDialog::Data
{
    explicit Data( QWidget *parent )
    {

    }


};

SettingsDialog::SettingsDialog( QWidget *parent )
    : QDialog{ parent }
    , m_data{ new Data{ this }}
{

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



} } }
