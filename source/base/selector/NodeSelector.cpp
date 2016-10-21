
#include <QVBoxLayout>

#include "NodeSelector.h"
#include "Node.h"

namespace Quartz {

const QString NodeSelector::SELECTOR_ID{ "quartz.node_selector" };
const QString NodeSelector::SELECTOR_NAME{ "Pages" };


NodeSelector::NodeSelector( QWidget *parent )
    : AbstractSelector( SELECTOR_ID,
                        SELECTOR_NAME,
                        parent )
{

}

NodeSelector::~NodeSelector()
{

}

void NodeSelector::setupLayout()
{

}

}
