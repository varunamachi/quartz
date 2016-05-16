#pragma once

#include <string>

namespace Vam {

class Constants {
public:
    Constants() = delete;
    Constants( Constants &other ) = delete;
    Constants & operator=( Constants &other ) = delete;

    static const std::string EMPTY_STRING;

};

}
