#pragma once

#include <memory>

#include <base/explorer/AbstractFileHandler.h>

class QFileInfo;

namespace Quartz { namespace Ext { namespace WebTech {

class MonacoEditor;

class SharedObject : public QObject
{
    Q_OBJECT
public:
    SharedObject(MonacoEditor *parent = nullptr);

    ~SharedObject();


public Q_SLOTS:
    void error(const QString &msg);

    void info(const QString &msg);

    void warn(const QString &msg);

    void dirtyChanged(bool val);

    void save();

Q_SIGNALS:
    void saved();

private:
    MonacoEditor *m_editor;
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

    //Settings...
    void setTheme(const QString &theme);

    void showMinimap(bool show);

    void showLineNumber(bool show);

    void setRulerAt(int len);

public Q_SLOTS:
    //Override from AbstractFileHandler
    bool handle(const QString &path) override;

    QString path() const override;

    bool close() override;

    bool save() override;


    static const QStringList & extension();

    static const QString escape(const QString &orig);

private:
    friend SharedObject;

    struct Data;
    std::unique_ptr<Data> m_data;


};

} } }
