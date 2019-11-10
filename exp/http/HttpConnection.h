#pragma once

#include <memory>

#include <QObject>

namespace Quartz { namespace Http {

class HttpConnection : public QObject {
    Q_OBJECT
public:
    explicit HttpConnection(QObject* parent = nullptr);

    ~HttpConnection();

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
