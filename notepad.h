#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QDialog>

namespace Ui {
class Notepad;
}

class Notepad : public QDialog
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();
private:
    Ui::Notepad *ui;
};

#endif // NOTEPAD_H
