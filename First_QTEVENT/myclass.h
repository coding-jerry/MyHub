#ifndef MYCLASS_H
#define MYCLASS_H

#include <QWidget>
#include<QEvent>
#include<QThread>
#include <QTime>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    ~MyClass();

//    bool event(QEvent *ev) override
//    {
//        if(ev->type() == QEvent::PolishRequest)
//        {

//            return true;
//        }
//        else if (ev->type() == QEvent::Show)
//        {
//            QObject::event(ev);
//            return true;
//        }
//        return  QObject::event(ev);
//    }
public slots:
    void doWork();
    void stopThread();

signals:
    void send_msg(const QString& msg);

private:
    bool isStop;

};

#endif // MYCLASS_H
