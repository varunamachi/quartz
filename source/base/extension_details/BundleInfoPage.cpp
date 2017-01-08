
#include <QVBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLibrary>

#include <core/extension_system/AbstractPluginBundle.h>
#include <core/extension_system/PluginManager.h>


#include "../QzAppContext.h"
#include "BundleItemModel.h"
#include "PluginItemModel.h"
#include "AdapterItemModel.h"
#include "BundleInfoPage.h"

namespace Quartz {

struct BundleInfoPage::Data
{
    Data( QWidget *parent )
        : m_bundle{ nullptr }
        , m_pluginModel{ new PluginItemModel{ parent }}
        , m_adapterModel{ new AdapterItemModel{ parent }}
        , m_bundleModel{ new BundleItemModel{ BundleItemModel::NumCols::Two,
                                              parent }}
        , m_pluginView{ new QTreeView{ parent }}
        , m_adapterView{new QTreeView{ parent }}
        , m_dependencyView{ new QTreeView{ parent }}
        , m_bundleId{ new QLineEdit{ parent }}
        , m_bundleName{ new QLineEdit{ parent }}
        , m_libName{ new QLineEdit{ parent }}
    {
        m_pluginView->setModel( m_pluginModel );
        m_adapterView->setModel( m_adapterModel );
        m_dependencyView->setModel( m_bundleModel );
        m_pluginView->setRootIsDecorated( false );
        m_adapterView->setRootIsDecorated( false );
        m_dependencyView->setRootIsDecorated( false );
        m_pluginView->setContentsMargins( QMargins{} );
        m_dependencyView->setContentsMargins( QMargins{} );

        m_bundleName->setEnabled( false );
        m_bundleId->setEnabled( false );
        m_libName->setEnabled( false );
    }

    const AbstractPluginBundle *m_bundle;

    PluginItemModel *m_pluginModel;

    AdapterItemModel *m_adapterModel;

    BundleItemModel *m_bundleModel;

    QTreeView *m_pluginView;

    QTreeView *m_adapterView;

    QTreeView *m_dependencyView;

    QLineEdit *m_bundleId;

    QLineEdit *m_bundleName;

    QLineEdit *m_libName;

    QVector< const AbstractPluginBundle *> m_deps;
};

const QString BundleInfoPage::CONTENT_ID{ "qz.bundlepage" };
const QString BundleInfoPage::CONTENT_NAME{ "Plugin Details" };
const QString BundleInfoPage::CONTENT_KIND{ "qz.info" };

BundleInfoPage::BundleInfoPage( QWidget *parent )
    : ContentWidget{ CONTENT_ID,
                     CONTENT_NAME,
                     CONTENT_KIND,
                     parent }
    , m_data{ new Data{ this }}
{

    auto infoLayout = new QGridLayout{};
    infoLayout->addWidget( new QLabel{ tr( "Bundle Name"), this }, 0, 0);
    infoLayout->addWidget( m_data->m_bundleName, 0, 1 );
    infoLayout->addWidget( new QLabel{ tr( "Bundle Id"), this }, 1, 0);
    infoLayout->addWidget( m_data->m_bundleId, 1, 1 );
    infoLayout->addWidget( new QLabel{ tr( "Bundle Library"), this }, 2, 0);
    infoLayout->addWidget( m_data->m_libName, 2, 1 );
    infoLayout->setContentsMargins( QMargins{} );

    auto hlyt = new QHBoxLayout{};
    hlyt->addWidget( m_data->m_adapterView );
    hlyt->addWidget( m_data->m_dependencyView );
    hlyt->setContentsMargins( QMargins{} );

    auto layout = new QVBoxLayout{};
    layout->addLayout( infoLayout );
    layout->addWidget( m_data->m_pluginView );
    layout->addLayout( hlyt );
    layout->setContentsMargins( QMargins{} );
    this->setLayout( layout );
    this->setContentsMargins( QMargins{} );
}

BundleInfoPage::~BundleInfoPage()
{

}

void BundleInfoPage::setBundle( const AbstractPluginBundle *bundle )
{
    if( bundle == nullptr ) {
        return;
    }
    auto lib = appContext()->pluginManager()->libraryForBundle(
                bundle->bundleId() );
    m_data->m_bundleId->setText( bundle->bundleId() );
    m_data->m_bundleName->setText( bundle->bundleName() );
    m_data->m_libName->setText( lib != nullptr ? lib->fileName() : "NA");
    m_data->m_bundle = bundle;
    m_data->m_deps.clear();
    const auto &depIds = bundle->dependencies();
    for( int i = 0; i < depIds.size(); ++ i ) {
        auto dep = appContext()->pluginManager()->bundle(
                    depIds.at( i ).first );
        if( dep != nullptr ) {
            m_data->m_deps.push_back( dep );
        }
    }
    m_data->m_pluginModel->setPluginList( &bundle->plugins() );
    m_data->m_adapterModel->setAdapterList( &bundle->adapters() );
    m_data->m_bundleModel->setBundleList( &m_data->m_deps );
}



}

