#include "flyingbox.h"
#include <QPixmap>

#include <QSize>
#include <QDebug>

const int iconWidth = 100; // TODO: fix these disgusting consts
const int iconHeight = 100;

FlyingBox::FlyingBox(QWidget *parent) : QWidget(parent)
{
    icon = new QLabel(this);
    hiddenText = new QLabel(this);

    fadeEffect = new QGraphicsOpacityEffect;

    iconFlyingDown = new QPropertyAnimation;
    iconFlyingUp = new QPropertyAnimation;
    fadeInHiddenText = new QPropertyAnimation;
    fadeOutHiddenText =new QPropertyAnimation;

    showAnimation = new QParallelAnimationGroup;
    hideAnimation = new QParallelAnimationGroup;

    layout = new QVBoxLayout;

    initAnimations();
    configureWidgets();

    setLayout(layout);
    setAttribute(Qt::WA_Hover);
    performHideAnimation();
}

FlyingBox::~FlyingBox(){
    delete icon;
    delete hiddenText;
    delete iconFlyingDown;
    delete iconFlyingUp;
    delete fadeEffect;
}

void FlyingBox::setIcon(QString path)
{
    QPixmap pixmap(path);
    icon->setPixmap(pixmap);
}

void FlyingBox::setHiddenText(QString text)
{
    hiddenText->setText(text);
}

void FlyingBox::performShowAnimation()
{
    showAnimation->start();
}

void FlyingBox::performHideAnimation()
{
    hideAnimation->start();
}

void FlyingBox::initAnimations()
{
    initHideAnimation();
    initShowAnimation();
    hiddenText->setGraphicsEffect(fadeEffect);
}

void FlyingBox::initAnimationUp()
{
    iconFlyingUp->setTargetObject(icon);
    iconFlyingUp->setPropertyName("geometry");
    iconFlyingUp->setDuration(200);
    iconFlyingUp->setStartValue(QRect(25, 100, 100, 100));
    iconFlyingUp->setEndValue(QRect(25, 50, 100, 100));
}

void FlyingBox::initAnimationDown()
{
    iconFlyingDown->setTargetObject(icon);
    iconFlyingDown->setPropertyName("geometry");
    iconFlyingDown->setDuration(500);
    iconFlyingDown->setStartValue(QRect(25, 50, 100, 100));
    iconFlyingDown->setEndValue(QRect(25, 100, 100, 100));
}

void FlyingBox::initAnimationFadeOut()
{
    fadeOutHiddenText->setTargetObject(fadeEffect);
    fadeOutHiddenText->setPropertyName("opacity");
    fadeOutHiddenText->setDuration(300);
    fadeOutHiddenText->setStartValue(1);
    fadeOutHiddenText->setEndValue(0);
}

void FlyingBox::initAnimationFadeIn()
{
    fadeInHiddenText->setTargetObject(fadeEffect);
    fadeInHiddenText->setPropertyName("opacity");
    fadeInHiddenText->setDuration(1000);
    fadeInHiddenText->setStartValue(0);
    fadeInHiddenText->setEndValue(1);
}

void FlyingBox::initShowAnimation()
{
    initAnimationUp();
    initAnimationFadeIn();

    showAnimation->addAnimation(iconFlyingUp);
    showAnimation->addAnimation(fadeInHiddenText);
}

void FlyingBox::initHideAnimation()
{
    initAnimationDown();
    initAnimationFadeOut();

    hideAnimation->addAnimation(iconFlyingDown);
    hideAnimation->addAnimation(fadeOutHiddenText);
}

void FlyingBox::configureWidgets()
{
    layout->addWidget(icon);
    layout->addWidget(hiddenText);
    layout->setAlignment(hiddenText, Qt::AlignCenter);
//    QSize qize (iconHeight, iconWidth);
//    icon->setFixedSize(iconHeight, iconWidth);
}

QSize FlyingBox::sizeHint() const {
    return QSize(200, 200);
}

bool FlyingBox::event(QEvent *event)
{
    switch(event->type()){
    case QEvent::HoverEnter:
        performShowAnimation();
        return true;
    case QEvent::HoverLeave:
        performHideAnimation();
        return true;
    default:
        break;
    }

    return QObject::event(event);
}
