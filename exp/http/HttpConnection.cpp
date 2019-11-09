

#include "HttpConnection.h"

namespace Quartz { namespace Http {

struct HttpConnection::Data {};

HttpConnection::HttpConnection(QObject* parent)
    : QObject{parent}
    , m_data{new Data{}} {
}

HttpConnection::~HttpConnection() {
}

}} // namespace Quartz::Http
