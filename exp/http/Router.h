#pragma once

#include <memory>

#include "Common.h"

class QString;

namespace Quartz { namespace Http {

class Router {

public:
    explicit Router();

    ~Router();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
