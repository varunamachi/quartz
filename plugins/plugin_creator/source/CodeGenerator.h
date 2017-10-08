#pragma once

#include <memory>

class QString;

namespace Quartz { namespace Plugin { namespace Creator {

class GenInfo;

class CodeGenerator
{
public:

    CodeGenerator( const GenInfo *info );

    ~CodeGenerator();

    bool generate(const QString &path );

    const QString & lastError() const;

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} } }
