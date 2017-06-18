#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>


enum HttpRequestVarLayout {NOT_SET, ADDRESS, URL_ENCODED, MULTIPART};

struct HttpRequestInputFileElement
{
    QString m_variableName;
    QString m_localFilename;
    QString m_requestFilename;
    QString m_mimeType;
};


struct HttpRequestInput
{
    QString m_urlStr;

    QString m_httpMethod;

    HttpRequestVarLayout m_varLayout;

    QMap<QString, QString> m_vars;

    QList<HttpRequestInputFileElement> m_files;

    HttpRequestInput();

    HttpRequestInput(QString v_url_str, QString v_http_method);

    void initialize();

    void addVar(QString key, QString value);

    void addFile(QString variable_name,
                  QString local_filename,
                  QString request_filename,
                  QString mime_type);

};

class HttpRequestWorker : public QObject {
    Q_OBJECT
public:
    QByteArray response;

    QNetworkReply::NetworkError m_errorType;

    QString m_errorStr;

    explicit HttpRequestWorker(QObject *parent = 0);

    QString httpAttributeEncode(QString attributeName, QString input);

    void execute(HttpRequestInput *input);

signals:
    void onExecutionFinished(HttpRequestWorker *worker);

private:
    QNetworkAccessManager *manager;

private slots:
    void onManagerFinished(QNetworkReply *reply);

};

