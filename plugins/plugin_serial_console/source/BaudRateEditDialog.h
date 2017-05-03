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

private slots:
    void add();

    void removeSelected();

signals:
    void baudRateChanged();


private:
    struct Data;
    std::unique_ptr< Data > m_data;
};

} } }
