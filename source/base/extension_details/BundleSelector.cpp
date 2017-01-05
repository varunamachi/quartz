
#include <core/extension_system/AbstractPluginBundle.h>

#include "BundleSelector.h"

namespace Quartz {

struct BundleSelector::Data
{

};

const QString BundleSelector::SELECTOR_ID{ "qz.bundle_selector" };
const QString BundleSelector::SELECTOR_NAME{ "Plugins" };


BundleSelector::BundleSelector( QWidget *parent )
    : AbstractSelector{ SELECTOR_ID, SELECTOR_NAME, parent }
    , m_data{ new Data{ }}
{

}

BundleSelector::~BundleSelector()
{

}

void BundleSelector::onSelected( const QModelIndex &/*index*/ )
{

}



}
