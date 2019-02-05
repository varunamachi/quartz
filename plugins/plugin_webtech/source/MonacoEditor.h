#pragma once

#include <memory>

#include <base/explorer/AbstractFileHandler.h>

class QFileInfo;

namespace Quartz { namespace Ext { namespace WebTech {

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

    void setContent(const QString &content, const QString &lang = "txt");

    void setLanguage(const QString &language);

    void setTheme(const QString &theme);

    void setMinimapState(bool show);

    void mapToLanguage(const QFileInfo &info);

    bool handle(const QString &path) override;

    QString path() const override;

    bool close() override;

    bool save() override;

    static const QStringList & extension();

signals:

public slots:

private:
    struct Data;
    std::unique_ptr<Data> m_data;


};

} } }
