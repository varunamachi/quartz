#pragma once

#include <functional>
#include <cstdint>

#include <QHash>

namespace Quartz { namespace Http {

    class MultipartFile;
    class HttpRequest;
    class HttpResponse;

    using Headers = QHash< QString, QString >;
    using MultipartFiles = QHash<QString, MultipartFile>;
    using ProgFunc = std::function<void( std::size_t prog, std::size_t total)>;
    using Param = QHash< QString, QString >;
    using Handler = std::function<void(const HttpRequest &, HttpResponse & )>;
} }
