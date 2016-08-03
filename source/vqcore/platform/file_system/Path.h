#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../common/Result.h"

namespace Vq {

class Path
{
public:
    Path();

    Path( const std::vector< std::string > &components, bool absolute );

    Path( const std::vector< std::string > &&components, bool absolute );

    Path( const Path &other );

    Path( Path &&other );

    ~Path();

    Path & operator = ( const Path &other );

    Path & operator = ( Path &&other );

    bool operator == ( const Path &other ) const;

    bool operator == ( const std::string &strPath ) const;

    bool operator != ( const Path &other ) const;

    bool operator != ( const std::string strPath ) const;

    std::string toString() const;

    std::string fileName() const;

    std::string extension() const;

    std::string baseName() const;

    bool isValid() const;

    bool isAbsolute() const;

    const std::vector< std::string > & components() const;

    const std::vector< std::string > & components();

    Path & append( const std::string &relative );

    Path parent() const;

    Result< Path & > mergeWith( const Path &other );

    Result< Path > relativeTo( const Path & other );

    static Result< Path > create( const std::string &strPath );

    const static std::string SEPERATOR;

private:
    std::vector< std::string > mutableComponents();

    void assign( std::vector< std::string > && comp, bool isAbs );

    static Result< std::vector< std::string >> parse(
            const std::string &strPath );

    class Data;
    std::unique_ptr< Data > m_data;
};


}
