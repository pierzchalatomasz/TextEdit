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
#include <textblockuserdata.h>
#include <textblock.h>

TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    loadFile("test.html");
    syntaxHighlighter();

    Styles *stylesInit = new Styles();

    ui->menuBar->setStyleSheet("background: #fff; color: #333;");

 /*   QTextBlock block = ui->textEdit->textCursor().block();
    while(block.isValid())
    {
        QTextBlockUserData *openingsClosings = new QTextBlockUserData();
        block.setUserData(openingsClosings);

        // Testing
        QString testString = block.text() + "\n";
        ui->testingConsole->insertPlainText(testString);

        block = block.next();
    }

    /*TextBlock block = ui->textEdit->textCursor().block();
    while(block.isValid())
    {
        TextBlockUserData *openingsClosings = new TextBlockUserData;
        block.setUserData(openingsClosings);

        // Testing
        QString testString = block.text() + "\n";
        ui->testingConsole->insertPlainText(testString);

        block = block.next();
    }*/
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

    //lineHighlight.cursor.insertText("text");
    //cursor.insertText("test");
}

// Otwieranie nowego pliku
void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    loadFile(fileName);
    ui->tabWidget->addTab(new QTextEdit, fileName);
}

// Dodawanie znaczników
void TextEdit::on_textEdit_textChanged()
{
    QTextBlock currentLine = ui->textEdit->textCursor().block();

    currentLine.text();

    QRegExp expression("<div>");
    int index = currentLine.text().indexOf(expression);

    //TextBlockUserData *openingsClosings = new TextBlockUserData;
    //currentLine.setUserData(openingsClosings);

    QTextBlockUserData *openingsClosings = currentLine.userData();

    if (index >= 0 && currentLine.userState() == -1) {
        //openingsClosings->addOpening();
        //openingsClosings->addClosing();
        currentLine.setUserState(0);
        ui->textEdit->textCursor().insertText("\n\n");
        ui->textEdit->textCursor().insertText("</div>");
        ui->textEdit->moveCursor(QTextCursor::Up);
        ui->textEdit->textCursor().insertText("\t");
        currentLine.setUserState(-1);
    }
}
