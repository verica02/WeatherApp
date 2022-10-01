#include "weatherlogic.h"

#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QFileInfo>
#include <QChar>
#include <QMap>

#include <algorithm>
#include <memory>

#include "weatherservice.h"
#include "htttqueryservice.h"

#define GET_NEW_DATA

class QueryValidator {
    public:
    virtual ~QueryValidator() {delete next;}
    void addValidator(QueryValidator *validator) {
        next = validator;
    }
    virtual void validate(QString &query){
        if(next) next->validate(query);
    }

    private:
    QueryValidator *next{nullptr};
};

class UpperCaseQueryValidator : public QueryValidator {
    public:
    void validate(QString &query) override {

        QStringList strList = query.split(" ");
        query.clear();

        for(auto &str : strList) {
            makeFirstCharUpper(str);
            query += str + " ";
        }
        query.remove(query.size()-1, 1);

        QueryValidator::validate(query);
    }

    private:
    void makeFirstCharUpper(QString &str) {
        str[0] = str[0].toUpper();
        std::for_each(str.begin()+1, str.end(), [](QChar &c) {
            c = c.toLower();
        });
        qDebug() << __FUNCTION__ << " " << str;
    }
};

class ApiKeyParser {
    public:
    QString getApiKey(QString filepath) {
        QFile credentialsFile{filepath};

        if(!credentialsFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Api key file doesn't exist";
            return "";
        }
        QString key = credentialsFile.readLine();
        credentialsFile.close();
        qDebug() << "api key is: " << key;
        
        return key;
    }
};

class CityCodesParser {
  public:
    CityCodesParser(QString codesFilepath) {
        codes.setFileName(codesFilepath);
        if(!codes.open(QIODevice::ReadOnly)) {
            qDebug() << "File doesn't exist";
            codes.close();
            return;
        } 

        while(!codes.atEnd()) {
            content += codes.readLine();
        }
        codes.close();
    }

    QString findCodeForCity(QString city) {

        if(!codes.open(QIODevice::ReadOnly)) {
            qDebug() << "File doesn't exist";
            return "";
        } 
        QJsonDocument jsonDocument = QJsonDocument::fromJson(content.toUtf8());
        QJsonObject jsonObject = jsonDocument.object();
        QJsonArray jsonArray = jsonDocument.array();

        foreach(const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            if(city == obj.value("name").toString()) {
                qDebug() << "code of " << city << " is " << obj.value("id");
                codes.close();
                return QString::number(obj.value("id").toInt());
            }
        }
        
        return "";
    }

  private:
    QFile codes;
    QString content;
};

WeatherLogic::WeatherLogic(QObject *parent) : QObject(parent)
{
    std::unique_ptr<HttpQueryService> httpService(new HttpQueryService{});
    std::unique_ptr<WeatherService> weatherServ(new WeatherService{std::move(httpService)});
    weatherService = std::move(weatherServ);
    makeConnections();
}

void WeatherLogic::queryData(QString queryCity)
{
    QueryValidator queryValidator;
    queryValidator.addValidator(new UpperCaseQueryValidator);
    queryValidator.validate(queryCity);
    qDebug() << "After validation " << queryCity;
    latestQuery = queryCity;
#ifdef GET_NEW_DATA
    getWeatherFromNetwork(queryCity);
#else
    queryFinished(0, QProcess::NormalExit);
#endif
}

void WeatherLogic::onWeatherServiceReply(QString reply)
{
    if(reply == "") {
        qDebug() << "Reply error, taking old data";
        emit invalidQuery();
        return;
    }

    emit weatherUpdated(getWeatherInfoFromReply(reply));
}

void WeatherLogic::makeConnections()
{
    connect(weatherService.get(), &WeatherService::reply, this,
            &WeatherLogic::onWeatherServiceReply);
}

void WeatherLogic::getWeatherFromNetwork(QString city) {

    static CityCodesParser cityCodeParser(":/city_codes");
    ApiKeyParser apiKeyParser;
    QString cityCode = cityCodeParser.findCodeForCity(city);
    QString apiKey = apiKeyParser.getApiKey(":/Credentials/api_key");

    if(cityCode == "") {
        emit invalidQuery();
        return;
    }
    if(apiKey == "") {
        emit info(QString{"No Credentials"});
        qDebug() << "Api key not found";
        return;
    }

    qDebug() << __FUNCTION__ << " city code " << cityCode;
    weatherService->setBaseUrl("http://api.openweathermap.org/data/2.5/weather?");
    weatherService->setQueryString(QMap<QString, QString> {
                        std::pair<QString, QString>{"appid=", apiKey},
                        std::pair<QString, QString>{"&id",cityCode}});
    weatherService->getWeather();
}

QString WeatherLogic::KelvinsToCelsius(QString tempKelvin)
{
    double temperature = tempKelvin.toDouble() - 273;
    return QString::number(temperature);
}

WeatherInfo WeatherLogic::getWeatherInfoFromReply(QString reply)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    WeatherInfo weatherInfo;
    fillWeatherInfoFromJson(jsonObject ,weatherInfo);

    return weatherInfo;
}

void WeatherLogic::getWindSpeedFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
   weatherInfo.windSpeed = QString::number(jsonObject.value("speed").toDouble()) + "m/s";
}

void WeatherLogic::getMainFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
    foreach(const QString& jsonKey, jsonObject.keys()){
        if("temp" == jsonKey){
            weatherInfo.temperature = KelvinsToCelsius(QString::number(jsonObject.value(jsonKey).toDouble()));
            weatherInfo.temperature += " \u00B0C";
        } else if ("pressure" == jsonKey) {
            weatherInfo.pressure = QString::number(jsonObject.value(jsonKey).toDouble());
            weatherInfo.pressure += " hPa";
        } else if ("humidity" == jsonKey) {
            weatherInfo.humidity = QString::number(jsonObject.value(jsonKey).toDouble());
            weatherInfo.humidity += " %";
        }
    }
}

void WeatherLogic::getWeatherFromJson(QJsonArray jsonArray, WeatherInfo &weatherInfo)
{
    QJsonObject jsonObject = (jsonArray[0].toArray())[0].toObject();

    foreach(const QString& jsonKey, jsonObject.keys()){

        if("main" == jsonKey){
            weatherInfo.description = jsonObject.value(jsonKey).toString();
        } else if ("description" == jsonKey) {
            weatherInfo.cloudDescription = jsonObject.value(jsonKey).toString();
        } else if ("icon" == jsonKey) {
            weatherInfo.iconCode = jsonObject.value(jsonKey).toString();
        }
    }
}

void WeatherLogic::fillWeatherInfoFromJson(QJsonObject jsonObject, WeatherInfo &weatherInfo)
{
    foreach(const QString& jsonKey, jsonObject.keys()){

        if("main" == jsonKey) {
            getMainFromJson(jsonObject.value(jsonKey).toObject(), weatherInfo);
        } else if ("weather" == jsonKey) {
            QJsonArray jsonArray{jsonObject.value(jsonKey)};
            getWeatherFromJson(jsonArray, weatherInfo);
        } else if ("wind" == jsonKey) {
            getWindSpeedFromJson(jsonObject.value(jsonKey).toObject(), weatherInfo);
        }
    }
}
