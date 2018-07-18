#pragma once

#include <memory>

class QByteArray;

namespace Quartz { namespace Http {

class HttpRequest;
class HttpResponse;

class HttpParser
{
public:
    enum Type {
        ParseRequest,
        ParseResponse,
        ParseBoth,
    };

    explicit HttpParser(Type type);

    ~HttpParser();

    std::unique_ptr<HttpRequest> parseRequest(QByteArray &data);

    std::unique_ptr<HttpResponse> parserResponse(QByteArray &data);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

} }
