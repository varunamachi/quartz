#pragma once

#include <memory>
#include <string>

namespace Vam {

class File
{
public:
    explicit File( const std::string &path );

    bool isDir() const;

    const std::string & path() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};

}

