
#include <QVBoxLayout>
#include <QTreeView>
#include <QHeaderView>

#include <common/matfont/MaterialFont.h>

#include "../QzAppContext.h"
#include "../content_manager/ContentManager.h"
#include "../selector/Node.h"
#include "GeneralNodeTree.h"
#include "GeneralSelector.h"

namespace Quartz {

const QString GeneralSelector::SELECTOR_ID{ "qz.node_selector" };
const QString GeneralSelector::SELECTOR_NAME{ "Pages" };


struct GeneralSelector::Data
{
    explicit Data( QTreeView *treeView,
                   GeneralNodeTree *model )
        : m_view( treeView )
        , m_model( model )
    {

    }

    QTreeView *m_view;

    GeneralNodeTree *m_model;
};

GeneralSelector::GeneralSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        matIcon(MatIcon::BlurCircular),
                        parent )
//    , m_data( std::make_unique< Data >( new QTreeView( this )))
    , m_data( new GeneralSelector::Data( new QTreeView( this ),
                                         new GeneralNodeTree( this )))
{
    auto layout = new QVBoxLayout();
    //deligate
    m_data->m_view->setModel( m_data->m_model );
    m_data->m_view->header()->setVisible( false );
    m_data->m_view->setSelectionMode( QAbstractItemView::SingleSelection );
    m_data->m_view->setSelectionBehavior( QAbstractItemView::SelectRows );
    layout->addWidget( m_data->m_view );
    this->setLayout( layout );
    connect( m_data->m_view->selectionModel(),
             &QItemSelectionModel::currentChanged,
             this,
             &GeneralSelector::onSelected );
    this->setContentsMargins( QMargins{ });
    m_data->m_view->setContentsMargins( QMargins{ });
    layout->setContentsMargins( QMargins{ });
}

GeneralSelector::~GeneralSelector()
{

}

GeneralNodeTree *GeneralSelector::model()
{
    return m_data->m_model;
}

void GeneralSelector::selected()
{
    const auto &selectionModel = m_data->m_view->selectionModel();
    if( selectionModel->hasSelection() ) {
        auto index = selectionModel->currentIndex();
        onSelected( index, QModelIndex{} );
    }
    else {
        if( m_data->m_model->rowCount( QModelIndex{} ) != 0 ) {
            auto index = m_data->m_model->index( 0, 0, QModelIndex{} );
            selectionModel->setCurrentIndex(
                        index,
                        QItemSelectionModel::SelectCurrent);
        }
    }
}

void GeneralSelector::unselected()
{

}

void GeneralSelector::onSelected( const QModelIndex &current,
                                  const QModelIndex &/*previous*/ )
{
    if( ! ( current.isValid() && current.internalPointer() != nullptr )) {
        return;
    }
    auto node = static_cast< Node *>( current.internalPointer() );
    if( appContext()->hasContentManager() ) {
        appContext()->contentManager()->selectContent( node->nodeId() );
    }
    emit sigNodeSelected( node );
}

}
