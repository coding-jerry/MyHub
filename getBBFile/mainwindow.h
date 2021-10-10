#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <makefiles.h>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_createBtn_clicked();
    void rcvProgress(int size);
    void on_pathBtn_clicked();

protected:
    void initConnection();
private:
    Ui::MainWindow *ui;
    MakeFiles *mf;
    QString fileName;
    QString type;
    int fileNUm;
    double fileSize;
    double allFilesCount;
    double recSize;
};
#endif // MAINWINDOW_H
