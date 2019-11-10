

#include "tmpinclude.h"
#include "HttpServer.h"

namespace Quartz { namespace Http {

struct HttpServer::Data {
    socket_t* m_socket;
};

HttpServer::HttpServer(QObject* parent)
    : QObject{parent}
    , m_data{new Data{}} {
}

HttpServer& HttpServer::get(const QString& /*pattern*/,
                            HttpServer::Handler /*handler*/) {
    return *this;
}

HttpServer& HttpServer::post(const QString& /*pattern*/,
                             HttpServer::Handler /*handler*/) {
    return *this;
}

HttpServer& HttpServer::put(const QString& /*pattern*/,
                            HttpServer::Handler /*handler*/) {
    return *this;
}

HttpServer& HttpServer::del(const QString& /*pattern*/,
                            HttpServer::Handler /*handler*/) {
    return *this;
}

HttpServer& HttpServer::opt(const QString& /*pattern*/,
                            HttpServer::Handler /*handler*/) {
    return *this;
}

void HttpServer::setStaticDir(const QDir& /*dir*/) {
}

void HttpServer::addMiddleware(const QString& /*patter*/,
                               HttpServer::Handler /*handler*/) {
}

void HttpServer::setErrorHandler(HttpServer::Handler /*handler*/) {
}

bool HttpServer::start() {
    return false;
}

bool HttpServer::stop() {
    return false;
}

bool HttpServer::isRunning() {
    return false;
}

HttpServer::~HttpServer() {
}

bool HttpServer::handle(const QString& /*pattern*/,
                        const HttpRequest& /*req*/,
                        HttpResponse& /*res*/) {
    return false;
}

}} // namespace Quartz::Http
