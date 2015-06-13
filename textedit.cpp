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

    TextEdit::setWindowIcon(QIcon(":/icons/icons/pencil.png"));

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
    QColor color;
    color.setRgb(60, 60, 60);
    QBrush brush(color);
    lineHighlight.format.setBackground(brush);

    QList<QTextEdit::ExtraSelection> extras;
    extras << lineHighlight;
    ui->textEdit->setExtraSelections( extras );

    // Dodawanie tabów wewnątrz elementu
    QTextBlock currentLine = ui->textEdit->textCursor().block();
    if(currentLine.text().isEmpty() && currentLine.userState() == -1)
    {
        QString tab = "\t";
        int tabsNumber = 0;
        int tabsCounter = currentLine.previous().text().indexOf(tab);

        while(tabsCounter >= 0)
        {
            tabsNumber++;
            tabsCounter = currentLine.previous().text().indexOf(tab, tabsCounter + tab.length());
        }

        QString tabs;
        int i = 0;
        while(i < tabsNumber)
        {
            tabs.append("\t");
            i++;
        }
        ui->textEdit->textCursor().insertText(tabs);
    }
}

// Otwieranie nowego pliku
void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    loadFile(fileName);
    ui->tabWidget->addTab(new QTextEdit, fileName);
}

//Obsługa poleceń z menu edycja
void TextEdit::on_actionPaste_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_V, Qt::ControlModifier));
}

void TextEdit::on_actionCopy_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier));
}

void TextEdit::on_actionCut_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_X, Qt::ControlModifier));
}

// Zamykanie znaczników
void TextEdit::on_textEdit_textChanged()
{
    QTextBlock currentLine = ui->textEdit->textCursor().block();

    currentLine.text();

    QRegExp expression("<div.*>");
    int index = currentLine.text().indexOf(expression);

    QTextBlockUserData *openingsClosings = currentLine.userData();

    if (index >= 0 && currentLine.userState() == -1) {
        currentLine.setUserState(0);
        currentLine.next().setUserState(0);

        QString tab = "\t";
        int tabsNumber = 0;
        int tabsCounter = currentLine.text().indexOf(tab);

        while(tabsCounter >= 0)
        {
            tabsNumber++;
            tabsCounter = currentLine.text().indexOf(tab, tabsCounter + tab.length());
        }

        QString tabs;
        int i = 0;
        while(i < tabsNumber)
        {
            tabs.append("\t");
            i++;
        }

        ui->textEdit->textCursor().insertText("\n\n");
        ui->textEdit->textCursor().insertText(tabs);
        ui->textEdit->textCursor().insertText("</div>");
        ui->textEdit->moveCursor(QTextCursor::Up);
        //ui->textEdit->textCursor().insertText(tabs);
        ui->textEdit->textCursor().insertText("\t");

        currentLine.setUserState(1);
    }
}
