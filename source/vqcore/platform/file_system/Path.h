#pragma once

#include <memory>

namespace Vam {

class Path
{
public:
    explicit Path( const std::string path );

    std::string toString() const;

    const std::string & fileName() const;

    const std::string & extension() const;

    const std::string & baseName() const;

    bool exists() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;
};


}
