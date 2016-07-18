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

//    explicit Path( const std::vector< std::string > &components );

    Path( const Path &other );

    Path( Path &&other );

    ~Path();

    Path & operator = ( const Path &other );

    Path & operator = ( Path &&other );

    bool operator == ( Path &other );

    std::string toString() const;

    const std::string & fileName() const;

    const std::string & extension() const;

    const std::string & baseName() const;

    std::vector< std::string > components();

    void append( const std::string &relative );

    Path parent() const;

    const static std::string SEPERATOR;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};


}
