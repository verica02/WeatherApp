#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include "../Logic/weatherlogic.h"

#include <QObject>
#include <QString>

class WeatherController : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(WeatherInfo* ui_weatherInfo READ ui_weatherInfo NOTIFY ui_weatherUpdated)
    
    explicit WeatherController(QObject *parent=nullptr);
    explicit WeatherController(WeatherLogic *weatherLogic);
    void setLogic(WeatherLogic *weatherLogic);

signals:
    void ui_weatherUpdated();
    void weatherUpdated(WeatherInfo weatherInfo);
    void briefInfoUpdated(QString iconCode, QString temperature, QString description);
    void invalidQuery();
    void userInfo(QString info);

    void getData(QString query);    // for communication with data provider

public slots:
    WeatherInfo *ui_weatherInfo() {
        return weatherInfo;
    }
    void queryData(QString query);
    void logicDataUpdated(WeatherInfo weatherInfo);

private:
    WeatherLogic *weatherLogic{nullptr};
    WeatherInfo *weatherInfo{nullptr};
};

#endif // WEATHERCONTROLLER_H
