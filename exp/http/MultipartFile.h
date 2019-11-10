#pragma once

#include <memory>

#include <QString>

namespace Quartz { namespace Http {

class MultipartFile {
public:
    explicit MultipartFile(const QString& fileName,
                           const QString& contentType,
                           std::size_t offset = 0,
                           std::size_t length = 0);

    ~MultipartFile();

    const QString& fileName() const;

    const QString& contentType() const;

    std::size_t offset() const;

    std::size_t length() const;

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
