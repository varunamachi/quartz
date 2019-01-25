#pragma once

#include <memory>

#include <QWidget>

#include "../QuartzCommon.h"

namespace Quartz {

class QUARTZ_COMMON_API SharedObject : public QObject
{
    Q_OBJECT
public:
    SharedObject(QObject *parent = nullptr);

    ~SharedObject();

public Q_SLOTS:
    void setContent(const QString &content);

Q_SIGNALS:
    void contentSet(const QString &content);
};

class QUARTZ_COMMON_API MonacoEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MonacoEditor(QWidget *parent = nullptr);

    ~MonacoEditor();

    SharedObject * controller() const;

signals:

public slots:

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}
