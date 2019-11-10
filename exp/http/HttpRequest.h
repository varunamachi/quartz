#pragma once

#include <QString>

#include <memory>

#include "Constants.h"
#include "Common.h"

namespace Quartz { namespace Http {

class MultipartFile;

class HttpRequest {
public:
    HttpRequest();

    ~HttpRequest();

    //    const QString &version, Method method, const QString &path

    void setVersion(const QString& version);

    const QString& version() const;

    Method method() const;

    void setMethod(Method method);

    void setPath(const QString& path);

    const QString& path() const;

    ProgFunc progress() const;

    QString header(const QString key) const;

    bool hasHeader(const QString key) const;

    QString param(const QString& key) const;

    bool hasFile(const QString& key) const;

    const MultipartFile* multipartFile(const QString name) const;

    QByteArray& body();

    void setHeader(const QString& key, const QString& value);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
