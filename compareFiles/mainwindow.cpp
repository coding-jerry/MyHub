#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <sys/timeb.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFilesInfo(Model m)
{
    if(!m_path.isEmpty())
    {
        QStringList fileNames = m_md5.getFiles(m_path);
        QByteArray *btyAry = new QByteArray();
        QTime qTime;
        for(int i=0;i<fileNames.size();i++)
        {
            QString fileNamePath = fileNames[i];
    //        QString md5 = m_md5.getFileMd5(fileNamePath);

            //将相应文件的Md5加入列表
//            qDebug() << __FUNCTION__ << __LINE__ << fileNamePath << ": " << md5.toUtf8().toHex()<< endl;
            if(m == Model::FILE1)
            {
                //计算读取文件的时间 利用QTime，其精度为ms级
                qTime.start();
                *btyAry = m_md5.getFileData(fileNamePath);
                qDebug() << "getFileData running time : " << qTime.elapsed()/1000.0 << "s";

                //计算形成Md5 code 的时间
                qTime.start();
                QString md5 = m_md5.getSigFileMd5(*btyAry);
                qDebug() << "getSigFileMd5 running time : " << qTime.elapsed()/1000.0 << "s";
                m_map1[fileNamePath] = md5;
                m_fileNames1.append(fileNamePath);
            }
            else if(m == Model::FILE2)
            {
                qTime.start();
                QString md5 = m_md5.getFileMd5(fileNamePath);
                qDebug() << "[block]getFileMd5 running time : " << qTime.elapsed()/1000.0 << "s";
                m_map2[fileNamePath] = md5;
                m_fileNames2.append(fileNamePath);
            }
        } //end for
    }//end if
}

/*
    打开文件1
*/
void MainWindow::on_btn_open_5_clicked()
{
    ui->listWidget_1->clear();

    m_fileNames1.clear();
    QString path = m_md5.openDirectory();
    m_path = path;
    qDebug() << __FUNCTION__ << __LINE__ << m_path << endl;
    QTime qtime;
    qtime.start();
    getFilesInfo(Model::FILE1);
    qDebug() << "total time: " << qtime.elapsed()/1000.0 << "s";
    //数据展示到界面
    ui->file_text_1->setText(path);
    ui->listWidget_1->addItems(m_fileNames1);
}
/*
    打开文件2
*/
void MainWindow::on_btn_open_6_clicked()
{
    ui->listWidget_2->clear();
    m_fileNames2.clear();
    QString path = m_md5.openDirectory();
    m_path = path;
    QTime qtime;
    qtime.start();
    getFilesInfo(Model::FILE2);
    qDebug() << "total time: " << qtime.elapsed()/1000.0 << "s";

    ui->file_text_2->setText(path);
    ui->listWidget_2->addItems(m_fileNames2);
}
/*
    比较文件
*/
void MainWindow::on_btn_compare_clicked()
{
    if(!m_compareNames.isEmpty())
        m_compareNames.clear();
    for(QMap<QString,QString>::iterator iter=m_map1.begin();iter!=m_map1.end();iter++)
    {
        for(QMap<QString,QString>::iterator iter2=m_map2.begin();iter2!=m_map2.end();iter2++)
        {
            if(iter.value() == iter2.value())
            {
//                qDebug() << __FUNCTION__ << __LINE__ << endl;
//                qDebug() << "Dir 1: " << __LINE__  << endl;
//                qDebug() << iter.key() << iter.value().toUtf8().toHex() << endl;
//                qDebug() << "Dir 2: " << __LINE__  << endl;
//                qDebug() << iter2.key() << iter2.value().toUtf8().toHex() << endl;
//                qDebug() << __FUNCTION__ << __LINE__ << endl;
                m_compareNames.append(iter2.key());
            }
        }
    }

    for(int i=0;i<ui->listWidget_2->count();i++)
    {
        if(!m_compareNames.contains(ui->listWidget_2->item(i)->text()))
        {
            qDebug() << ui->listWidget_2->item(i)->text() << endl;
            ui->listWidget_2->item(i)->setTextColor(QColor("red"));
        }
    }
}
