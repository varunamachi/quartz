#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFile>

#include "MonacoEditor.h"


namespace Quartz {

struct MonacoEditor::Data
{
    explicit Data(QWidget *parent)
        : m_monaco(new QWebEngineView(parent))
    {

    }

    QWebEngineView *m_monaco;
};


MonacoEditor::MonacoEditor(QWidget *parent)
    : QWidget(parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_data->m_monaco);
//    m_data->m_monaco->setUrl(QUrl{"qrc:/resources/index.html"});
//    m_data->m_monaco->setHT(QUrl{"qrc:/resources/index.html"});
    QFile file{":/resources/index.html"};
    if (file.open(QFile::ReadOnly)) {
        const QString html = file.readAll();
        m_data->m_monaco->setHtml(html, QUrl("qrc:/resources/"));
    } else {
        m_data->m_monaco->setHtml(tr("<h2>Failed to load index.html</h2>"));
    }
    this->setLayout(layout);
}

MonacoEditor::~MonacoEditor()
{

}

}

