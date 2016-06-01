
#pragma once

#include <map>
#include <string>
#include <memory>

#include "../Vq.h"

namespace Vq {

class VQ_API Parameters
{
public:
    Parameters();

    explicit Parameters( std::map< std::string, std::string > &params );

    void addParam( const std::string &key, const std::string &value );

    void removeParam( const std::string &key );

    const std::string & param( const std::string &key ) const;

private:
    class Data;
    std::unique_ptr< Data > m_data;




};

}
