#include "weathercontroller.h"
#include <QDebug>

WeatherController::WeatherController(QObject *parent) :
    QObject(parent), weatherInfo(new WeatherInfo) {
}

WeatherController::WeatherController(WeatherLogic *weatherLogic) : WeatherController()
{
    setLogic(weatherLogic);
}

void WeatherController::setLogic(WeatherLogic *weatherLogic) {
    this->weatherLogic = weatherLogic;
    connect(this, &WeatherController::getData, weatherLogic, &WeatherLogic::queryData);
    connect(weatherLogic, &WeatherLogic::info, this, &WeatherController::userInfo);
}

void WeatherController::queryData(QString query)
{
    if(query != ""){
        qDebug() << "emitting getData";
        emit getData(query);
    }

    qDebug() << "Query: " << query << "in WeatherController::queryData";
}

void WeatherController::logicDataUpdated(WeatherInfo data)
{
    *weatherInfo = data;
    emit weatherUpdated(data);
    emit ui_weatherUpdated();
    emit briefInfoUpdated(data.iconCode, data.temperature, data.description);
}

