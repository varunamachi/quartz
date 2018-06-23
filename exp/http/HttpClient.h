#pragma once

#include <memory>

#include <QObject>

#include "Common.h"
#include "Constants.h"

namespace Quartz { namespace Http {

class HttpResponse;
class HttpRequest;

class HttpClient : public QObject {
    Q_OBJECT
public:
    explicit HttpClient( const QString &host,
                         int port,
                         QObject *parent = nullptr );

    virtual ~HttpClient();

    std::shared_ptr<HttpResponse> get(
            const QString &path,
            ProgFunc progress);

    std::shared_ptr<HttpResponse> get(
            const QString &path,
            const Headers &headers,
            ProgFunc progress = nullptr);

    std::shared_ptr<HttpResponse> post(
            const QString &path,
            const QString &body,
            const QString &contentType);

    std::shared_ptr<HttpResponse> post(
            const QString &path,
            const Headers &headers,
            const QString &body,
            const QString &contentType);

    std::shared_ptr<HttpResponse> put(
            const QString &path,
            const QString &body,
            const QString &contentType);

    std::shared_ptr<HttpResponse> put(
            const QString &path,
            const Headers &headers,
            const QString &body,
            const QString &contentType);

    std::shared_ptr<HttpResponse> del(
            const QString &path,
            ProgFunc progress);

    std::shared_ptr<HttpResponse> perform(
            Method method,
            const HttpRequest &req,
            const HttpResponse &resp);

private:
    struct Data;
    std::unique_ptr< Data > m_data;

};

} }
