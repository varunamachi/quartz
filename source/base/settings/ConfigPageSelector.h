
#pragma once

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz {

class Node;
class ConfigNodeTree;

class QUARTZ_BASE_API ConfigPageSelector : public AbstractSelector
{
    Q_OBJECT

public:
    ConfigPageSelector( QWidget *parent = nullptr );

    ~ConfigPageSelector();

    ConfigNodeTree * model();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

signals:
    void sigConfigNodeSelected( const Node *node );

private slots:
    void onSelected( const QModelIndex &index );

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

}
