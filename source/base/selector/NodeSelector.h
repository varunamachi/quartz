#pragma once

#include <memory>

#include "AbstractSelector.h"

namespace Quartz {



class NodeSelector : public AbstractSelector
{
    Q_OBJECT

public:
    NodeSelector( QWidget *parent = nullptr );

    ~NodeSelector();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

private:
//    struct Data;
//    std::unique_ptr< Data > m_data;

    void setupLayout();
};



}
