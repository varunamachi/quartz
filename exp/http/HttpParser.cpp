
#include <cstring>

#include <QByteArray>

#include <core/logger/Logging.h>

#include "HttpParser.h"
#include "http_parser.h"

namespace Quartz { namespace Http {

static int onMessageBegin(http_parser* /*parser*/) {
    return 0;
}

static int onUrl(http_parser* /*parser*/,
                 const char* /*at*/,
                 size_t /*length*/) {
    return 0;
}

static int onStatus(http_parser* /*parser*/,
                    const char* /*at*/,
                    size_t /*length*/) {
    return 0;
}

static int onHeaderField(http_parser* /*parser*/,
                         const char* /*at*/,
                         size_t /*length*/) {
    return 0;
}

static int onHeaderValue(http_parser* /*parser*/,
                         const char* /*at*/,
                         size_t /*length*/) {
    return 0;
}

static int onHeadersComplete(http_parser* /*parser*/) {
    return 0;
}

static int onBody(http_parser* /*parser*/,
                  const char* /*at*/,
                  size_t /*length*/) {
    return 0;
}

static int onMessageComplete(http_parser* /*parser*/) {
    return 0;
}


bool parse(QByteArray &packet,
    http_parser_type type, 
    void *data)
{
    http_parser parser;
    http_parser_settings settings;
    http_parser_init(&parser, type);
    std::memset(&settings, 0, sizeof(http_parser_settings));
    parser.data = data;
    settings.on_message_begin    = onMessageBegin;
    settings.on_url              = onUrl;
    settings.on_status           = onStatus;
    settings.on_header_field     = onHeaderField;
    settings.on_header_value     = onHeaderValue;
    settings.on_headers_complete = onHeadersComplete;
    settings.on_body             = onBody;
    settings.on_message_complete = onMessageComplete;

    auto res = http_parser_execute(
                &parser,
                &settings,
                packet.data(),
                static_cast<std::size_t>(packet.length())) == 0;
    return res;
}


std::unique_ptr<HttpRequest> HttpParser::parseAsRequest(QByteArray &data)
{
    auto req = std::make_unique<HttpRequest>();
    if (!parse(data, HTTP_REQUEST, req.get())) {
        QZ_ERROR("Qz:Http") << "Failed to parse request";
        return req;
    }
    return nullptr;
}

std::unique_ptr<HttpResponse> HttpParser::parseAsResponse(QByteArray &data)
{
    auto resp = std::make_unique<HttpResponse>();
    if (!parse(data, HTTP_REQUEST, resp.get())) {
        QZ_ERROR("Qz:Http") << "Failed to parse response";
        return resp;
    }
    return nullptr;
}

} }
