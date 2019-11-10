
#include <cstring>

#include <QByteArray>

#include <core/logger/Logging.h>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "http_parser.h"
#include "HttpParserUtil.h"

namespace Quartz { namespace Http {

struct Accumulator {
    QByteArray m_headerName;

    QByteArray m_headerValue;

    QHash<QByteArray, QByteArray> m_headers;

    QByteArray m_url;

    QByteArray m_body;

    Method m_method;

    QString m_version;

    QString m_remoteAddr;

    QString m_remotePort;
};

static int onMessageBegin(http_parser* /*parser*/) {
    return 0;
}

static int onUrl(http_parser* parser, const char* at, std::size_t length) {
    auto acc = static_cast<Accumulator*>(parser->data);
    acc->m_url.append(at, static_cast<int>(length));
    return 0;
}

static int onStatus(http_parser* parser, const char* at, size_t length) {
    auto acc = static_cast<Accumulator*>(parser->data);
    return 0;
}

static int onHeaderField(http_parser* parser,
                         const char* /*at*/,
                         size_t /*length*/) {
    auto acc = static_cast<Accumulator*>(parser->data);
    if (!acc->m_headerName.isEmpty() && !acc->m_headerValue.isEmpty()) {
        // header names are always lower-cased
        acc->m_headers.insert(acc->m_headerName.toLower(),
                              acc->m_headerValue.toLower());
        acc->m_headerName.clear();
        acc->m_headerValue.clear();
    }
    return 0;
}

static int onHeaderValue(http_parser* parser, const char* at, size_t length) {
    auto acc = static_cast<Accumulator*>(parser->data);
    acc->m_headerValue.append(at, static_cast<int>(length));
    return 0;
}

static int onHeadersComplete(http_parser* parser) {
    auto acc = static_cast<Accumulator*>(parser->data);
    return 0;
}

static int onBody(http_parser* parser, const char* /*at*/, size_t /*length*/) {
    auto acc = static_cast<Accumulator*>(parser->data);
    return 0;
}

static int onMessageComplete(http_parser* parser) {
    auto acc = static_cast<Accumulator*>(parser->data);
    return 0;
}

bool parse(QByteArray& packet, http_parser_type type, void* data) {
    http_parser parser;
    http_parser_settings settings;
    http_parser_init(&parser, type);
    std::memset(&settings, 0, sizeof(http_parser_settings));
    parser.data = data;
    settings.on_message_begin = onMessageBegin;
    settings.on_url = onUrl;
    settings.on_status = onStatus;
    settings.on_header_field = onHeaderField;
    settings.on_header_value = onHeaderValue;
    settings.on_headers_complete = onHeadersComplete;
    settings.on_body = onBody;
    settings.on_message_complete = onMessageComplete;

    auto res = http_parser_execute(&parser,
                                   &settings,
                                   packet.data(),
                                   static_cast<std::size_t>(packet.length()))
        == 0;
    return res;
}

std::unique_ptr<HttpRequest> HttpParserUtil::parseRequest(QByteArray& data) {
    std::unique_ptr<HttpRequest> req;
    Accumulator acc;
    if (parse(data, HTTP_REQUEST, &acc)) {
        req = std::make_unique<HttpRequest>();
        // populate request from accumulator
    } else {
        QZ_ERROR("Qz:Http") << "Failed to parse request";
    }
    return req;
}

std::unique_ptr<HttpResponse> HttpParserUtil::parseResponse(QByteArray& data) {
    std::unique_ptr<HttpResponse> resp;
    Accumulator acc;
    if (parse(data, HTTP_REQUEST, &acc)) {
        resp = std::make_unique<HttpResponse>();
        // populate response from accumulator
    } else {
        QZ_ERROR("Qz:Http") << "Failed to parse response";
    }
    return resp;
}

}} // namespace Quartz::Http
