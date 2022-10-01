#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H

#include <memory>

#include <QObject>
#include <QMap>

#include "ihttpservice.h"

/** @brief Provides Weather getting service */
class WeatherService : public QObject
{
    Q_OBJECT
public:
    explicit WeatherService(QObject *parent=nullptr);
    explicit WeatherService(std::unique_ptr <IHTTPService> httpService, QObject *parent=nullptr);
    virtual ~WeatherService(){}
    virtual void setApiKey(QString key);
    virtual void setBaseUrl(QString baseUrl);
    virtual void setQueryString(QMap <QString, QString> query);
    virtual void getWeather();

signals:
    void reply(QString reply);

private slots:
    void onReply(QString replyBody, IHTTPService::ErrorCode);

private:
    QStringList makeQueryString();

protected:
    std::unique_ptr<IHTTPService> httpService;
    QString apiKey;
    QString baseUrl;
    QMap <QString, QString>query;
};

#endif // WEATHERSERVICE_H
