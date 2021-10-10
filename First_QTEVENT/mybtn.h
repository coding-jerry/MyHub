#ifndef MYBTN_H
#define MYBTN_H
#include<QToolButton>
#include<QEvent>

class MyBtn : public QToolButton
{
    Q_OBJECT
public:
    MyBtn(QWidget *parent = nullptr);
    ~MyBtn();
    //bool event(QEvent *e) override;

private slots:
    void button_clicked(bool);
};

#endif // MYBTN_H
