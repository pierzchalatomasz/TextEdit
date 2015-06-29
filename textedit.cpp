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
#include <QTextDocument>
#include <QScrollBar>

int fileType;
TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    tabController.init(ui->tabWidget);

    File file("test.html");
    file.openInCard(ui->tabWidget);
    syntaxHighlighter(1);
    setConnections();

    TextEdit::setWindowIcon(QIcon(":/icons/icons/pencil.png"));

    Styles *stylesInit = new Styles();

    ui->menuBar->setStyleSheet("background: #fff; color: #333;");
    ui->textEdit->setStyleSheet("QScrollBar:vertical { width: 5px; background: #333 !important; border: none !important; } QScrollBar::handle:vertical { background: #222 !important; border-radius: 5px; }");

    textFormatter.lineHighlighter(tabController.currentTextEdit());

    // Dodawanie tabów wewnątrz elementu
    //textFormatter.tabsInsideElements(tabController.currentTextEdit());
}

TextEdit::~TextEdit()
{
    delete ui;
}

// Aktywuje kolorowanie składni
void TextEdit::syntaxHighlighter(int fileType)
{
    SyntaxHighlighter* highlighter = new SyntaxHighlighter(tabController.currentTextEdit()->document());
    highlighter->setFileType(fileType);
}

//otwarcie pliku
void TextEdit::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    File file(fileName);
    QString shortFileName = file.cutFileName();

    tabController.newTab(shortFileName);
    file.openInCard(ui->tabWidget);

    syntaxHighlighter(file.checkFileType());
    connect(tabController.currentTextEdit(),SIGNAL(cursorPositionChanged()),this,SLOT(on_currentTextEdit_cursorPositionChanged()));
    setLineNumberArea();
}

void TextEdit::setLineNumberArea(){
    tabController.currentLineNumberArea()->setCursor(Qt::ArrowCursor);
    updateLineNumArea(tabController.currentTextEdit()->document()->blockCount());
    connect(tabController.currentTextEdit()->document(),SIGNAL(blockCountChanged(int)),this,SLOT(updateLineNumArea(int)));
    connect(tabController.currentTextEdit()->verticalScrollBar(),SIGNAL(valueChanged(int)),
            tabController.currentLineNumberArea()->verticalScrollBar(),SLOT(setValue(int)));
}

void TextEdit::on_currentTextEdit_textChanged()
{
    // Dodawanie tabów wewnątrz elementu
    textFormatter.tabsInsideElements(tabController.currentTextEdit());
}

// Zaznacza linię w której jest kursor (gdy pozycja kursora się zmienia)
void TextEdit::on_currentTextEdit_cursorPositionChanged()
{
    textFormatter.lineHighlighter(tabController.currentTextEdit());
    textFormatter.highlightBlock(tabController.currentTextEdit());

    //textFormatter.elementsClosing(tabController.currentTextEdit());
}

// stworzenie nowego pliku
void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    tabController.newTab(fileName);
    File file(fileName);
    file.openInCard(ui->tabWidget);
}

// Zamykanie znaczników
void TextEdit::on_textEdit_textChanged()
{
    textFormatter.elementsClosing(ui->textEdit);
}

// Opcje wywoływane z menu
void TextEdit::on_actionMenuPaste_triggered(){
    menu.paste(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuCopy_triggered(){
    menu.copy(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuCut_triggered(){
    menu.cut(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuUndo_triggered(){
    menu.undo(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuRedo_triggered(){
    menu.redo(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuSelectAll_triggered(){
    menu.selectAll(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuFont_triggered(){
    menu.selectFont(tabController.currentTextEdit(), tabController.currentLineNumberArea());
}

void TextEdit::on_actionMenuSyntaxHighlighting_triggered(){
    menu.toggleSyntaxHighlighting(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuZoomIn_triggered(){
    menu.zoomIn(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuZoomOut_triggered(){
    menu.zoomOut(tabController.currentTextEdit());
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

    connect(tabController.currentTextEdit(),SIGNAL(cursorPositionChanged()),this,SLOT(on_currentTextEdit_cursorPositionChanged()));
    connect(tabController.currentTextEdit(),SIGNAL(textChanged()),this,SLOT(on_currentTextEdit_textChanged()));
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

void TextEdit::updateLineNumArea(int num){
    lineNumbering.updateLineNumberArea(tabController.currentLineNumberArea(), num);
}
