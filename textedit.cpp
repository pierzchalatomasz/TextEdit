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
#include <file.h>
#include <QFontDialog>
#include <QShortcut>
#include <textformatter.h>

int fileType;
TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    tabController.init(ui->tabWidget);

    File file("test.html");
    file.openInCard(ui->tabWidget);
    syntaxHighlighter();
    setConnections();

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
    if(fileType==1){
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);

    if( !file.error() )
    {
        QTextStream fileStream(&file);
        QString fileString = fileStream.readAll();

        Ui::TextEdit* newUi = new Ui::TextEdit;
        newUi->textEdit->setPlainText(fileString);
    }
    else
    {
        QDialog loadFileErrorDialog;
        loadFileErrorDialog.show();
        ui->textEdit->setPlainText("Niestety, nie udało się otworzyć pliku!");
    }
    }
    if(fileType==2){

    }
}

// Aktywuje kolorowanie składni
void TextEdit::syntaxHighlighter()
{
    SyntaxHighlighter* highlighter = new SyntaxHighlighter(tabController.currentTextEdit()->document());
}

//skraca nazwe pliku w kartach
QString TextEdit::cutFileName(QString fileName){
    QString shortFileName;
    int lastIndex;


    lastIndex=fileName.lastIndexOf(QRegExp("/"));

    for(int i=lastIndex+1; i<fileName.length(); i++){
        shortFileName=shortFileName+fileName[i];
    }
    return shortFileName;
}

//otwarcie pliku
void TextEdit::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    QString shortFileName=cutFileName(fileName);

    checkFileType(fileName);

    File file(fileName);
    tabController.newTab(shortFileName);
    file.openInCard(ui->tabWidget);

    syntaxHighlighter();
    textFormatter.lineHighlighter(tabController.currentTextEdit());
}

//sprawdzenie typu pliku
void TextEdit::checkFileType(QString fileName)
{
    if(fileName.endsWith("html")||fileName.endsWith("htm")){
        fileType=1;
    }
    else if(fileName.endsWith("css")){
        fileType=2;
    }
}

// Zaznacza linię w której jest kursor (gdy pozycja kursora się zmienia)
void TextEdit::on_textEdit_cursorPositionChanged()
{
    textFormatter.lineHighlighter(ui->textEdit);

    // Dodawanie tabów wewnątrz elementu
    textFormatter.tabsInsideElements(ui->textEdit);
}

// stworzenie nowego pliku
void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    tabController.newTab(fileName);
    File file(fileName);
    file.openInCard(ui->tabWidget);
}

//Obsługa poleceń z menu edycja
void TextEdit::on_actionMenuPaste_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_V, Qt::ControlModifier));
}

void TextEdit::on_actionMenuCopy_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier));
}

void TextEdit::on_actionMenuCut_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_X, Qt::ControlModifier));
}

void TextEdit::on_actionMenuUndo_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Z, Qt::ControlModifier));
}

void TextEdit::on_actionMenuRedo_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_Y, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_Y, Qt::ControlModifier));
}

void TextEdit::on_actionMenuSelectAll_triggered(){
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier));
    QApplication::postEvent( ui->textEdit, new QKeyEvent(QEvent::KeyRelease, Qt::Key_A, Qt::ControlModifier));
}

// Zamykanie znaczników
void TextEdit::on_textEdit_textChanged()
{
    textFormatter.elementsClosing(ui->textEdit);
}

// Wybór czcionki
void TextEdit::on_actionMenuFont_triggered(){
    bool font;
    QFont currentFont = ui->textEdit->currentFont();
    QFont selectedFont = QFontDialog::getFont(&font,currentFont,0,"Wybór czcionki");
    if(!font)
        return;
    else
        ui->textEdit->setFont(selectedFont);
}

// Włączenie i wyłączenie kolorowania składni
void TextEdit::on_actionMenuSyntaxHighlighting_triggered(){
    static int mode = 1; // kolorowanie wł = 1, wył = -1
    mode = -mode;

    if(mode == -1){
        foreach(QSyntaxHighlighter* highlighter,
                ui->textEdit->findChildren<QSyntaxHighlighter*>()) {
            delete highlighter;
        }

        QColor defaultcolor;
        defaultcolor.setRgb(60, 60, 60);
        ui->textEdit->setTextColor(defaultcolor);
    }
    else
        syntaxHighlighter();
}

// Obsługa zoom (menu)
void TextEdit::on_actionMenuZoomIn_triggered()
{
    ui->textEdit->zoomIn(2);
}

void TextEdit::on_actionMenuZoomOut_triggered()
{
    ui->textEdit->zoomOut(2);
}

// Aktywuje potrzebne połączenia sygnał -> slot
void TextEdit::setConnections(){
    QShortcut *shortcutZoomIn = new QShortcut(QKeySequence("Ctrl++"),this);
    connect(shortcutZoomIn,SIGNAL(activated()),ui->actionMenuZoomIn,SLOT(trigger()));
    QShortcut *shortcutZoomOut = new QShortcut(QKeySequence("Ctrl+-"),this);
    connect(shortcutZoomOut,SIGNAL(activated()),ui->actionMenuZoomOut,SLOT(trigger()));
    QShortcut *shortcutNewFile = new QShortcut(QKeySequence("Ctrl+N"),this);
    connect(shortcutNewFile,SIGNAL(activated()),ui->actionNewFile,SLOT(trigger()));
    QShortcut *shortcutOpenFile = new QShortcut(QKeySequence("Ctrl+O"),this);
    connect(shortcutOpenFile,SIGNAL(activated()),ui->actionOpenFile,SLOT(trigger()));
}

//zapisanie pliku
/*int save( const QString & input, const QString & s  )
 {
  FILE *fp;
  QString file = input;
  if ( (fp=fopen(s, "w")) != NULL ) {
     fputs(file, fp);
     fclose(fp);
     } else {
     QMessageBox sch ( "ERROR", "Blad otwarcia pliku.",
           QMessageBox::Warning,
           QMessageBox::Ok, 0, 0 );
     sch.exec();
     }
 return 0;
 }*/

//zapisywanie pliku jako..
void TextEdit::on_actionZapisz_triggered()
{

    QString str = ui->textEdit->toPlainText();
    QString fileName = QFileDialog::getSaveFileName();
    QFile file(fileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<str<<endl;
    file.close();
}
