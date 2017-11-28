#pragma once

#include <memory>

class QString;
class QStringList;
class QVariant;

namespace Quartz {

class TemplateInstance;

namespace Plugin { namespace Creator {

class GenInfo
{
public:
    GenInfo( const QString &id,
             const QString &name,
             const QString &display,
             const QString &nmspace );

    ~GenInfo();

    const QString & id() const;

    const QString & name() const;

    const QString & display() const;

    const QString & ns() const;

    const QStringList & files() const;

    int numTemplateInstances() const;

    const TemplateInstance * templateInstanceAt( int i ) const;

    void addTemplateInstance( TemplateInstance *inst );

    void removeTemplateInstance( const QString &instanceName );

private:
    struct Data;
    std::unique_ptr< Data > m_data;


};

} } }
