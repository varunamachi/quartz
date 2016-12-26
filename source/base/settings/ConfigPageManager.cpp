
#include <QHash>

#include "ConfigPageManager.h"


namespace Quartz {

struct ConfigPageManager::Data
{
//    QHash< QString,
};

ConfigPageManager::ConfigPageManager( const QString &id,
                                      const QString &name,
                                      const QString &kind,
                                      QWidget *parent )
    : ContentWidget{ id, name, kind, parent }
{

}

ConfigPageManager::~ConfigPageManager()
{

}

}
