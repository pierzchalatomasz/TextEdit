#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);

    setWindowTitle("  ");
    setWindowFlags(Qt::Tool);

    setBaseSize(QSize(200,200));
    setStyleSheet("color: white; background-color: #272727");
    setMaximumWidth(600);
    setMaximumHeight(600);
}

Notepad::~Notepad()
{
    delete ui;
}
