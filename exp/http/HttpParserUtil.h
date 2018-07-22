#pragma once

#include <memory>

#include "Constants.h"

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

    static Method toMethod(const QString &meth);

private:
};

} }
