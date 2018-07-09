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

    QVector< AbstractSelector *> m_extensionSelectors;
};


const QString SelectorManager::ADAPTER_NAME{ "qz.title_bar" };


SelectorManager::SelectorManager( AbstractContainer *container,
                                  QWidget *parent )
    : QWidget( parent )
    , m_data( new Data( container ))

{
    auto layout = new QHBoxLayout{ this };
    layout->addWidget( m_data->m_selectorContainer );
    layout->setContentsMargins( 4, 1, 4, 1 );
    this->setLayout( layout );
    //Only string style connect works on Windows
    connect( m_data->m_selectorContainer,
             SIGNAL( sigSelected( const QString &, QWidget *) ),
             this,
             SLOT( onSelectorSelected( const QString &, QWidget * )));
//    using SigFunc = void ( AbstractContainer::*)( const QString &, QWidget *);
//    auto sig = static_cast< SigFunc >( &AbstractContainer::sigSelected );
//    connect( m_data->m_selectorContainer,
//             sig,
//             this,
//             &SelectorManager::onSelectorSelected );
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
//        auto selector = m_data->m_selectors.value( selectorId );
        m_data->m_selectorContainer->select( selectorId );
    }
    else {
        QZ_ERROR( "Qz:SelectorManager" )
                << "Could not find a selector with id " << selectorId;
    }
}

const QString & SelectorManager::extensionType() const
{
    return AbstractSelectorProvider::EXTENSION_TYPE;
}

const QString & SelectorManager::extensionAdapterName() const
{
    return ADAPTER_NAME;
}

bool SelectorManager::handleExtension( Ext::Extension *extension )
{
    auto result = false;
    auto provider = dynamic_cast< AbstractSelectorProvider *>( extension );
    if( provider != nullptr ) {
        auto selectors = provider->selectors();
        foreach( auto selector, selectors ) {
            addSelector( selector );
            m_data->m_extensionSelectors.push_back( selector );
        }
        result = true;
    }
    else {
        auto extensionName = extension != nullptr ? extension->extensionId()
                                            : "<null>";
        QZ_ERROR( "Qz:SelectorManager" )
                << "Invalid selector extension provided: " << extensionName;
    }
    return result;
}

bool SelectorManager::finalizeExtension()
{
    m_data->m_extensionSelectors.clear();
    return true;
}

void SelectorManager::onSelectorSelected( const QString &selectorId,
                                          QWidget */*widget*/ )
{
    auto selector = m_data->m_selectors.value( selectorId,
                                               nullptr );
    if( selector != nullptr ) {
        selector->selected();
    }
}

}
