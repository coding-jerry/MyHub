#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    this->isStop = false;

}

MyClass::~MyClass()
{

}

void MyClass::stopThread()
{
    this->isStop = true;
}

void MyClass::doWork()
{
    QTime t;
    while (!isStop) {
        t = QTime::currentTime();
        QString strTime = t.toString("HH:mm:ss:zzz");
        emit send_msg(strTime);
    }
}
