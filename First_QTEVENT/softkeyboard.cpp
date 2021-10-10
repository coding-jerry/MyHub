#include "softkeyboard.h"
#include "ui_softkeyboard.h"

softKeyboard::softKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::softKeyboard)
{
    ui->setupUi(this);
}

softKeyboard::~softKeyboard()
{
    delete ui;
}

Ui::softKeyboard *softKeyboard::getUi() const
{
    return ui;
}
