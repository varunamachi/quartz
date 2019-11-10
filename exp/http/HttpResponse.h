#pragma once

#include <memory>

#include "Constants.h"

namespace Quartz { namespace Http {

class HttpResponse {
public:
    HttpResponse(const QString& version, StatusCode status);

    ~HttpResponse();

    const QString& version() const;

    StatusCode status() const;

    QString header(const QString& key) const;

    bool hasHeader(const QString& key) const;

    void setHeader(const QString& key, const QString& value);

    void setRedirect(const QString& url);

    void setContent(const QByteArray& content, const QString& contentType);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
