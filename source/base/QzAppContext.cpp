#include <QStandardPaths>

#include <core/logger/Logger.h>
#include <base/content_manager/ContentManager.h>
#include <base/selector/SelectorManager.h>
#include <base/general_selector/GeneralSelector.h>
#include <base/settings/ConfigPageManager.h>
#include <base/theme/ThemeManager.h>

#include "QzAppContext.h"


namespace Quartz {

struct QzAppContext::Data
{
    ContentManager *m_contentManager;

    SelectorManager *m_selectorManager;

    GeneralSelector *m_nodeSelector;

    ConfigPageManager *m_configPageManager;

    ThemeManager *m_themeManager;
};

QzAppContext::QzAppContext()
//    : m_data( std::make_unique< Data >{ })
    : m_data( new Data{ })
{

}

QzAppContext::~QzAppContext()
{

}

QString QzAppContext::expand( StdPath pathID )
{
    //version?
    switch( pathID ) {
    case StdPath::DataDirectory: {
        return QStandardPaths::writableLocation(
                    QStandardPaths::AppDataLocation ) + "/.quartz/";
    }
    case StdPath::LogDirectory: {
        auto path = QStandardPaths::writableLocation(
                    QStandardPaths::AppDataLocation );
        return path + "/.quartz/logs";
    }
    }
    return QStandardPaths::writableLocation( QStandardPaths::AppDataLocation );
}

QZCONTEXT_FUNC_DEFINE( QzAppContext, ContentManager, contentManager );
QZCONTEXT_FUNC_DEFINE( QzAppContext, SelectorManager, selectorManager );
QZCONTEXT_FUNC_DEFINE( QzAppContext, GeneralSelector, nodeSelector );
QZCONTEXT_FUNC_DEFINE( QzAppContext, ConfigPageManager, configPageManager );
QZCONTEXT_FUNC_DEFINE( QzAppContext, ThemeManager, themeManager );

}
