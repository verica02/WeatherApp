#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QKeyEvent>
#include <QSize>

class TextEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor(){} // TODO: implement d-tor

    QSize sizeHint() const Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
signals:
    void textInserted(QString);
    void insertCancelled();

private:
    QLineEdit *lineEdit;
    void configureLineEdit();
    QString currentQuery;

    // key handling
    void onEscKey();
    void onEnterKey();
};

#endif // TEXTEDITOR_H
