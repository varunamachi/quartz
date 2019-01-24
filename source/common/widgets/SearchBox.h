#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

class QString;
class QIcon;

namespace Quartz {

class QUARTZ_COMMON_API SearchBox : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBox(QWidget *parent = nullptr);

    ~SearchBox();

public Q_SLOTS:
    void setButtonIcon(const QIcon &icon);

    void setPlaceholderText(const QString &text);

Q_SIGNALS:
    void textChanged(const QString &text);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
