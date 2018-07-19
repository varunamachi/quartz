#pragma once

#include <memory>

class QByteArray;

namespace Quartz { namespace Http {

class HttpRequest;
class HttpResponse;

class HttpParser
{
public:
    HttpParser() = delete;

    ~HttpParser() = delete;

    static std::unique_ptr<HttpRequest> parseAsRequest(QByteArray &data);

    static std::unique_ptr<HttpResponse> parseAsResponse(QByteArray &data);

private:
};

} }
