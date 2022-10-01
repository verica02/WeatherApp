#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include <QString>
#include <QLayout>
#include <QStackedWidget>

#include "texteditor.h"
#include "textpresentation.h"

class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    ~UIWidget();

signals:
    void queryData(QString query);

private slots:
    void newQuery(QString query);
    void switchToTextEditor();
    void switchToTextPresentation();

private:
    enum WidgetState {PRESENTATION, INSERTION} widgetState;

    QLayout *layout;
    QStackedWidget *stackedWidget;
    TextEditor *textEditor;
    TextPresentation *textPresentation;

    void makeConnections();
    void configureWidgets();
};


#endif // UIWIDGET_H
