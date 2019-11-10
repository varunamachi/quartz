
#include "Router.h"

namespace Quartz { namespace Http {

struct Router::Data {};

Router::Router()
    : m_data(std::make_unique<Data>()) {
}

Router::~Router() {
}

}} // namespace Quartz::Http
