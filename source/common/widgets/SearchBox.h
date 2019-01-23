#pragma once

#include <memory>

#include <QLineEdit>

#include "../QuartzCommon.h"

class QResizeEvent;
class QString;
class QIcon;

namespace Quartz {

class QUARTZ_COMMON_API SearchBox : public QLineEdit
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);

    ~SearchBox();

public slots:
    void setClearImage(const QIcon &icon);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateCloseButton(const QString &text);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
