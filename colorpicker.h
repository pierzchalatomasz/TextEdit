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
    void setConnections();
    void setElements();

private slots:
    void colorChanged();

private:
    Ui::ColorPicker *ui;
};

#endif // COLORPICKER_H
