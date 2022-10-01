#ifndef BRIEFWIDGET_H
#define BRIEFWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QStackedLayout>


/** The BriefWidget class
 *
 * /brief Class embeds 3 so called views, which provide informative role or user.
 */
class BriefWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BriefWidget(QWidget *parent = nullptr);
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void setNormalView(QString imageCode, QString mainText, QString secondaryText);
    void setGreetingView();
    void setInvalidQueryView();

private:
    QStackedLayout stackedLayout;
    void configureViews();

    // normal View
    QWidget normalView;
    QHBoxLayout normalViewLayout;
    QVBoxLayout vLayout[2];
    QLabel mainText;
    QLabel secondaryText;
    QLabel image;
    void normalViewUpdate(QString imageCode, QString mainText, QString secondaryText);
    void normalViewConfigure();
    void normalViewFormatMainText();
    void normalViewFormatSecondaryText();
    void normalViewFormatImage();
    void normalViewConfigureLayout();

    // invalid query View
    QWidget invalidQueryView;
    QVBoxLayout invalidViewLayout;
    QLabel invalidViewImage;
    QLabel invalidViewText;
    void invalidQueryViewConfigure();

    // greeting View
    QWidget greetView;
    QHBoxLayout greetViewLayout;
    QLabel greetViewImage;
    QLabel greetViewText;
    void greetViewConfigure();
};

#endif // BRIEFWIDGET_H
