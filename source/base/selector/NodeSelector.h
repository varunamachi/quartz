#pragma once

#include <memory>

#include "../QuartzBase.h"
#include "AbstractSelector.h"

namespace Quartz {

class Node;

class QUARTZ_BASE_API NodeSelector : public AbstractSelector
{
    Q_OBJECT

public:
    NodeSelector( QWidget *parent = nullptr );

    ~NodeSelector();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

signals:
    void sigNodeSelected( const Node *node );

private slots:
    void onSelected( const QModelIndex &index );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
