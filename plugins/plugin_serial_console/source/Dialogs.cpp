
#include <QObject>

#include "Dialogs.h"
#include "SerialSettings.h"
#include "SettingsDialog.h"
#include "BaudRateEditDialog.h"

namespace Quartz { namespace Plugin { namespace SerialConsole {

std::unique_ptr< Dialogs > Dialogs::s_instance{ nullptr };

struct Dialogs::Data
{
    Data( QWidget *parent )
        : m_settingsDialog{ new SettingsDialog{ parent }}
        , m_rateEditorDialog{ new BaudRateEditDialog{ parent }}
    {

    }

    SettingsDialog *m_settingsDialog;

    BaudRateEditDialog *m_rateEditorDialog;

};

void Dialogs::init( QWidget *parent )
{
    //No thread saftey, assuming we are getting this call from main thread
    //since we are getting a QWidget object
    if( s_instance == nullptr ) {
        s_instance = std::unique_ptr< Dialogs >{ new Dialogs{ parent }};
    }
}

void Dialogs::destroy()
{
    s_instance.release();
}

SerialSettingsPtr Dialogs::openSettings()
{
    auto code = s_instance->m_data->m_settingsDialog->exec();
    if( code == QDialog::Accepted ) {
        return s_instance->m_data->m_settingsDialog->settings();
    }
    return nullptr;
}

SerialSettingsPtr Dialogs::openSettings( const SerialSettings &inSettings )
{
    auto dialog = s_instance->m_data->m_settingsDialog;
    dialog->setSettings( inSettings );
    auto code = dialog->exec();
    if( code == QDialog::Accepted ) {
        return dialog->settings();
    }
    return nullptr;
}

void Dialogs::openBaudRateEditor()
{
    s_instance->m_data->m_rateEditorDialog->exec();
}

BaudRateEditDialog * Dialogs::baudRateEditDialog()
{
    return s_instance->m_data->m_rateEditorDialog;
}

Dialogs::~Dialogs()
{

}

Dialogs::Dialogs( QWidget *parent )
    : m_data{ new Data{ parent }}
{
    QObject::connect( m_data->m_rateEditorDialog,
                      &BaudRateEditDialog::baudRateChanged,
                      m_data->m_settingsDialog,
                      &SettingsDialog::updateBaudRates );
}



} } }
