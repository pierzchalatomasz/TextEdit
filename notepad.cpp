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

    connect(ui->noteArea, SIGNAL(textChanged()),SLOT(saveData()));

    setData();
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::setData(){
    QFile file("notepadData.txt");
    QString text;
    file.open(QIODevice::ReadWrite);
    QTextStream textStream(&file);
    while(!textStream.atEnd())
        text += textStream.readLine();
    file.close();
    ui->noteArea->append(text);
}

void Notepad::saveData(){

    QFile file("notepadData.txt");
    QString text = ui->noteArea->toPlainText();
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<text<<endl;
    file.close();


}
