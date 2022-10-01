#include "weatherwidget.h"
#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QDebug>

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget(parent)
{
    labelTemperature = new QLabel;
    labelHumidity  = new QLabel;
    labelPressure  = new QLabel;
    labelCloud     = new QLabel;
    labelWindSpeed = new QLabel;
    layout 		   = new QVBoxLayout;

    this->setLayout(layout);
    configureWidgets();
    makeConnections();
}

WeatherWidget::~WeatherWidget()
{
    delete layout;
    delete labelTemperature;
}

void WeatherWidget::update(WeatherInfo data)
{
    qDebug() << "updating weather widget";

    updateLabels(data);
}

void WeatherWidget::makeConnections()
{
}

bool WeatherWidget::configureWidgets(QString configFilePath)
{
    layout->addWidget(labelTemperature);
    layout->addWidget(labelCloud);
    layout->addWidget(labelHumidity);
    layout->addWidget(labelPressure);
    layout->addWidget(labelWindSpeed);

    labelTemperature->setText("Temperature");
    labelCloud->setText("Cloud");
    labelHumidity->setText("Humidity");
    labelPressure->setText("Pressure");
    labelWindSpeed->setText("Wind speed");

    Q_UNUSED(configFilePath); // to be corrected

    return true;
}

void WeatherWidget::updateLabels(WeatherInfo &weatherInfo)
{
    labelTemperature->setText(weatherInfo.temperature);
    labelCloud->setText(weatherInfo.cloudDescription);
    labelHumidity->setText(weatherInfo.humidity);
    labelPressure->setText(weatherInfo.pressure);
    labelWindSpeed->setText(weatherInfo.windSpeed);
}
