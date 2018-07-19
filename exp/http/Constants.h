#pragma once

#include <functional>
#include <cstdint>

#include <QHash>
#include <QString>


namespace Quartz { namespace Http {

enum class StatusCode {
    CONTINUE                                                    = 100,
    SWITCHING_PROTOCOLS                                         = 101,
    PROCESSING                                                  = 102,
    OK                                                          = 200,
    CREATED                                                     = 201,
    ACCEPTED                                                    = 202,
    NON_AUTHORITATIVE_INFORMATION                               = 203,
    NO_CONTENT                                                  = 204,
    RESET_CONTENT                                               = 205,
    PARTIAL_CONTENT                                             = 206,
    MULTI_STATUS                                                = 207,
    ALREADY_REPORTED                                            = 208,
    IM_USED                                                     = 226,
    MULTIPLE_CHOICES                                            = 300,
    MOVED_PERMANENTLY                                           = 301,
    FOUND                                                       = 302,
    SEE_OTHER                                                   = 303,
    NOT_MODIFIED                                                = 304,
    USE_PROXY                                                   = 305,
    TEMPORARY_REDIRECT                                          = 307,
    PERMANENT_REDIRECT                                          = 308,
    BAD_REQUEST                                                 = 400,
    UNAUTHORIZED                                                = 401,
    PAYMENT_REQUIRED                                            = 402,
    FORBIDDEN                                                   = 403,
    NOT_FOUND                                                   = 404,
    METHOD_NOT_ALLOWED                                          = 405,
    NOT_ACCEPTABLE                                              = 406,
    PROXY_AUTHENTICATION_REQUIRED                               = 407,
    REQUEST_TIMEOUT                                             = 408,
    CONFLICT                                                    = 409,
    GONE                                                        = 410,
    LENGTH_REQUIRED                                             = 411,
    PRECONDITION_FAILED                                         = 412,
    PAYLOAD_TOO_LARGE                                           = 413,
    URI_TOO_LONG                                                = 414,
    UNSUPPORTED_MEDIA_TYPE                                      = 415,
    RANGE_NOT_SATISFIABLE                                       = 416,
    EXPECTATION_FAILED                                          = 417,
    MISDIRECTED_REQUEST                                         = 421,
    UNPROCESSABLE_ENTITY                                        = 422,
    LOCKED                                                      = 423,
    FAILED_DEPENDENCY                                           = 424,
    UPGRADE_REQUIRED                                            = 426,
    PRECONDITION_REQUIRED                                       = 428,
    TOO_MANY_REQUESTS                                           = 429,
    REQUEST_HEADER_FIELDS_TOO_LARGE                             = 431,
    UNAVAILABLE_FOR_LEGAL_REASONS                               = 451,
    INTERNAL_SERVER_ERROR                                       = 500,
    NOT_IMPLEMENTED                                             = 501,
    BAD_GATEWAY                                                 = 502,
    SERVICE_UNAVAILABLE                                         = 503,
    GATEWAY_TIMEOUT                                             = 504,
    HTTP_VERSION_NOT_SUPPORTED                                  = 505,
    VARIANT_ALSO_NEGOTIATES                                     = 506,
    INSUFFICIENT_STORAGE                                        = 507,
    LOOP_DETECTED                                               = 508,
    NOT_EXTENDED                                                = 510,
    NETWORK_AUTHENTICATION_REQUIRED                             = 511
};

struct StatusCodeDesc {
    QString m_name;

    QString m_desc;

    const QString & name() const {
        return m_name;
    }

