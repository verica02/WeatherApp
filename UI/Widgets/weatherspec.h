#ifndef WEATHERSPEC_H
#define WEATHERSPEC_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>

#include "../../Logic/weatherlogic.h"
#include "flyingbox.h"

class WeatherSpec : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherSpec(QWidget *parent = nullptr);
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void updateDescriptions(WeatherInfo weatherInfo);

private:
    QHBoxLayout hLayouts[2];
    QVBoxLayout vLayout;

    FlyingBox pressure;
    FlyingBox windSpeed;
    FlyingBox humidity;
    FlyingBox cloudiness;

    void configureWidgets();
};

#endif // WEATHERSPEC_H
