#include <QVBoxLayout>

#include <common/widgets/MonacoEditor.h>

#include "EditorPage.h"

namespace Quartz {

const QString EditorPage::CONTENT_ID("qz.editor");
const QString EditorPage::CONTENT_NAME("Code Editor");
const QString EditorPage::CONTENT_KIND("editor");

EditorPage::EditorPage(QWidget *parent)
    : ContentWidget(CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent)
{
    auto layout = new QVBoxLayout();
    layout->addWidget(new MonacoEditor(this));
    this->setLayout(layout);
}

EditorPage::~EditorPage()
{

}


}
