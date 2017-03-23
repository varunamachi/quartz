
#include <QVBoxLayout>

#include "CreatorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

const QString CreatorWidget::CONTENT_ID{ "qzp.creator.content.main" };
const QString CreatorWidget::CONTENT_NAME{ "PluginCreator" };
const QString CreatorWidget::CONTENT_KIND{ "meta" };

CreatorWidget::CreatorWidget(QWidget *parent)
    : ContentWidget( CONTENT_ID, CONTENT_NAME, CONTENT_KIND, parent )
{
    auto layout = new QVBoxLayout{ };
    this->setLayout( layout );
}



} } }
