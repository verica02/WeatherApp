#include "texteditor.h"
#include <QDebug>

TextEditor::TextEditor(QWidget *parent) : QWidget(parent)
{
    lineEdit = new QLineEdit(this);
    configureLineEdit();
    currentQuery = "Your City";
}

void TextEditor::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Return:
        onEnterKey();
        break;
    case Qt::Key_Escape:
        onEscKey();
        break;
    default:
        break;
    }
}

void TextEditor::configureLineEdit()
{
    // TODO: load initial values from file
    lineEdit->setText("Your City");
    lineEdit->setStyleSheet("background-color:rgba(0,0,0,0)");
}

void TextEditor::onEscKey()
{
   lineEdit->setText(currentQuery);
   emit insertCancelled();
}

void TextEditor::onEnterKey()
{
    currentQuery = lineEdit->text();
    emit textInserted(lineEdit->text());
}

QSize TextEditor::sizeHint() const {
    return QSize(200, 50); // TODO: fix that
}
