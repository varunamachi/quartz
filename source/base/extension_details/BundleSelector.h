#pragma once

#include "../selector/AbstractSelector.h"

namespace Quartz {

class AbstractPluginBundle;

class BundleSelector : public AbstractSelector
{
    Q_OBJECT

public:
    explicit BundleSelector( QWidget *parent = nullptr );

    ~BundleSelector();

    static const QString SELECTOR_ID;

    static const QString SELECTOR_NAME;

Q_SIGNALS:
    void sigBundleSelected( AbstractPluginBundle *bundle );

private Q_SLOTS:
    void onSelected( const QModelIndex &index );

private:
    struct Data;
    std::unique_ptr< Data > m_data;
};




}
