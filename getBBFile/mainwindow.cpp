#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mf = new MakeFiles;
    fileName = "file";
    type = "txt";
    fileNUm = 20;
    fileSize = 10;
    initConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createBtn_clicked()
{
    ui->progressBar->setValue(0);
    fileName = ui->nameEdit->text();
    fileNUm = ui->numEdit->text().toInt();
    fileSize = ui->sizeEdit->text().toDouble();
    type    = ui->typeEdit->text();
    double realSize = fileSize * 1024 * 1000;
    allFilesCount = realSize * fileNUm;
    mf->writeTargetFiles(fileName,type,fileNUm,realSize);

}

void MainWindow::rcvProgress(int size)
{
    qDebug() << __FUNCTION__ << __LINE__ << size << allFilesCount <<endl;
    recSize += size;
    int tarSize = recSize / allFilesCount * 100;
    qDebug() << __FUNCTION__ << __LINE__ << tarSize << endl;
    ui->progressBar->setValue(tarSize);
}

void MainWindow::initConnection()
{
    connect(mf,&MakeFiles::sendProgress,this,&MainWindow::rcvProgress);
}

void MainWindow::on_pathBtn_clicked()
{
    QString localPath = QFileDialog::getExistingDirectory();
    ui->pathEdit->setText(localPath);
    mf->setSavePath(localPath);
    qDebug() << __FUNCTION__ << __LINE__ << localPath << endl;
}
