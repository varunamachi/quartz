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
    void print(const QString &msg);

Q_SIGNALS:
};

class QUARTZ_COMMON_API MonacoEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MonacoEditor(QWidget *parent = nullptr);

    ~MonacoEditor();

    SharedObject * controller() const;

    void setContent(const QString &content);

    void setContentFile(const QString &path);

    void setLanguage(const QString &language);

    void setTheme(const QString &theme);

signals:

public slots:

private:
    void set(const QString &method, const QString &value);

    struct Data;
    std::unique_ptr<Data> m_data;
};

}
