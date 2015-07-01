#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <textformatter.h>
#include <tabcontroller.h>
#include <menu.h>
#include <linenumbering.h>
#include <notepad.h>
#include <colorpicker.h>

namespace Ui {
class TextEdit;
}

class TextEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEdit(QWidget *parent = 0);
    ~TextEdit();

private slots:
    void on_actionOpenFile_triggered();

    void on_currentTextEdit_cursorPositionChanged();
    void on_currentTextEdit_textChanged();
    void on_textEdit_textChanged();
    void updateLineNumArea(int num); //aktualizuje pole z numerami linii

   // funkcje dla przycisków z menu
    void on_actionNewFile_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionMenuFont_triggered();
    void on_actionMenuUndo_triggered();
    void on_actionMenuRedo_triggered();
    void on_actionMenuSelectAll_triggered();
    void on_actionMenuSyntaxHighlighting_triggered();
    void on_actionMenuZoomOut_triggered();
    void on_actionMenuZoomIn_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionMenuNotepad_triggered();
    void on_actionMenuColorPicker_triggered();

    void on_actionMenuInsertHTMLTemplate_triggered();

private:
    Ui::TextEdit *ui;
    void loadFile( QString fileName );
    void syntaxHighlighter(int fileType);
    void setConnections();
    void newTab(QString fileName);
    void setLineNumberArea();
    void openUntitled();

    TextFormatter textFormatter;
    TabController tabController;
    Menu menu;
    LineNumbering lineNumbering;
    Notepad *notepad;
    ColorPicker *colorPicker;
};

#endif // TEXTEDIT_H
