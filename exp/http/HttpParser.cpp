
#include <cstring>

#include "HttpParser.h"
#include "http_parser.h"

namespace Quartz { namespace Http {

static int onMessageBegin(http_parser* /*p*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onUrl(http_parser* /*p*/, const char* /*at*/, size_t /*length*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onStatus(http_parser* /*p*/, const char* /*at*/, size_t /*length*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onHeaderField(http_parser* /*p*/,
                         const char* /*at*/,
                         size_t /*length*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onHeaderValue(http_parser* /*p*/,
                         const char* /*at*/,
                         size_t /*length*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onHeadersComplete(http_parser* /*p*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onBody(http_parser* /*p*/, const char* /*at*/, size_t /*length*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}

static int onMessageComplete(http_parser* /*p*/) {
    //    auto data = static_cast<HttpParser *>(p->data);
    return 0;
}


struct HttpParser::Data {
    http_parser m_impl;

    http_parser_settings m_settings;

};

HttpParser::HttpParser(Type type)
{
    m_data->m_impl.data  = this;
    http_parser_init(&m_data->m_impl,
                     static_cast<http_parser_type>(type));

    std::memset(&m_data->m_settings, 0, sizeof(http_parser_settings));
    m_data->m_settings.on_message_begin    = onMessageBegin;
    m_data->m_settings.on_url              = onUrl;
    m_data->m_settings.on_status           = onStatus;
    m_data->m_settings.on_header_field     = onHeaderField;
    m_data->m_settings.on_header_value     = onHeaderValue;
    m_data->m_settings.on_headers_complete = onHeadersComplete;
    m_data->m_settings.on_body             = onBody;
    m_data->m_settings.on_message_complete = onMessageComplete;

}

HttpParser::~HttpParser()
{

}

std::unique_ptr<HttpRequest> HttpParser::parseRequest(QByteArray &/*data*/)
{
    return nullptr;
}

std::unique_ptr<HttpResponse> HttpParser::parserResponse(QByteArray &/*data*/)
{
    return nullptr;
}



} }
