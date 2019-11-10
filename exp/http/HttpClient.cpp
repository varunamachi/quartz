
#include "HttpClient.h"

namespace Quartz { namespace Http {

struct HttpClient::Data {
    QString m_host;

    int m_port;
};

HttpClient::HttpClient(const QString& host, int port, QObject* parent)
    : QObject{parent}
    , m_data{new Data{host, port}} {
}

HttpClient::~HttpClient() {
}

std::shared_ptr<HttpResponse> HttpClient::get(const QString& /*path*/,
                                              ProgFunc /*progress*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::get(const QString& /*path*/,
                                              const Headers& /*headers*/,
                                              ProgFunc /*progress*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::post(const QString& /*path*/,
                                               const QString& /*body*/,
                                               const QString& /*contentType*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::post(const QString& /*path*/,
                                               const Headers& /*headers*/,
                                               const QString& /*body*/,
                                               const QString& /*contentType*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::put(const QString& /*path*/,
                                              const QString& /*body*/,
                                              const QString& /*contentType*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::put(const QString& /*path*/,
                                              const Headers& /*headers*/,
                                              const QString& /*body*/,
                                              const QString& /*contentType*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::del(const QString& /*path*/,
                                              ProgFunc /*progress*/) {
    return nullptr;
}

std::shared_ptr<HttpResponse> HttpClient::perform(
    Method /*method*/,
    const HttpRequest& /*req*/,
    const HttpResponse& /*resp*/) {
    return nullptr;
}

}} // namespace Quartz::Http
