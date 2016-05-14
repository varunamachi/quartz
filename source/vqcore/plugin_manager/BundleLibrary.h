#pragma once

#include <memory>

class QLibrary;


namespace Vam {

class PluginBundle;

class BundleLibrary
{
public:
    BundleLibrary();

    BundleLibrary( std::unique_ptr< QLibrary > library,
                   std::unique_ptr< PluginBundle > bundle );

    QLibrary * library() const;

    PluginBundle * bundle() const;

    bool isValid() const;

private:
    class Impl;
    std::unique_ptr< Impl > m_impl;


};


}
