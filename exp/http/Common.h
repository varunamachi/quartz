#pragma once

#include <functional>
#include <cstdint>

#include <QHash>

namespace Quartz { namespace Http {

    class MultipartFile;
    using Headers = QHash< QString, QString >;
    using MultipartFiles = QHash<QString, MultipartFile>;
    using ProgFunc = std::function<void( std::size_t prog, std::size_t total)>;
    using Param = QHash< QString, QString >;
} }
