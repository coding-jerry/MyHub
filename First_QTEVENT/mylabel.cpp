#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent)
{

}

MyLabel::~MyLabel()
{

}

bool MyLabel::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);

        if(mouseEvent->button() == Qt::LeftButton)
        {
            qDebug() << "you push the Left mouseBtn" << endl;
            return true;
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {
            qDebug() << "you push the Right mouseBtn " << endl;
            return true;
        }
    }
    return QLabel::event(e);
}
