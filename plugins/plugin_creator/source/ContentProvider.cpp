#include "ContentProvider.h"
#include "CreatorWidget.h"

namespace Quartz { namespace Plugin { namespace Creator {

/********************** Provider ************************************/
const QString ContentProvider::PLUGIN_ID{
    "qzp.creator.provider.content" };
const QString ContentProvider::PLUGIN_NAME{
    "Quartz Creator Content" };

struct ContentProvider::Data
{
    explicit Data( std::shared_ptr< TemplateManager > tman )
    {
        m_widgets.push_back( new CreatorWidget{ tman } );
    }

    QVector< ContentWidget *> m_widgets;
};

ContentProvider::ContentProvider( std::shared_ptr< TemplateManager > tman  )
    : AbstractContentProvider{ PLUGIN_ID, PLUGIN_NAME }
    , m_data{ new Data{ tman }}
{

}

ContentProvider::~ContentProvider()
{

}

bool ContentProvider::init()
{
    return true;
}

bool ContentProvider::destroy()
{
    return true;
}

QVector< ContentWidget *> ContentProvider::widgets()
{
    return m_data->m_widgets;
}



} } }
