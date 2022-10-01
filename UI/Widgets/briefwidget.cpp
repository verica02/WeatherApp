#include "briefwidget.h"
#include <QTextFormat>

const QString invalidViewImagePath = ":Icons/invalid_view_image"; // TODO: fix these disgusting consts
const QString greetViewImagePath = ":/Icons/greetings_view_image";

BriefWidget::BriefWidget(QWidget *parent) : QWidget(parent)
{
    configureViews();
    setLayout(&stackedLayout);
    setGreetingView();
}

QSize BriefWidget::sizeHint() const
{
    return QSize(200, 100);
}

void BriefWidget::setNormalView(QString imageCode, QString mainText, QString secondaryText)
{
    normalViewUpdate(imageCode, mainText, secondaryText);
    stackedLayout.setCurrentWidget(&normalView);
}

void BriefWidget::setGreetingView()
{
    stackedLayout.setCurrentWidget(&greetView);
}

void BriefWidget::setInvalidQueryView()
{
    stackedLayout.setCurrentWidget(&invalidQueryView);
}

void BriefWidget::configureViews()
{
    normalViewConfigure();
    invalidQueryViewConfigure();
    greetViewConfigure();

    stackedLayout.addWidget(&normalView);
    stackedLayout.addWidget(&invalidQueryView);
    stackedLayout.addWidget(&greetView);
}

void BriefWidget::normalViewUpdate(QString imageCode, QString mainText, QString secondaryText)
{
    QPixmap pixmap(":Icons/"+imageCode);
    this->image.setPixmap(pixmap);

    this->mainText.setText(mainText);
    this->secondaryText.setText(secondaryText);
}

void BriefWidget::normalViewConfigure()
{
    normalViewFormatMainText();
    normalViewFormatSecondaryText();
    normalViewFormatImage();
    normalViewConfigureLayout();
}

void BriefWidget::normalViewFormatMainText()
{
    QFont font("Helvetica", 35, QFont::Thin);
    mainText.setFont(font);
    mainText.setText("X\xBO C");
    mainText.setAlignment(Qt::AlignCenter);
}

void BriefWidget::normalViewFormatSecondaryText()
{
    QFont font("Helvetica", 20, QFont::Light);
    secondaryText.setFont(font);
    secondaryText.setText("Description");
    secondaryText.setAlignment(Qt::AlignCenter);
}

void BriefWidget::normalViewFormatImage()
{
    ;
}

void BriefWidget::normalViewConfigureLayout()
{
    vLayout[1].addWidget(&secondaryText);
    vLayout[1].addWidget(&mainText);
    vLayout[0].addWidget(&image);

    normalViewLayout.addLayout(&vLayout[0]);
    normalViewLayout.addLayout(&vLayout[1]);

    normalView.setLayout(&normalViewLayout);
}

void BriefWidget::invalidQueryViewConfigure()
{
    QPixmap invalidViewPixmap(invalidViewImagePath);
    invalidViewImage.setPixmap(invalidViewPixmap);

    invalidViewText.setText("I don't have information about specified city.");

    invalidViewLayout.addWidget(&invalidViewImage);
    invalidViewLayout.addWidget(&invalidViewText);

    invalidQueryView.setLayout(&invalidViewLayout);
}

void BriefWidget::greetViewConfigure()
{
    QPixmap greetViewPixmap(greetViewImagePath);
    greetViewImage.setPixmap(greetViewPixmap);

    greetViewText.setText("Hello! Click above to type your city name.");

    greetViewLayout.addWidget(&greetViewImage);
    greetViewLayout.addWidget(&greetViewText);

    greetView.setLayout(&greetViewLayout);
}
