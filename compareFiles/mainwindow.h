#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "filecalltomd5.h"
#include <QMap>
#include <time.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum Model{
    FILE1 = 0,
    FILE2,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getFilesInfo(Model);




private slots:
    void on_btn_open_5_clicked();

    void on_btn_open_6_clicked();

    void on_btn_compare_clicked();

private:
    Ui::MainWindow *ui;
    fileCallToMd5 m_md5;

    QString m_path;
    QStringList m_fileNames1;
    QStringList m_fileNames2;
    QStringList m_compareNames;
    QMap<QString,QString> m_map1;
    QMap<QString,QString> m_map2;
    bool isCleared;

};
#endif // MAINWINDOW_H
