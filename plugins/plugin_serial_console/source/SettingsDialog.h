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

    void refresh();

    void setSettings( const SerialSettings &settings );

    void open() override;

    int exec() override;

    static void init( QWidget *parent );

public slots:
    void updateBaudRates( QStringList rates );

private slots:
    void showPortDetails();

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};


} } }
