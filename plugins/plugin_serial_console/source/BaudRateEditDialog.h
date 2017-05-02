#pragma once

#include <memory>

#include <QDialog>

namespace Quartz { namespace Plugin { namespace SerialConsole {

class BaudRateEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaudRateEditDialog( QWidget *parent );

    ~BaudRateEditDialog();

signals:
    void baudRateChanged( QStringList rates );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
