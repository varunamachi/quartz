#pragma once

#include <QWidget>

#include "IQuartzTitleBar.h"
#include "IQuartzActionBar.h"
#include "IQuartzPageManager.h"
#include "IQuartzViewManager.h"


namespace Vam { namespace Quartz {

class QuartzContext
{
public:
    QuartzContext( IQuartzTitleBar &titleBar,
                   IQuartzPageManager &pageManager,
                   IQuartzViewManager &viewManager,
                   IQuartzActionBar &actionBar )
        : m_titleBar( titleBar )
        , m_pageManager( pageManager )
        , m_viewManager( viewManager )
        , m_actionBar( actionBar )
    {

    }

    IQuartzTitleBar & titleBar() const
    {
        return m_titleBar;
    }

    IQuartzPageManager & pageManager() const
    {
        return m_pageManager;
    }

    IQuartzViewManager & viewManager() const
    {
        return m_viewManager;
    }

    IQuartzActionBar & actionBar() const
    {
        return m_actionBar;
    }

private:
    IQuartzTitleBar & m_titleBar;

    IQuartzPageManager & m_pageManager;

    IQuartzViewManager & m_viewManager;

    IQuartzActionBar & m_actionBar;
};

} }
