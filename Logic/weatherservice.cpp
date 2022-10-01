#include "weatherservice.h"
#include <QDebug>

WeatherService::WeatherService(QObject *parent) : QObject(parent) {}

WeatherService::WeatherService(std::unique_ptr<IHTTPService> httpService, QObject *parent) :
    QObject(parent)  {

    this->httpService = std::move(httpService);
    connect(this->httpService.get(), &IHTTPService::finished, this, &WeatherService::onReply);
}

void WeatherService::setApiKey(QString key) {
    this->apiKey = key;
}

void WeatherService::setBaseUrl(QString baseUrl) {
    qDebug() << __FUNCTION__ << " " << baseUrl;
    this->baseUrl = baseUrl;
}

void WeatherService::setQueryString(QMap <QString, QString> query) {

    for(auto q : query.keys()) {
        qDebug() << __FUNCTION__ << " "<< q;
    }
    this->query = query;
}

void WeatherService::getWeather()
{
    // get request using http service
    // emits signal reply()
    qDebug() << __FUNCTION__ << " httpService" << (httpService ? "exists" : "is null");
    httpService->setBaseUrl(baseUrl);
    httpService->setQueryString(makeQueryString());
    httpService->get();
}

QStringList WeatherService::makeQueryString() {

    QStringList queryList;

    for(auto &q: query.keys()) {
        queryList<<q + "=" + query.value(q);
    }

    // for debug
    for(auto &q : queryList) {
        qDebug() << __FUNCTION__ << ": " << q;
    }

    return queryList;
}

void WeatherService::onReply(QString replyBody, IHTTPService::ErrorCode errCode)
{
    qDebug()<<__FUNCTION__ << ": got reply: " << replyBody;
    if(errCode == IHTTPService::ErrorCode::OK) {
        emit reply(replyBody);
    } else {
        emit(reply(""));
    }
}
