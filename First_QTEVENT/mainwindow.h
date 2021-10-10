#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include<QEvent>
#include <softkeyboard.h>
#include<QThread>
#include<QTime>
#include <myclass.h>

//SQL数据库header
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <sqltable.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class timeThread: public QThread
{
    Q_OBJECT
public:
    timeThread(QObject *parent = nullptr){};
    ~timeThread(){};
    void run() override
    {
        QTime t ;

        while (1)
        {
            t = QTime::currentTime();
            QString strTime = t.toString("hh:mm:ss");
            //发送信号
            emit sendTime(strTime);
            QThread::sleep(1);
        }
    }
signals:
    void sendTime(const QString & time);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event);

private slots:

//    void on_lineEdit_textEdited(const QString &arg1);

//    void on_toolButton_clicked();

    void on_exchangeBtn_clicked();

    void rcvTime(const QString &time);

    void rec_msg(const QString& msg);

    void on_registerBtn_clicked();

    void on_UserlineEdit_editingFinished();

    void on_passwordlineEdit_editingFinished();

signals:
    void send_command();
    void Stop_thread();
private:
    Ui::MainWindow *ui;
    bool isLowerOrbig;//判断是否为大小写；
    softKeyboard* keyBoard;
    timeThread * currentTime;

    QThread anotherThread;

    //SQL数据库
    QSqlDatabase database;
    SQLTable * mytable;
};



#endif // MAINWINDOW_H
