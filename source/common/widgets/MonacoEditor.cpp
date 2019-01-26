#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QWebChannel>
#include <QThread>

#include <core/logger/Logging.h>

#include "MonacoEditor.h"

#define CHECK_INIT() \
    if (! m_data->m_initialized) { \
        QZ_ERROR("Cmn:Monaco") << "Attempt to use Editor before it " \
            "is initialized"; \
    }


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
};


MonacoEditor::MonacoEditor(QWidget *parent)
    : QWidget(parent)
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
    CHECK_INIT()
    m_data->m_monaco->page()->runJavaScript(
                "window.editor.setValue(`"+content+"`)");
}

void MonacoEditor::setContentFile(const QString &path)
{
    CHECK_INIT()
    QFile file{path};
    if (file.open(QFile::ReadOnly)) {
        auto content = file.readAll();
        this->setContent(content);
        file.close();
    } else {
        QZ_ERROR("Cmn:Monaco") << "Could not load file at " << path;
    }
}

void MonacoEditor::setLanguage(const QString &language)
{
    CHECK_INIT()
    m_data->m_monaco->page()->runJavaScript(
                "monaco.editor.setModelLanguage("
                    "window.editor.getModel(), "
                "'" + language + "');");
}

void MonacoEditor::setTheme(const QString &theme)
{
    m_data->m_monaco->page()->runJavaScript(
                "monaco.editor.setTheme("
                    "window.editor.getModel(), "
                "'" + theme + "');");
}

void MonacoEditor::set(const QString &method, const QString &value)
{

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
    QZ_INFO("Cmn:Monaco") << msg;
}

}

