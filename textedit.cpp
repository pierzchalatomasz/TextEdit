#include "textedit.h"
#include "ui_textedit.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDialog>
#include <syntaxhighlighter.h>
#include <QFileDialog>

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    loadFile("test.html");
    syntaxHighlighter();
}

TextEdit::~TextEdit()
{
    delete ui;
}

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

void TextEdit::syntaxHighlighter()
{
    SyntaxHighlighter* highlighter = new SyntaxHighlighter(ui->textEdit->document());
}

void TextEdit::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    loadFile(fileName);
}

void TextEdit::on_textEdit_cursorPositionChanged()
{
    QTextEdit::ExtraSelection lineHighlight;
    lineHighlight.cursor = ui->textEdit->textCursor();
    lineHighlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    lineHighlight.format.setBackground( Qt::darkGray );

    QList<QTextEdit::ExtraSelection> extras;
    extras << lineHighlight;
    ui->textEdit->setExtraSelections( extras );
}
