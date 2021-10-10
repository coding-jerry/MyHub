#include "mybtn.h"
#include <QKeyEvent>
#include <QApplication>

MyBtn::MyBtn(QWidget *parent):QToolButton(parent)
{
    connect(this,SIGNAL(clicked(bool)),this,SLOT(button_clicked(bool)));
}

MyBtn::~MyBtn()
{

}

void MyBtn::button_clicked(bool)
{
    if(this->text() == "<-")
    {
        QKeyEvent *ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier,this->text());
        QApplication::postEvent(QApplication::focusWidget(),ke);
    }
    else {
        QKeyEvent *ke = new QKeyEvent(QEvent::KeyPress,'a',Qt::NoModifier,this->text());
        QApplication::postEvent(QApplication::focusWidget(),ke);
    }

}


