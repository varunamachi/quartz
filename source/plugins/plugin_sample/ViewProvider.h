#pragma once

#include <base/view_manager/QuartzView.h>

#include <base/view_manager/AbstractViewProvider.h>

namespace Quartz { namespace Plugin { namespace Sample {

class SampleView : public QuartzView {
    Q_OBJECT
public:
    SampleView( QWidget *parent = nullptr );

    ~SampleView();

    static const QString VIEW_ID;

    static const QString VIEW_NAME;

    static const QString VIEW_CATERGORY;

private:

};

class ViewProvider : public AbstractViewProvider
{
public:
    ViewProvider();

    ~ViewProvider();

    bool init() override;

    bool destroy() override;

    QVector< QuartzView *> views() const override;

    static const QString     PLUGIN_ID;

    static const QString     PLUGIN_NAME;

    static const QStringList DEPENDENCIES;

private:

};



} } }
