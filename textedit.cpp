#include "textedit.h"
#include "ui_textedit.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDialog>
#include <syntaxhighlighter.h>
#include <QFileDialog>
#include <QBrush>
#include "styles.h"

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    loadFile("test.html");
    syntaxHighlighter();

    Styles *stylesInit = new Styles();

    ui->menuBar->setStyleSheet("background: #fff; color: #333;");
}

TextEdit::~TextEdit()
{
    delete ui;
}

// Ładuje plik
void TextEdit::loadFile(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);

    if( !file.error() )
    {
        QTextStream fileStream(&file);
        QString fileString = fileStream.readAll();

        ui->textEdit->setPlainText(fileString);
    }
    else
    {
        QDialog loadFileErrorDialog;
        loadFileErrorDialog.show();
        ui->textEdit->setPlainText("Niestety, nie udało się otworzyć pliku!");
    }
    QTextCursor textCursor = ui->textEdit->textCursor();
}

// Aktywuje kolorowanie składni
void TextEdit::syntaxHighlighter()
{
    SyntaxHighlighter* highlighter = new SyntaxHighlighter(ui->textEdit->document());
}

void TextEdit::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    loadFile(fileName);
}

// Zaznacza linię w której jest kursor (gdy pozycja kursora się zmienia)
void TextEdit::on_textEdit_cursorPositionChanged()
{

    QTextEdit::ExtraSelection lineHighlight;
    lineHighlight.cursor = ui->textEdit->textCursor();
    lineHighlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    lineHighlight.format.setBackground(Qt::gray);

    QList<QTextEdit::ExtraSelection> extras;
    extras << lineHighlight;
    ui->textEdit->setExtraSelections( extras );
}

void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    loadFile(fileName);
    ui->tabWidget->addTab(new QTextEdit, fileName);
}
