#include "htttqueryservice.h"
#include <QUrl>


HttpQueryService::HttpQueryService(QObject *parent) : IHTTPService(parent)
{
    connect(&networkAccessManager, &QNetworkAccessManager::finished,
            this, &HttpQueryService::onNetworkReply);
}

void HttpQueryService::setQueryString(QStringList queryString)
{
    this->query = queryString;
}

void HttpQueryService::setBaseUrl(QString baseUrl)
{
    this->baseUrl = baseUrl;
}

void HttpQueryService::get()
{
    QString url = baseUrl;

    for(auto &q : query) {
        url += q + "&";
    }
    url.remove(url.size()-1, 1);
    qDebug() << __FUNCTION__ << ": url is: " << url;

    networkRequest.setUrl(QUrl{url});
    networkAccessManager.get(networkRequest);
}

void HttpQueryService::onNetworkReply(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << "Reply error";
        emit IHTTPService::finished("", IHTTPService::ErrorCode::NOT_OK);
        return;
    }

    emit IHTTPService::finished(reply->readAll(), IHTTPService::ErrorCode::OK);
}
