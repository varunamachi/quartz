#pragma once

#include <memory>

class QString;

namespace Quartz {

class TemplateInstance;

namespace Ext { namespace Creator {

class GenInfo;

class CodeGenerator
{
public:

    CodeGenerator( const GenInfo *info );

    virtual ~CodeGenerator();

    virtual bool generate( const QString &path );

    const QString & lastError() const;

protected:
    virtual bool generateForInstance(
            const QString &path,
            const TemplateInstance *instance );

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
