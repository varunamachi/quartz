#include <QVBoxLayout>

#include <common/widgets/MonacoEditor.h>

#include "EditorPage.h"

namespace Quartz {

struct EditorPage::Data
{
    explicit Data(QWidget *parent)
        : m_editor(new MonacoEditor(parent))
    {

    }

    MonacoEditor *m_editor;

};

const QString EditorPage::CONTENT_ID("qz.editor");
const QString EditorPage::CONTENT_NAME("Code Editor");
const QString EditorPage::CONTENT_KIND("editor");

EditorPage::EditorPage(QWidget *parent)
    : ContentWidget(CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent)
    , m_data(std::make_unique<Data>(this))
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_data->m_editor);
    this->setLayout(layout);
}

EditorPage::~EditorPage()
{

}

MonacoEditor * EditorPage::editor() const
{
    return m_data->m_editor;
}


}
