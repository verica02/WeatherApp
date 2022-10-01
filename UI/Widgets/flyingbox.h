#ifndef FLYINGBOX_H
#define FLYINGBOX_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSize>
#include <QGraphicsOpacityEffect>
#include <QLayout>
#include <QEvent>

class FlyingBox : public QWidget
{
    Q_OBJECT
public:
    explicit FlyingBox(QWidget *parent = nullptr);
    ~FlyingBox();

    QSize sizeHint() const Q_DECL_OVERRIDE;
    bool event(QEvent *event) Q_DECL_OVERRIDE;

public slots:
    void setIcon(QString pathToIcon);
    void setHiddenText(QString text);

private:
    // Widgets
    QLabel *icon;
    QLabel *hiddenText;
    QLayout *layout;

    // animations invocations
    void performShowAnimation();
    void performHideAnimation();

    // animations
    QParallelAnimationGroup *showAnimation;
    QParallelAnimationGroup *hideAnimation;
    QPropertyAnimation *iconFlyingUp;
    QPropertyAnimation *iconFlyingDown;
    QPropertyAnimation *fadeInHiddenText;
    QPropertyAnimation *fadeOutHiddenText;
    QGraphicsOpacityEffect *fadeEffect;

    void initAnimations();
    void initAnimationUp();
    void initAnimationDown();
    void initAnimationFadeOut();
    void initAnimationFadeIn();
    void initShowAnimation();
    void initHideAnimation();

    // widgets appereance changing
    void configureWidgets();
};

#endif // FLYINGBOX_H
