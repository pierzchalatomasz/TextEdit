#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QString>

namespace Ui {
class Notepad;
}

class Notepad : public QDialog
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = 0);
    ~Notepad();
    void setData(); //wczytuje notatkę z pliku
public slots:
    void saveData(); //zapisuje notatkę do pliku
private:
    Ui::Notepad *ui;
};

#endif // NOTEPAD_H
