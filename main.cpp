#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WeatherApp/weatherapp.h"

#include "Logic/weatherlogic.h"
#include "Controller/weathercontroller.h"

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);

    qmlRegisterType<WeatherController>("WC", 1, 0, "WeatherController");

    WeatherLogic weatherLogic;
    WeatherController weatherController;
    weatherController.setLogic(&weatherLogic);
    
    QObject::connect(&weatherLogic, &WeatherLogic::weatherUpdated, &weatherController, &WeatherController::logicDataUpdated);
    QObject::connect(&weatherLogic, &WeatherLogic::invalidQuery, &weatherController, &WeatherController::invalidQuery);

    QQmlApplicationEngine qmlEngine;
    qmlEngine.addImportPath("qrc:/");
    qmlEngine.rootContext()->setContextProperty("weatherController",
                                                &weatherController);

    qmlEngine.load(QUrl(QStringLiteral("qrc:/Views/MainView.qml")));
    if(qmlEngine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
