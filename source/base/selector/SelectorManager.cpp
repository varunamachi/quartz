#include <QHash>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>

#include <core/logger/Logging.h>

#include <common/widgets/StackedContainer.h>

#include "AbstractSelectorProvider.h"
#include "AbstractSelector.h"
#include "SelectorManager.h"


namespace Quartz {


struct SelectorManager::Data
{
    Data( AbstractContainer *container )
        : m_selectorContainer( container )
    {

    }

    AbstractContainer *m_selectorContainer;

    QHash< QString, AbstractSelector *> m_selectors;

    QVector< AbstractSelector *> m_pluginSelectors;
};


const QString SelectorManager::ADAPTER_NAME{ "quartz.title_bar" };


SelectorManager::SelectorManager( AbstractContainer *container,
                                  QWidget *parent )
    : QWidget( parent )
    , m_data( new Data( container ))

{
    auto layout = new QHBoxLayout{ this };
    layout->addWidget( m_data->m_selectorContainer );
    layout->setContentsMargins( QMargins{ });
    this->setLayout( layout );
}

SelectorManager::~SelectorManager()
{

}

void SelectorManager::addSelector( AbstractSelector *selector )
{
    if( selector != nullptr ) {
        m_data->m_selectorContainer->addWidget( selector->selectorId(),
                                    selector->selectorName(),
                                    selector );
        m_data->m_selectors.insert( selector->selectorId(), selector );
    }
    else {
        QZ_ERROR( "Qz:SelectorManager" ) << "Invalid selector given";
    }
}

void SelectorManager::removeSelector( const QString &selectorId )
{
    AbstractSelector *selector = m_data->m_selectors.value( selectorId );
    if( selector != nullptr ) {
        removeSelector( selectorId );
    }
    else {
        QZ_ERROR( "QzApp:SelectorManager" )
                << "Could not remove selector with id " << selectorId
                << ". No selector with given ID found";
    }
}

void SelectorManager::removeSelector( AbstractSelector *selector )
{
    if( selector != nullptr ) {
            m_data->m_selectorContainer->removeWidget( selector->selectorId() );
            m_data->m_selectors.remove( selector->selectorId() );
            QZ_INFO( "Qz:SelectorManager" )
                    << "succesfully removed selector with id "
                    << selector->selectorId();
    }
    else {
        QZ_ERROR( "Qz:SelectorManager" )
                << "Could not remove selector with id "
                   ". Invalid selector given";
    }
}

AbstractSelector * SelectorManager::selector( const QString &selectorId ) const
{
    AbstractSelector *selector = m_data->m_selectors.value( selectorId );
    return selector;
}

QList< AbstractSelector * > SelectorManager::selectors() const
{
    QList< AbstractSelector *> selectors;
    auto it = m_data->m_selectors.begin();
    for( ; it != m_data->m_selectors.end(); ++ it ) {
        selectors.append( it.value() );
    }
    return selectors;
}

AbstractSelector * SelectorManager::currentSelector() const
{
    QString selectorId = m_data->m_selectorContainer->currentId();
    AbstractSelector *selector = m_data->m_selectors.value( selectorId );
    return selector;
}

void SelectorManager::selectSelector( QString selectorId )
{
    if( m_data->m_selectors.contains( selectorId ) ) {
        m_data->m_selectorContainer->select( selectorId );
    }
    else {
        QZ_ERROR( "Qz:SelectorManager" )
                << "Could not find a selector with id " << selectorId;
    }
}

const QString & SelectorManager::pluginType() const
{
    return AbstractSelectorProvider::PLUGIN_TYPE;
}

const QString & SelectorManager::pluginAdapterName() const
{
    return ADAPTER_NAME;
}

bool SelectorManager::handlePlugin( AbstractPlugin *plugin )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractSelectorProvider *>( plugin );
    if( provider != nullptr ) {
        auto selectors = provider->selectors();
        foreach( auto selector, selectors ) {
            addSelector( selector );
            m_data->m_pluginSelectors.push_back( selector );
        }
        result = true;
    }
    else {
        auto pluginName = plugin != nullptr ? plugin->pluginId()
                                            : "<null>";
        QZ_ERROR( "Qz:SelectorManager" )
                << "Invalid selector plugin provided: " << pluginName;
    }
    return result;
}

bool SelectorManager::finalizePlugins()
{
//    for( int i = 0; i < m_data->m_pluginSelectors.size(); ++ i ) {
//        auto selector = m_data->m_pluginSelectors.at( i );
//        removeSelector( selector);
//    }
    m_data->m_pluginSelectors.clear();
    return true;
}




}
