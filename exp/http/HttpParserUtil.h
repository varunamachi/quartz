#pragma once

#include <memory>

class QByteArray;

namespace Quartz { namespace Http {

class HttpRequest;
class HttpResponse;

class HttpParserUtil
{
public:
    HttpParserUtil() = delete;

    ~HttpParserUtil() = delete;

    static std::unique_ptr<HttpRequest> parseRequest(QByteArray &data);

    static std::unique_ptr<HttpResponse> parseResponse(QByteArray &data);

private:
};

} }
