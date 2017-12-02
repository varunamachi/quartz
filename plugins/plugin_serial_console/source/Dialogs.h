#pragma once

#include <memory>

class QWidget;

namespace Quartz { namespace Ext { namespace SerialConsole {

class BaudRateEditDialog;
class SerialSettings;
using SerialSettingsPtr = std::unique_ptr< SerialSettings >;


class Dialogs
{
public:

    static void init( QWidget *parent );

    static void destroy();

    static SerialSettingsPtr openSettings();

    static SerialSettingsPtr openSettings( const SerialSettings &inSettings );

    static void openBaudRateEditor();

    static BaudRateEditDialog * baudRateEditDialog();

    ~Dialogs();


private:
    Dialogs( QWidget *parent );

    static std::unique_ptr< Dialogs > s_instance;

    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
