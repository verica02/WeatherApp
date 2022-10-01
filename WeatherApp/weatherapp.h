#ifndef WEATHERAPP_H
#define WEATHERAPP_H

#include "../Logic/weatherlogic.h"
#include "../Controller/weathercontroller.h"

#include <QObject>
#include <QMainWindow>

class WeatherApp : QObject
{
    Q_OBJECT
public:
    explicit WeatherApp(QObject *parent=nullptr);
    ~WeatherApp();
    void run();

private:
    QMainWindow *mainWindow;
    WeatherLogic *weatherLogic;
    WeatherController *weatherController;

    void makeConnections();
};

#endif // WEATHERAPP_H
