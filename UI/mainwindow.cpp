#include "mainwindow.h"
#include "Widgets/uiwidget.h"
#include "Widgets/weatherspec.h"
#include "Widgets/briefwidget.h"

#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(WeatherController *weatherController, QWidget *parent) : QMainWindow(parent)
{
    weatherWidget = new WeatherSpec;
    userInteracionWidget = new UIWidget;
    centralWidget = new QWidget;
    briefWidget = new BriefWidget;
    layout = new QVBoxLayout;
    this->weatherController = weatherController;

    makeConnections();
    setAppereance();
}

MainWindow::~MainWindow()
{
    delete weatherWidget;
    delete userInteracionWidget;
    delete centralWidget;
    delete briefWidget;
    delete layout;
}

void MainWindow::setAppereance()
{
    layout->addWidget(userInteracionWidget);
    layout->addWidget(briefWidget);
    layout->addWidget(weatherWidget);

    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);

    layout->setAlignment(userInteracionWidget, Qt::AlignCenter);
    layout->setAlignment(weatherWidget, Qt::AlignCenter);
    layout->setAlignment(briefWidget, Qt::AlignCenter);
}

void MainWindow::makeConnections()
{
    // widgets
    connect(userInteracionWidget, SIGNAL(queryData(QString)), weatherController, SLOT(queryData(QString)));
    connect(weatherController, SIGNAL(briefInfoUpdated(QString,QString,QString)), briefWidget, SLOT(setNormalView(QString, QString, QString)));

    // logic
    connect(weatherController, SIGNAL(weatherUpdated(WeatherInfo)), weatherWidget, SLOT(updateDescriptions(WeatherInfo)));
    connect(weatherController, SIGNAL(invalidQuery()), briefWidget, SLOT(setInvalidQueryView()));
}
