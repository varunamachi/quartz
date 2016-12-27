
#include <QHash>
#include <QVBoxLayout>
#include <QStackedLayout>

#include "AbstractConfigPage.h"
#include "ConfigPageManager.h"


namespace Quartz {

struct ConfigPageManager::Data
{
    explicit Data( QWidget *parent )
        : m_layout{ new QStackedLayout{ parent }}
    {

    }

    QHash< QString, AbstractConfigPage *> m_pages;

    QStackedLayout *m_layout;
};

ConfigPageManager::ConfigPageManager( const QString &id,
                                      const QString &name,
                                      const QString &kind,
                                      QWidget *parent )
    : ContentWidget{ id, name, kind, parent }
{
    auto layout = new QVBoxLayout();
    layout->addLayout( m_data->m_layout );
    layout->setContentsMargins( QMargins{ });
    m_data->m_layout->setContentsMargins( QMargins{ });
    this->setLayout( layout );
}

ConfigPageManager::~ConfigPageManager()
{

}


bool ConfigPageManager::addPage( AbstractConfigPage *page )
{
    bool result = false;
    if( page != nullptr ) {
        m_data->m_pages.insert( page->configPageId(), page );
        auto index = m_data->m_layout->addWidget( page );
        m_data->m_layout->setCurrentIndex( index );
        result = true;
    }
    return result;
}

bool ConfigPageManager::removePage( const QString &pageId )
{
    bool result = false;
    auto page = m_data->m_pages.value( pageId );
    if( page != nullptr ) {
        if( m_data->m_layout->currentWidget() == page
                && m_data->m_layout->count() > 0 ) {
                m_data->m_layout->setCurrentIndex( 0 );
        }
        m_data->m_pages.remove( pageId );
        m_data->m_layout->removeWidget( page );
        result = true;
    }
    return result;
}

AbstractConfigPage * ConfigPageManager::page( const QString &pageId )
{
    AbstractConfigPage * widget = m_data->m_pages.value( pageId, nullptr );
    return widget;
}

void ConfigPageManager::selectPage( const QString &pageId )
{
    auto widget = m_data->m_pages.value( pageId );
    if( widget != nullptr ) {
        m_data->m_layout->setCurrentWidget( widget );
    }
}

}
