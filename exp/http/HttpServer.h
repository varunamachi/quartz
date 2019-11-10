#pragma once

#include <memory>

#include <QObject>

#include "Common.h"

class QString;
class QDir;

namespace Quartz { namespace Http {

class HttpServer : public QObject {
    Q_OBJECT

public:
    explicit HttpServer(QObject* parent = nullptr);

    HttpServer& get(const QString& pattern, Handler handler);

    HttpServer& post(const QString& pattern, Handler handler);

    HttpServer& put(const QString& pattern, Handler handler);

    HttpServer& del(const QString& pattern, Handler handler);

    HttpServer& opt(const QString& pattern, Handler handler);

    void setStaticDir(const QDir& dir);

    void addMiddleware(const QString& patter, Handler handler);

    void setErrorHandler(Handler handler);

    bool start();

    bool stop();

    bool isRunning();

    virtual ~HttpServer();

protected:
    virtual bool handle(const QString& pattern,
                        const HttpRequest& req,
                        HttpResponse& res);

private:
    struct Data;
    std::unique_ptr<Data> m_data;
};

}} // namespace Quartz::Http
