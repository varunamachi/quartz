
#include <QVBoxLayout>
#include <QTreeView>
#include <QItemSelectionModel>

#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/PluginManager.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "BundleInfoPage.h"
#include "BundleItemModel.h"
#include "BundleSelector.h"


namespace Quartz {

struct BundleSelector::Data
{
    explicit Data( QWidget *parent )
        : m_bundleModel{ new BundleItemModel{ BundleItemModel::NumCols::One,
                                              parent }}
        , m_bundleView{ new QTreeView{ parent }}
        , m_content{ new BundleInfoPage{ parent }}
    {

    }

    BundleItemModel *m_bundleModel;

    QTreeView *m_bundleView;

    BundleInfoPage *m_content;

    QVector< const AbstractPluginBundle *> m_bundles;
};

const QString BundleSelector::SELECTOR_ID{ "qz.bundle_selector" };
const QString BundleSelector::SELECTOR_NAME{ "Plugins" };


BundleSelector::BundleSelector( QWidget *parent )
    : AbstractSelector{ SELECTOR_ID, SELECTOR_NAME, parent }
    , m_data{ new Data{ this }}
{
    auto layout = new QVBoxLayout{ this };
    layout->addWidget( m_data->m_bundleView );
    this->setLayout( layout );

    layout->setContentsMargins( QMargins{} );
    m_data->m_bundleView->setContentsMargins( QMargins{} );
    this->setContentsMargins( QMargins{} );

    appContext()->contentManager()->addContent( m_data->m_content );
    m_data->m_bundles = appContext()->pluginManager()->bundles();
    m_data->m_bundleModel->setBundleList( &m_data->m_bundles );
    m_data->m_bundleView->setModel( m_data->m_bundleModel );
    connect( m_data->m_bundleView->selectionModel(),
             &QItemSelectionModel::currentChanged,
             this,
             &BundleSelector::onSelected );
}

BundleSelector::~BundleSelector()
{
    m_data->m_bundleModel->clear();
}

void BundleSelector::selected()
{
    const auto &selectionModel = m_data->m_bundleView->selectionModel();
    if( selectionModel->hasSelection() ) {
        auto index = selectionModel->currentIndex();
        onSelected( index, QModelIndex{} );
    }
    else {
        if( m_data->m_bundleModel->rowCount( QModelIndex{} ) != 0 ) {
            auto index = m_data->m_bundleModel->index( 0, 0, QModelIndex{} );
            selectionModel->setCurrentIndex(
                        index,
                        QItemSelectionModel::SelectCurrent );
        }
    }
}

void BundleSelector::unselected()
{

}

void BundleSelector::onSelected( const QModelIndex &index,
                                 const QModelIndex &/*previous*/ )
{
    appContext()->contentManager()->selectContent( BundleInfoPage::CONTENT_ID );
    auto bundle = static_cast< AbstractPluginBundle *>(
                index.internalPointer() );
    if( bundle != nullptr ) {
        m_data->m_content->setBundle( bundle );
    }
}



}
