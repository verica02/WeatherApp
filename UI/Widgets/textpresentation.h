#ifndef TEXTPRESENTATION_H
#define TEXTPRESENTATION_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QSize>
#include <QMouseEvent>

class TextPresentation : public QWidget
{
    Q_OBJECT
public:
    explicit TextPresentation(QWidget *parent=nullptr);
    ~TextPresentation(){} // TODO: implement d-tor

    QSize sizeHint()const Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void updateText(QString text);

signals:
    void mousePressed();

private:
    QLabel *label;

    void configureLabel();
};

#endif // TEXTPRESENTATION_H
