#pragma once

#include <memory>

#include <base/explorer/AbstractFileHandler.h>

namespace Quartz {

class SharedObject : public QObject
{
    Q_OBJECT
public:
    SharedObject(QObject *parent = nullptr);

    ~SharedObject();


public Q_SLOTS:
    void print(const QString &msg);

Q_SIGNALS:
};

class MonacoEditor : public AbstractFileHandler
{
    Q_OBJECT
public:
    explicit MonacoEditor(QWidget *parent = nullptr);

    ~MonacoEditor() override;

    SharedObject * controller() const;

    void setContent(const QString &content);

    void setLanguage(const QString &language);

    void setTheme(const QString &theme);

    bool handle(QFile &file) override;

    bool close() override;

    bool save() override;

signals:

public slots:

private:
    struct Data;
    std::unique_ptr<Data> m_data;


};

}
