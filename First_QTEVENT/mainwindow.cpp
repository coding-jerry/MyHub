#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UserlineEdit->installEventFilter(this);
    ui->passwordlineEdit->installEventFilter(this);

//    ui->bigCasewidget->hide();
//    ui->lowerCasewidget->hide();
    ui->bigCasewidget->setVisible(false);
    ui->lowerCasewidget->setVisible(false);

    this->isLowerOrbig = false;

    //直接定义一个类得到键盘界面
    //this->keyBoard->getUi();
    keyBoard = new softKeyboard(this);
    keyBoard->setGeometry(this->x(),this->height()/2,this->width(),this->height()/2);
    //keyBoard->hide();
    keyBoard->setVisible(false);

    this->currentTime = new timeThread;
    //绑定发送时间和接收时间
    connect(currentTime,&timeThread::sendTime,this,&MainWindow::rcvTime);
    //this->currentTime->run();-->这个是个错误
    this->currentTime->start();

    //线程的另外一种模式
    MyClass *mc = new MyClass;
    mc->moveToThread(&anotherThread);


    connect(&anotherThread,&QThread::finished,mc,&QObject::deleteLater,Qt::DirectConnection);
    connect(this,&MainWindow::send_command,mc,&MyClass::doWork);
    connect(mc,&MyClass::send_msg,this,&MainWindow::rec_msg);
    connect(this,&MainWindow::Stop_thread,mc,&MyClass::stopThread);
    emit send_command();
    anotherThread.start();

    //SQL数据库操作
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
        qDebug()<< "SQL table is existing" << endl;
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        database.setUserName("Jerry");
        database.setPassword("123");
        qDebug() << "create SQL table success" << endl;
    }
    mytable = new SQLTable(&database,"Jerry","123");
}

MainWindow::~MainWindow()
{
    emit Stop_thread();
    anotherThread.quit();
    anotherThread.wait();
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->UserlineEdit || obj == ui->passwordlineEdit)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
//                ui->toolButton->show();
//                ui->toolButton_2->show();

                if(!this->isLowerOrbig)
                {
                    //ui->bigCasewidget->show();
                    ui->bigCasewidget->setVisible(true);
                }
                else
                {
//                    ui->lowerCasewidget->show();
                    //this->isLowerOrbig = true;
                    ui->lowerCasewidget->setVisible(true);
                }

                if(obj == ui->passwordlineEdit)
                    ui->passwordlineEdit->setFocus();
                else
                    ui->UserlineEdit->setFocus();
            }
        }
    }
    return QMainWindow::eventFilter(obj,event);
}

void MainWindow::on_exchangeBtn_clicked()
{
    ui->UserlineEdit->setFocus();
    if(this->isLowerOrbig)
    {
//        ui->bigCasewidget->show();
//        ui->lowerCasewidget->hide();
        ui->bigCasewidget->setVisible(true);
        ui->lowerCasewidget->setVisible(false);

        this->isLowerOrbig = false;
    }
    else
    {
//        ui->bigCasewidget->hide();
//        ui->lowerCasewidget->show();
        this->isLowerOrbig = true;
        ui->bigCasewidget->setVisible(false);
        ui->lowerCasewidget->setVisible(true);
    }
}

void MainWindow::rcvTime(const QString &strtime)
{
    ui->label->setText(strtime);
}

void MainWindow::rec_msg(const QString &msg)
{
    ui->label_2->setText(msg);
}

void MainWindow::on_registerBtn_clicked()
{
    if(ui->UserlineEdit->text() == nullptr || ui->passwordlineEdit->text() == nullptr)
    {
        QMessageBox::warning(this,"warning","input your user name or password");
    }
    else {
        QMap<QString,QString> acount;
        acount.insert(ui->UserlineEdit->text(),ui->passwordlineEdit->text());
        mytable->insertDataInSQLTable(acount);
        qDebug() << "insert the Table" << endl;
    }
}

void MainWindow::on_UserlineEdit_editingFinished()
{
    if(this->isLowerOrbig)
    {
        ui->bigCasewidget->hide();
    }
    else
    {
        ui->lowerCasewidget->hide();
    }
}

void MainWindow::on_passwordlineEdit_editingFinished()
{
    if(this->isLowerOrbig)
    {
        ui->bigCasewidget->hide();
    }
    else
    {
        ui->lowerCasewidget->hide();
    }
}
