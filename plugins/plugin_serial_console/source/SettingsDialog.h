#pragma once

#include <memory>

#include <QDialog>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class SerialSettings;

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog( QWidget *parent = nullptr );

    ~SettingsDialog();

    std::unique_ptr< SerialSettings > settings() const;

    void setSettings( std::unique_ptr< SerialSettings > settings );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


} } }
