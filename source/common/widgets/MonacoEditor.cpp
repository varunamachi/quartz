#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>
#include <QWebChannel>

#include "MonacoEditor.h"


namespace Quartz {

struct MonacoEditor::Data
{
    explicit Data(QWidget *parent)
        : m_monaco(new QWebEngineView(parent))
        , m_qzwrapper(new SharedObject(parent))
    {
        auto channel = new QWebChannel(parent);
        m_monaco->page()->setWebChannel(channel);
        channel->registerObject(QStringLiteral("qzwrapper"), m_qzwrapper);
    }

    QWebEngineView *m_monaco;

    SharedObject *m_qzwrapper;
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
        m_data->m_qzwrapper->contentSet(
            "function x() {console.log('hello!');}");
    } else {
        m_data->m_monaco->setHtml(tr("<h2>Failed to load index.html</h2>"));
    }
    this->setLayout(layout);
}

MonacoEditor::~MonacoEditor()
{

}

SharedObject *MonacoEditor::controller() const
{
    return  m_data->m_qzwrapper;
}

SharedObject::SharedObject(QObject *parent)
    : QObject (parent)
{

}

SharedObject::~SharedObject()
{

}

void SharedObject::setContent(const QString &content)
{
    emit contentSet(content);
}

}

