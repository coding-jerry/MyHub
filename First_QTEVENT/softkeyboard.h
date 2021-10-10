#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H

#include <QWidget>

namespace Ui {
class softKeyboard;
}

class softKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit softKeyboard(QWidget *parent = nullptr);
    ~softKeyboard();

    Ui::softKeyboard *getUi() const;

private:
    Ui::softKeyboard *ui;
};

#endif // SOFTKEYBOARD_H
