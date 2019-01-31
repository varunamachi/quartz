#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QWebChannel>
#include <QThread>
#include <QFileInfo>
#include <QQueue>

#include <plugin_base/PluginLogging.h>

#include "MonacoEditor.h"


#define EXEC(statement)                                                 \
    if (!m_data->m_initialized) {                                       \
        m_data->m_pendingCommands.append([=]() {                        \
            m_data->m_monaco->page()->runJavaScript(statement);         \
        });                                                             \
    } else {                                                            \
        m_data->m_monaco->page()->runJavaScript(statement);             \
    }                                                                   \

namespace Quartz {

struct MonacoEditor::Data
{
    explicit Data(QWidget *parent)
        : m_monaco(new QWebEngineView(parent))
        , m_qzwrapper(new SharedObject(parent))
        , m_initialized(false)
    {
        auto channel = new QWebChannel(parent);
        m_monaco->page()->setWebChannel(channel);
        channel->registerObject(QStringLiteral("qzwrapper"), m_qzwrapper);
    }

    QWebEngineView *m_monaco;

    SharedObject *m_qzwrapper;

    bool m_initialized;

    QFile m_file;

    QQueue<std::function<void()>> m_pendingCommands;
};


MonacoEditor::MonacoEditor(QWidget *parent)
    : AbstractFileHandler(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_data->m_monaco);
    QFile file{":/resources/index.html"};
    if (file.open(QFile::ReadOnly)) {
        const QString html = file.readAll();
        m_data->m_monaco->setHtml(html, QUrl("qrc:/resources/"));
        file.close();

    } else {
        m_data->m_monaco->setHtml(tr("<h2>Failed to load index.html</h2>"));
    }

    this->setLayout(layout);

    connect(m_data->m_monaco,
            &QWebEngineView::loadFinished,
            [this]() {
        m_data->m_initialized = true;
        while (!m_data->m_pendingCommands.empty()) {
            auto func = m_data->m_pendingCommands.takeFirst();
            func();
        }
    });
}

MonacoEditor::~MonacoEditor()
{

}

SharedObject *MonacoEditor::controller() const
{
    return  m_data->m_qzwrapper;
}

void MonacoEditor::setContent(const QString &content)
{
    EXEC(
        "if (window.editor) {"
            "window.editor.setValue(`"+content+"`);"
         "}"
    );
}

void MonacoEditor::setLanguage(const QString &language)
{
    EXEC(
        "if (window.editor) {"
            " monaco.editor.setModelLanguage("
                "window.editor.getModel(), "
                "`" + language + "`);"
        "}"
    );
}

void MonacoEditor::setTheme(const QString &theme)
{
    EXEC(
        "if (window.editor) {"
            " monaco.editor.setTheme("
                "window.editor.getModel(), "
                "`" + theme + "`);"
        "}"
    );
}

bool MonacoEditor::handle(QFile &file)
{
    auto result = false;
    if (QFileInfo(file).isFile() && file.open(QFile::ReadOnly)) {
        auto content = file.readAll();
        this->setContent(content);
        file.close();
        result = true;
    } else {
        QZP_ERROR << "Could not load file at " << file.fileName();
    }
    return result;
}

bool MonacoEditor::close()
{
    auto result = true;
    if (m_data->m_file.isOpen()) {
        m_data->m_file.close();
        result = !m_data->m_file.isOpen();
        if (!result) {
            QFileInfo info{m_data->m_file};
            QZP_ERROR << "Failed to close file " << info.path();
        }
    }
    return result;
}

bool MonacoEditor::save()
{
    return false;
}



SharedObject::SharedObject(QObject *parent)
    : QObject (parent)
{

}

SharedObject::~SharedObject()
{

}

void SharedObject::print(const QString &msg)
{
    QZP_INFO << msg;
}

}

