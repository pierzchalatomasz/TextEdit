#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QDialog>
#include <QColor>

namespace Ui {
class ColorPicker;
}

class ColorPicker : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPicker(QWidget *parent = 0);
    ~ColorPicker();
    void setConnections(); // ustawia wymagane połączenia
    void setElements(); // formatuje elementy okna

private slots:
    void colorChanged(); // zmienia kolor okienka podglądu
                         // oraz wyświetla go jako rgb i hex
private:
    Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H
