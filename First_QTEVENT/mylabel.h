#ifndef MYLABEL_H
#define MYLABEL_H
#include<QWidget>
#include<QLabel>
#include<QEvent>
#include<QMouseEvent>
#include<QDebug>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget* parent = nullptr);
    ~MyLabel();

    bool event(QEvent *e) override;
};

#endif // MYLABEL_H
