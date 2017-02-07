#include "HttpRequestWorker.h"

#include <QDateTime>
#include <QUrl>
#include <QFileInfo>
#include <QBuffer>


HttpRequestInput::HttpRequestInput() {
    initialize();
}

HttpRequestInput::HttpRequestInput(QString v_url_str, QString v_http_method) {
    initialize();
    m_urlStr = v_url_str;
    m_httpMethod = v_http_method;
}

void HttpRequestInput::initialize() {
    m_varLayout = NOT_SET;
    m_urlStr = "";
    m_httpMethod = "GET";
}

void HttpRequestInput::addVar(QString key, QString value) {
    m_vars[key] = value;
}

void HttpRequestInput::addFile( QString variableName,
                                QString localFilename,
                                QString requestFilename,
                                QString mimeType) {
    HttpRequestInputFileElement file;
    file.m_variableName = variableName;
    file.m_localFilename = localFilename;
    file.m_requestFilename = requestFilename;
    file.m_mimeType = mimeType;
    m_files.append(file);
}


HttpRequestWorker::HttpRequestWorker(QObject *parent)
    : QObject(parent)
    , manager(nullptr)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    manager = new QNetworkAccessManager(this);
    connect(manager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(onManagerFinished(QNetworkReply*)));
}

QString HttpRequestWorker::httpAttributeEncode(QString attributeName,
                                               QString input) {
    // result structure follows RFC 5987
    bool needUtfEncoding = false;
    QString result = "";
    QByteArray inputC = input.toLocal8Bit();
    char c;
    for (int i = 0; i < inputC.length(); i++) {
        c = inputC.at(i);
        if (c == '\\' || c == '/' || c == '\0' || c < ' ' || c > '~') {
            // ignore and request utf-8 version
            needUtfEncoding = true;
        }
        else if (c == '"') {
            result += "\\\"";
        }
        else {
            result += c;
        }
    }

    if (result.length() == 0) {
        needUtfEncoding = true;
    }

    if (!needUtfEncoding) {
        // return simple version
        return QString("%1=\"%2\"").arg(attributeName, result);
    }

    QString resultUtf8 = "";
    for (int i = 0; i < inputC.length(); i++) {
        c = inputC.at(i);
        if (
            (c >= '0' && c <= '9')
            || (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
        ) {
            resultUtf8 += c;
        }
        else {
            resultUtf8 += "%" + QString::number(
                        static_cast<unsigned char>(inputC.at(i)), 16).toUpper();
        }
    }
    // return enhanced version with UTF-8 support
    return QString("%1=\"%2\"; %1*=utf-8''%3").arg(attributeName,
                                                   result,
                                                   resultUtf8);
}

void HttpRequestWorker::execute(HttpRequestInput *input)
{
    // reset variables
    QByteArray request_content = "";
    response = "";
    m_errorType = QNetworkReply::NoError;
    m_errorStr = "";

    // decide on the variable layout
    if (input->m_files.length() > 0) {
        input->m_varLayout = MULTIPART;
    }
    if (input->m_varLayout == NOT_SET) {
        input->m_varLayout =
                input->m_httpMethod == "GET"
                || input->m_httpMethod == "HEAD" ? ADDRESS : URL_ENCODED;
    }


    // prepare request content
    QString boundary = "";
    if (input->m_varLayout == ADDRESS || input->m_varLayout == URL_ENCODED) {
        // variable layout is ADDRESS or URL_ENCODED

        if (input->m_vars.count() > 0) {
            bool first = true;
            foreach (QString key, input->m_vars.keys()) {
                if (!first) {
                    request_content.append("&");
                }
                first = false;

                request_content.append(QUrl::toPercentEncoding(key));
                request_content.append("=");
                request_content.append(QUrl::toPercentEncoding(input->m_vars.value(key)));
            }

            if (input->m_varLayout == ADDRESS) {
                input->m_urlStr += "?" + request_content;
                request_content = "";
            }
        }
    }
    else {
        // variable layout is MULTIPART

        boundary = "__-----------------------"
            + QString::number(QDateTime::currentDateTime().toTime_t())
            + QString::number(qrand());
        QString boundary_delimiter = "--";
        QString new_line = "\r\n";

        // add variables
        foreach (QString key, input->m_vars.keys()) {
            // add boundary
            request_content.append(boundary_delimiter);
            request_content.append(boundary);
            request_content.append(new_line);

            // add header
            request_content.append("Content-Disposition: form-data; ");
            request_content.append(httpAttributeEncode("name", key));
            request_content.append(new_line);
            request_content.append("Content-Type: text/plain");
            request_content.append(new_line);

            // add header to body splitter
            request_content.append(new_line);

            // add variable content
            request_content.append(input->m_vars.value(key));
            request_content.append(new_line);
        }

        // add files
        for (QList<HttpRequestInputFileElement>::iterator file_info = input->m_files.begin(); file_info != input->m_files.end(); file_info++) {
            QFileInfo fi(file_info->m_localFilename);

            // ensure necessary variables are available
            if (
                file_info->m_localFilename == NULL || file_info->m_localFilename.isEmpty()
                || file_info->m_variableName == NULL || file_info->m_variableName.isEmpty()
                || !fi.exists() || !fi.isFile() || !fi.isReadable()
            ) {
                // silent abort for the current file
                continue;
            }

            QFile file(file_info->m_localFilename);
            if (!file.open(QIODevice::ReadOnly)) {
                // silent abort for the current file
                continue;
            }

            // ensure filename for the request
            if (file_info->m_requestFilename == NULL || file_info->m_requestFilename.isEmpty()) {
                file_info->m_requestFilename = fi.fileName();
                if (file_info->m_requestFilename.isEmpty()) {
                    file_info->m_requestFilename = "file";
                }
            }

            // add boundary
            request_content.append(boundary_delimiter);
            request_content.append(boundary);
            request_content.append(new_line);

            // add header
            request_content.append(QString("Content-Disposition: form-data; %1; %2").arg(
                httpAttributeEncode("name", file_info->m_variableName),
                httpAttributeEncode("filename", file_info->m_requestFilename)
            ));
            request_content.append(new_line);

            if (file_info->m_mimeType != NULL && !file_info->m_mimeType.isEmpty()) {
                request_content.append("Content-Type: ");
                request_content.append(file_info->m_mimeType);
                request_content.append(new_line);
            }

            request_content.append("Content-Transfer-Encoding: binary");
            request_content.append(new_line);

            // add header to body splitter
            request_content.append(new_line);

            // add file content
            request_content.append(file.readAll());
            request_content.append(new_line);

            file.close();
        }

        // add end of body
        request_content.append(boundary_delimiter);
        request_content.append(boundary);
        request_content.append(boundary_delimiter);
    }


    // prepare connection

    QNetworkRequest request = QNetworkRequest(QUrl(input->m_urlStr));
    request.setRawHeader("User-Agent", "Agent name goes here");

    if (input->m_varLayout == URL_ENCODED) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    }
    else if (input->m_varLayout == MULTIPART) {
        request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + boundary);
    }

    if (input->m_httpMethod == "GET") {
        manager->get(request);
    }
    else if (input->m_httpMethod == "POST") {
        manager->post(request, request_content);
    }
    else if (input->m_httpMethod == "PUT") {
        manager->put(request, request_content);
    }
    else if (input->m_httpMethod == "HEAD") {
        manager->head(request);
    }
    else if (input->m_httpMethod == "DELETE") {
        manager->deleteResource(request);
    }
    else {
        QBuffer buff(&request_content);
        manager->sendCustomRequest(request, input->m_httpMethod.toLatin1(), &buff);
    }

}

void HttpRequestWorker::onManagerFinished(QNetworkReply *reply) {
    m_errorType = reply->error();
    if (m_errorType == QNetworkReply::NoError) {
        response = reply->readAll();
    }
    else {
        m_errorStr = reply->errorString();
    }

    reply->deleteLater();

    emit onExecutionFinished(this);
}
