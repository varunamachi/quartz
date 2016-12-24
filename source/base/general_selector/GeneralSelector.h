#pragma once

#include <memory>

#include "../QuartzBase.h"
#include "../selector/AbstractSelector.h"

namespace Quartz {

class Node;
class SelectionTree;
class Context;

class QUARTZ_BASE_API GeneralSelector : public AbstractSelector
{
    Q_OBJECT

public:
    GeneralSelector( const QzAppContext *context,
                  QWidget *parent = nullptr );

    ~GeneralSelector();

    SelectionTree * model();

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
