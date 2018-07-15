#pragma once

#include <memory>

#include <QDialog>

namespace Quartz {

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);

    ~AboutDialog();

private:
//    struct Data;
//    std::unique_ptr<Data> m_data;
};

}
