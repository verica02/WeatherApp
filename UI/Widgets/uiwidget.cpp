#include "uiwidget.h"
#include <QVBoxLayout>
#include <QDebug>


UIWidget::UIWidget(QWidget *parent) : QWidget(parent)
{
    textEditor = new TextEditor(this);
    textPresentation = new TextPresentation(this);
    layout = new QVBoxLayout;
    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(textEditor);
    stackedWidget->addWidget(textPresentation);

    layout->addWidget(stackedWidget);
    setLayout(layout);

    configureWidgets();
    makeConnections();

    widgetState = PRESENTATION;
    stackedWidget->setCurrentWidget(textPresentation);
}

UIWidget::~UIWidget()
{
    delete textEditor;
    delete textPresentation;
    delete stackedWidget;
    delete layout;
}

void UIWidget::newQuery(QString query)
{
    qDebug() << "clicked " << query;
    emit queryData(query);
}

void UIWidget::switchToTextEditor()
{
    stackedWidget->setCurrentWidget(textEditor);
}

void UIWidget::switchToTextPresentation()
{
    stackedWidget->setCurrentWidget(textPresentation);
}

void UIWidget::makeConnections()
{
    connect(textEditor, &TextEditor::textInserted, this, &UIWidget::newQuery);
    connect(textEditor, &TextEditor::textInserted, textPresentation, &TextPresentation::updateText);
    connect(textPresentation, &TextPresentation::mousePressed, this, &UIWidget::switchToTextEditor);
    connect(textEditor, &TextEditor::textInserted, this, &UIWidget::switchToTextPresentation);
    connect(textEditor, &TextEditor::insertCancelled, this, &UIWidget::switchToTextPresentation);
}

void UIWidget::configureWidgets()
{
    layout->setAlignment(stackedWidget, Qt::AlignCenter);
}
