#pragma once

#include <memory>

#include "AbstractSelector.h"

namespace Quartz {

class NodeSelector : public AbstractSelector
{
public:
    NodeSelector( const QString &selectorId,
                  const QString &selectorName,
                  QWidget *parent = nullptr );

    static const QString SELECTOR_ID;
private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