    const QString & description() const {
        return m_desc;
    }
};


const QHash< StatusCode, StatusCodeDesc > STATUS_NAMES =  {
    { 
        StatusCode::CONTINUE, 
        StatusCodeDesc{ "CONTINUE", 
                        "Continue" }
    },
    { 
        StatusCode::SWITCHING_PROTOCOLS, 
        StatusCodeDesc{ "SWITCHING_PROTOCOLS", 
                        "Switching Protocols" }, 
    },
    { 
        StatusCode::PROCESSING, 
        StatusCodeDesc{ "PROCESSING", 
                        "Processing" }, 
    },
    { 
        StatusCode::OK, 
        StatusCodeDesc{ "OK", 
                        "OK" }, 
    },
    { 
        StatusCode::CREATED, 
        StatusCodeDesc{ "CREATED", 
                        "Created" }, 
    },
    { 
        StatusCode::ACCEPTED, 
        StatusCodeDesc{ "ACCEPTED", 
                        "Accepted" }, 
    },
    { 
        StatusCode::NON_AUTHORITATIVE_INFORMATION, 
        StatusCodeDesc{ "NON_AUTHORITATIVE_INFORMATION", 
                        "Non-Authoritative Information" }, 
    },
    { 
        StatusCode::NO_CONTENT, 
        StatusCodeDesc{ "NO_CONTENT", 
                        "No Content" }, 
    },
    { 
        StatusCode::RESET_CONTENT, 
        StatusCodeDesc{ "RESET_CONTENT", 
                        "Reset Content" }, 
    },
    { 
        StatusCode::PARTIAL_CONTENT, 
        StatusCodeDesc{ "PARTIAL_CONTENT", 
                        "Partial Content" }, 
    },
    { 
        StatusCode::MULTI_STATUS, 
        StatusCodeDesc{ "MULTI_STATUS", 
                        "Multi-Status" }, 
    },
    { 
        StatusCode::ALREADY_REPORTED, 
        StatusCodeDesc{ "ALREADY_REPORTED", 
                        "Already Reported" }, 
    },
    { 
        StatusCode::IM_USED, 
        StatusCodeDesc{ "IM_USED", 
                        "IM Used" }, 
    },
    { 
        StatusCode::MULTIPLE_CHOICES, 
        StatusCodeDesc{ "MULTIPLE_CHOICES", 
                        "Multiple Choices" }, 
    },
    { 
        StatusCode::MOVED_PERMANENTLY, 
        StatusCodeDesc{ "MOVED_PERMANENTLY", 
                        "Moved Permanently" }, 
    },
    { 
        StatusCode::FOUND, 
        StatusCodeDesc{ "FOUND", 
                        "Found" }, 
    },
    { 
        StatusCode::SEE_OTHER, 
        StatusCodeDesc{ "SEE_OTHER", 
                        "See Other" }, 
    },
    { 
        StatusCode::NOT_MODIFIED, 
        StatusCodeDesc{ "NOT_MODIFIED", 
                        "Not Modified" }, 
    },
    { 
        StatusCode::USE_PROXY, 
        StatusCodeDesc{ "USE_PROXY", 
                        "Use Proxy" }, 
    },
    { 
        StatusCode::TEMPORARY_REDIRECT, 
        StatusCodeDesc{ "TEMPORARY_REDIRECT", 
                        "Temporary Redirect" }, 
    },
    { 
        StatusCode::PERMANENT_REDIRECT, 
        StatusCodeDesc{ "PERMANENT_REDIRECT", 
                        "Permanent Redirect" }, 
    },
    { 
        StatusCode::BAD_REQUEST, 
        StatusCodeDesc{ "BAD_REQUEST", 
                        "Bad Request" }, 
    },
    { 
        StatusCode::UNAUTHORIZED, 
        StatusCodeDesc{ "UNAUTHORIZED", 
                        "Unauthorized" }, 
    },
    { 
        StatusCode::PAYMENT_REQUIRED, 
        StatusCodeDesc{ "PAYMENT_REQUIRED", 
                        "Payment Required" }, 
    },
    { 
        StatusCode::FORBIDDEN, 
        StatusCodeDesc{ "FORBIDDEN", 
                        "Forbidden" }, 
    },
    { 
        StatusCode::NOT_FOUND, 
        StatusCodeDesc{ "NOT_FOUND", 
                        "Not Found" }, 
    },
    { 
        StatusCode::METHOD_NOT_ALLOWED, 
        StatusCodeDesc{ "METHOD_NOT_ALLOWED", 
                        "Method Not Allowed" }, 
    },
    { 
        StatusCode::NOT_ACCEPTABLE, 
        StatusCodeDesc{ "NOT_ACCEPTABLE", 
                        "Not Acceptable" }, 
    },
    { 
        StatusCode::PROXY_AUTHENTICATION_REQUIRED, 
        StatusCodeDesc{ "PROXY_AUTHENTICATION_REQUIRED", 
                        "Proxy Authentication Required" }, 
    },
    { 
        StatusCode::REQUEST_TIMEOUT, 
        StatusCodeDesc{ "REQUEST_TIMEOUT", 
                        "Request Timeout" }, 
    },
    { 
        StatusCode::CONFLICT, 
        StatusCodeDesc{ "CONFLICT", 
                        "Conflict" }, 
    },
    { 
        StatusCode::GONE, 
        StatusCodeDesc{ "GONE", 
                        "Gone" }, 
    },
    { 
        StatusCode::LENGTH_REQUIRED, 
        StatusCodeDesc{ "LENGTH_REQUIRED", 
                        "Length Required" }, 
    },
    { 
        StatusCode::PRECONDITION_FAILED, 
        StatusCodeDesc{ "PRECONDITION_FAILED", 
                        "Precondition Failed" }, 
    },
    { 
        StatusCode::PAYLOAD_TOO_LARGE, 
        StatusCodeDesc{ "PAYLOAD_TOO_LARGE", 
                        "Payload Too Large" }, 
    },
    { 
        StatusCode::URI_TOO_LONG, 
        StatusCodeDesc{ "URI_TOO_LONG", 
                        "URI Too Long" }, 
    },
    { 
        StatusCode::UNSUPPORTED_MEDIA_TYPE, 
        StatusCodeDesc{ "UNSUPPORTED_MEDIA_TYPE", 
                        "Unsupported Media Type" }, 
    },
    { 
        StatusCode::RANGE_NOT_SATISFIABLE, 
        StatusCodeDesc{ "RANGE_NOT_SATISFIABLE", 
                        "Range Not Satisfiable" }, 
    },
    { 
        StatusCode::EXPECTATION_FAILED, 
        StatusCodeDesc{ "EXPECTATION_FAILED", 
                        "Expectation Failed" }, 
    },
    { 
        StatusCode::MISDIRECTED_REQUEST, 
        StatusCodeDesc{ "MISDIRECTED_REQUEST", 
                        "Misdirected Request" }, 
    },
    { 
        StatusCode::UNPROCESSABLE_ENTITY, 
        StatusCodeDesc{ "UNPROCESSABLE_ENTITY", 
                        "Unprocessable Entity" }, 
    },
    { 
        StatusCode::LOCKED, 
        StatusCodeDesc{ "LOCKED", 
                        "Locked" }, 
    },
    { 
        StatusCode::FAILED_DEPENDENCY, 
        StatusCodeDesc{ "FAILED_DEPENDENCY", 
                        "Failed Dependency" }, 
    },
    { 
        StatusCode::UPGRADE_REQUIRED, 
        StatusCodeDesc{ "UPGRADE_REQUIRED", 
                        "Upgrade Required" }, 
    },
    { 
        StatusCode::PRECONDITION_REQUIRED, 
        StatusCodeDesc{ "PRECONDITION_REQUIRED", 
                        "Precondition Required" }, 
    },
    { 
        StatusCode::TOO_MANY_REQUESTS, 
        StatusCodeDesc{ "TOO_MANY_REQUESTS", 
                        "Too Many Requests" }, 
    },
    { 
        StatusCode::REQUEST_HEADER_FIELDS_TOO_LARGE, 
        StatusCodeDesc{ "REQUEST_HEADER_FIELDS_TOO_LARGE", 
                        "Request Header Fields Too Large" }, 
    },
    { 
        StatusCode::UNAVAILABLE_FOR_LEGAL_REASONS, 
        StatusCodeDesc{ "UNAVAILABLE_FOR_LEGAL_REASONS", 
                        "Unavailable For Legal Reasons" }, 
    },
    { 
        StatusCode::INTERNAL_SERVER_ERROR, 
        StatusCodeDesc{ "INTERNAL_SERVER_ERROR", 
                        "Internal Server Error" }, 
    },
    { 
        StatusCode::NOT_IMPLEMENTED, 
        StatusCodeDesc{ "NOT_IMPLEMENTED", 
                        "Not Implemented" }, 
    },
    { 
        StatusCode::BAD_GATEWAY, 
        StatusCodeDesc{ "BAD_GATEWAY", 
                        "Bad Gateway" }, 
    },
    { 
        StatusCode::SERVICE_UNAVAILABLE, 
        StatusCodeDesc{ "SERVICE_UNAVAILABLE", 
                        "Service Unavailable" }, 
    },
    { 
        StatusCode::GATEWAY_TIMEOUT, 
        StatusCodeDesc{ "GATEWAY_TIMEOUT", 
                        "Gateway Timeout" }, 
    },
    { 
        StatusCode::HTTP_VERSION_NOT_SUPPORTED, 
        StatusCodeDesc{ "HTTP_VERSION_NOT_SUPPORTED", 
                        "HTTP Version Not Supported" }, 
    },
    { 
        StatusCode::VARIANT_ALSO_NEGOTIATES, 
        StatusCodeDesc{ "VARIANT_ALSO_NEGOTIATES", 
                        "Variant Also Negotiates" }, 
    },
    { 
        StatusCode::INSUFFICIENT_STORAGE, 
        StatusCodeDesc{ "INSUFFICIENT_STORAGE", 
                        "Insufficient Storage" }, 
    },
    { 
        StatusCode::LOOP_DETECTED, 
        StatusCodeDesc{ "LOOP_DETECTED", 
                        "Loop Detected" }, 
    },
    { 
        StatusCode::NOT_EXTENDED, 
        StatusCodeDesc{ "NOT_EXTENDED", 
                        "Not Extended" }, 
    },
    {
        StatusCode::NETWORK_AUTHENTICATION_REQUIRED, 
        StatusCodeDesc{ "NETWORK_AUTHENTICATION_REQUIRED", 
                        "Network Authentication Required" }, 
    },
};

enum class Method {
    DELETE,
    GET,
    HEAD,
    POST,
    PUT,
    CONNECT,
    OPTIONS,
    TRACE,
    COPY,
    LOCK,
    MKCOL,
    MOVE,
    PROPFIND,
    PROPPATCH,
    SEARCH,
    UNLOCK,
    BIND,
    REBIND,
    UNBIND,
    ACL,
    REPORT,
    MKACTIVITY,
    CHECKOUT,
    MERGE,
    MSEARCH,
    NOTIFY,
    SUBSCRIBE,
    UNSUBSCRIBE,
    PATCH,
    PURGE,
    MKCALENDAR,
    LINK,
    UNLINK
};

const QHash< Method, QString > METHODS = {
    { Method::DELETE,           "DELETE"     },
    { Method::GET,              "GET"        },
    { Method::HEAD,             "HEAD"       },
    { Method::POST,             "POST"       },
    { Method::PUT,              "PUT"        },
    { Method::CONNECT,          "CONNECT"    },
    { Method::OPTIONS,          "OPTIONS"    },
    { Method::TRACE,            "TRACE"      },
    { Method::COPY,             "COPY"       },
    { Method::LOCK,             "LOCK"       },
    { Method::MKCOL,            "MKCOL"      },
    { Method::MOVE,             "MOVE"       },
    { Method::PROPFIND,         "PROPFIND"   },
    { Method::PROPPATCH,        "PROPPATCH"  },
    { Method::SEARCH,           "SEARCH"     },
    { Method::UNLOCK,           "UNLOCK"     },
    { Method::BIND,             "BIND"       },
    { Method::REBIND,           "REBIND"     },
    { Method::UNBIND,           "UNBIND"     },
    { Method::ACL,              "ACL"        },
    { Method::REPORT,           "REPORT"     },
    { Method::MKACTIVITY,       "MKACTIVITY" },
    { Method::CHECKOUT,         "CHECKOUT"   },
    { Method::MERGE,            "MERGE"      },
    { Method::MSEARCH,          "MSEARCH"    },
    { Method::NOTIFY,           "NOTIFY"     },
    { Method::SUBSCRIBE,        "SUBSCRIBE"  },
    { Method::UNSUBSCRIBE,      "UNSUBSCRIBE"},
    { Method::PATCH,            "PATCH"      },
    { Method::PURGE,            "PURGE"      },
    { Method::MKCALENDAR,       "MKCALENDAR" },
    { Method::LINK,             "LINK"       },
    { Method::UNLINK,           "UNLINK"     }
};

inline uint qHash(Method key, uint seed)
{
    return ::qHash(static_cast<uint>(key), seed);
}

inline uint qHash(StatusCode key, uint seed)
{
    return ::qHash(static_cast<uint>(key), seed);
}

const QString HTTP_VERSION_1_0 = QStringLiteral( "HTTP/1.0" );
const QString HTTP_VERSION_1_1 = QStringLiteral( "HTTP/1.1" );

} }
