#pragma once

#include <memory>

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz {

class Node;
class GeneralNodeTree;
class Context;

class QUARTZ_BASE_API GeneralSelector : public AbstractSelector
{
    Q_OBJECT

public:
    GeneralSelector( QWidget *parent = nullptr );

    ~GeneralSelector();

    GeneralNodeTree * model();

    void selected() override;

    void unselected() override;

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

public Q_SLOTS:
    void setSelected(const QString &nodeID);

Q_SIGNALS:
    void sigNodeSelected( const Node *node );

private Q_SLOTS:
    void onSelected( const QModelIndex &current,
                     const QModelIndex &previous );


private:
    struct Data;
    std::unique_ptr< Data > m_data;

};



}
