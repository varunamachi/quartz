#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../common/Result.h"

namespace Vq {

class Path
{
public:
    explicit Path( const std::string &path );

    Path( const Path &other );

    Path( Path &&other );

    ~Path();

    Path & operator = ( const Path &other );

    Path & operator = ( Path &&other );

    bool operator == ( const Path &other ) const;

    bool operator == ( const std::string &strPath ) const;

    std::string toString() const;

    std::string fileName() const;

    std::string extension() const;

    std::string baseName() const;

    const std::vector< std::string > & components() const;

    void append( const std::string &relative );

    Path parent() const;

    const static std::string SEPERATOR;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};


}
