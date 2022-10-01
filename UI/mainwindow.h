#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Controller/weathercontroller.h"

#include <QMainWindow>
#include <QLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(WeatherController *weatherController, QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    QWidget *userInteracionWidget;
    QWidget *weatherWidget;
    QWidget *centralWidget;
    QWidget *briefWidget;
    QLayout *layout;
    WeatherController *weatherController;

    void setAppereance();
    void makeConnections();
};

#endif // MAINWINDOW_H
