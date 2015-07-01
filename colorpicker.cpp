#include "colorpicker.h"
#include "ui_colorpicker.h"
#include <QPalette>

ColorPicker::ColorPicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);

    setWindowTitle("  ");
    setWindowFlags(Qt::Tool);

    setStyleSheet("color:black; font: 13px Arial bold; background: white");

    setElements();
    setConnections();
    colorChanged();
}

ColorPicker::~ColorPicker()
{
    delete ui;
}

void ColorPicker::setElements(){

    ui->redSlider->setRange(0,255);
    ui->greenSlider->setRange(0,255);
    ui->blueSlider->setRange(0,255);

    ui->redValue->setRange(0,255);
    ui->greenValue->setRange(0,255);
    ui->blueValue->setRange(0,255);

    //ui->colorPreview->setReadOnly(true);
}

void ColorPicker::setConnections(){

    connect(ui->redSlider,SIGNAL(valueChanged(int)),SLOT(colorChanged()));
    connect(ui->greenSlider,SIGNAL(valueChanged(int)),SLOT(colorChanged()));
    connect(ui->blueSlider,SIGNAL(valueChanged(int)),SLOT(colorChanged()));

    connect(ui->redSlider,SIGNAL(valueChanged(int)),ui->redValue,SLOT(setValue(int)));
    connect(ui->greenSlider,SIGNAL(valueChanged(int)),ui->greenValue,SLOT(setValue(int)));
    connect(ui->blueSlider,SIGNAL(valueChanged(int)),ui->blueValue,SLOT(setValue(int)));

    connect(ui->redValue,SIGNAL(valueChanged(int)),ui->redSlider,SLOT(setValue(int)));
    connect(ui->greenValue,SIGNAL(valueChanged(int)),ui->greenSlider,SLOT(setValue(int)));
    connect(ui->blueValue,SIGNAL(valueChanged(int)),ui->blueSlider,SLOT(setValue(int)));
}

// maluje pole podglądu na wybrany kolor
void ColorPicker::colorChanged(){

    QString RGB = "rgb("
                + QString::number(ui->redSlider->value()) + ","
                + QString::number(ui->greenSlider->value()) + ","
                + QString::number(ui->blueSlider->value()) + ")";

    QString hexRed, hexGreen, hexBlue; //składowe koloru w zapisie szesnastkowym

   if((ui->redSlider->value())<16)
       hexRed = "0" + (QString::number(ui->redSlider->value(),16)).toUpper();
   else
       hexRed = (QString::number(ui->redSlider->value(),16)).toUpper();

   if((ui->greenSlider->value())<16)
       hexGreen = "0" + (QString::number(ui->greenSlider->value(),16)).toUpper();
   else
       hexGreen = (QString::number(ui->greenSlider->value(),16)).toUpper();

   if((ui->blueSlider->value())<16)
       hexBlue = "0" + (QString::number(ui->blueSlider->value(),16)).toUpper();
   else
       hexBlue = (QString::number(ui->blueSlider->value(),16)).toUpper();

    QString HEX = "#" + hexRed + hexGreen + hexBlue;

    ui->colorPreview->setStyleSheet("background-color:"+RGB);
    ui->rgbOutput->clear();
    ui->rgbOutput->setText(RGB);
    ui->hexOutput->clear();
    ui->hexOutput->setText(HEX);
}
