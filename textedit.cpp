﻿#include "textedit.h"
#include "ui_textedit.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDialog>
#include "syntaxhighlighter.h"
#include <QFileDialog>
#include <QBrush>
#include "styles.h"
#include "file.h"
#include <QFontDialog>
#include <QShortcut>
#include "textformatter.h"
#include <QTextDocument>
#include <QScrollBar>

int fileType;
TextEdit::TextEdit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);
    tabController.init(ui->tabWidget);
    setConnections();
    TextEdit::setWindowIcon(QIcon(":/icons/icons/pencil.png"));
    Styles *stylesInit = new Styles();
    ui->menuBar->setStyleSheet("background: #fff; color: #333;");
    ui->textEdit->setStyleSheet("QScrollBar:vertical { width: 5px; background: #333 !important; border: none !important; } QScrollBar::handle:vertical { background: #222 !important; border-radius: 5px; }");

    openUntitled();
}

TextEdit::~TextEdit()
{
    delete ui;
}

// Otwiera pierwszy plik
void TextEdit::openUntitled()
{
    ui->tabWidget->removeTab(0);

    QString fileName = "untitled.html";
    File file(fileName);

    tabController.newTab(fileName);
    file.openInCard(ui->tabWidget);

    syntaxHighlighter(file.checkFileType());
    connect(tabController.currentTextEdit(),SIGNAL(cursorPositionChanged()),this,SLOT(on_currentTextEdit_cursorPositionChanged()));
    setLineNumberArea();
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

    tabController.newTab(fileName);
    file.openInCard(ui->tabWidget);

    int typeOfFile = file.checkFileType();
    syntaxHighlighter(typeOfFile);
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
    // Dodawanie wcięć wewnątrz elementu
    textFormatter.tabsInsideElements(tabController.currentTextEdit());
}

// Zaznacza linię w której jest kursor (gdy pozycja kursora się zmienia)
void TextEdit::on_currentTextEdit_cursorPositionChanged()
{
    textFormatter.lineHighlighter(tabController.currentTextEdit());
}

// stworzenie nowego pliku
void TextEdit::on_actionNewFile_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    tabController.newTab(fileName);
    File file(fileName);
    file.openInCard(ui->tabWidget);
}

// Opcje wywoływane z menu
void TextEdit::on_actionPaste_triggered(){
    menu.paste(tabController.currentTextEdit());
}

void TextEdit::on_actionCopy_triggered(){
    menu.copy(tabController.currentTextEdit());
}

void TextEdit::on_actionCut_triggered(){
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

// wł/wył kolorowania składni
void TextEdit::on_actionMenuSyntaxHighlighting_triggered(){
    static int mode = 1; mode = (-1)*mode;
    QString name = tabController.currentFileName();

    if((!name.endsWith("css")) && (!name.endsWith("html")) && (!name.endsWith("htm")))
        return;
    if(mode == -1)
        menu.toggleSyntaxHighlighting(tabController.currentTextEdit());
    else
    {
        if(name.endsWith("css"))
            syntaxHighlighter(2); // kolorowanie dla CSS
        else
            syntaxHighlighter(1); // kolrowanie dla HTML
    }
}

void TextEdit::on_actionMenuZoomIn_triggered(){
    menu.zoomIn(tabController.currentTextEdit(), tabController.currentLineNumberArea());
}

void TextEdit::on_actionMenuZoomOut_triggered(){
    menu.zoomOut(tabController.currentTextEdit(),tabController.currentLineNumberArea());
}

void TextEdit::on_actionMenuInsertHTMLTemplate_triggered()
{
    menu.InsertHTMLTemplate(tabController.currentTextEdit());
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
    QShortcut *shortcutSaveAs = new QShortcut(QKeySequence("Ctrl+S"),this);
    connect(shortcutSaveAs,SIGNAL(activated()),ui->actionSaveAs,SLOT(trigger()));

    connect(tabController.currentTextEdit(),SIGNAL(cursorPositionChanged()),this,SLOT(on_currentTextEdit_cursorPositionChanged()));
    connect(tabController.currentTextEdit(),SIGNAL(textChanged()),this,SLOT(on_currentTextEdit_textChanged()));
}

void TextEdit::updateLineNumArea(int num){
    lineNumbering.updateLineNumberArea(tabController.currentLineNumberArea(), num);
}

// zapis pliku
void TextEdit::on_actionSave_triggered()
{
    File file(tabController.currentFileName());
    file.save(tabController.currentTextEdit());
}

// zapis pliku jako
void TextEdit::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    File file(fileName);
    file.save(tabController.currentTextEdit());
}

void TextEdit::on_actionMenuNotepad_triggered()
{
    Notepad *notepad = new Notepad(this);
    notepad->show();
}

void TextEdit::on_actionMenuColorPicker_triggered()
{
    ColorPicker *colorPicker = new ColorPicker(this);
    colorPicker->show();
}

