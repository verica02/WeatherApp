#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>

#include "../../Logic/weatherlogic.h"

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    WeatherWidget(QWidget *parent = 0);
    ~WeatherWidget();

public slots:
    void update(WeatherInfo weatherInfo);

private:
    void makeConnections();
    bool configureWidgets(QString configFile="MainWindowLayout.json");
    void updateLabels(WeatherInfo &WeatherInfo);

    QLabel *labelTemperature;
    QLabel *labelHumidity;
    QLabel *labelPressure;
    QLabel *labelCloud;
    QLabel *labelWindSpeed;
    QVBoxLayout *layout;
};

#endif // WEATHERWIDGET_H
