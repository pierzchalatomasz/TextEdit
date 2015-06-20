#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>

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

    void on_textEdit_cursorPositionChanged();
    void on_textEdit_textChanged();

   // funkcje dla przycisków z menu
    void on_actionNewFile_triggered();
    void on_actionMenuCopy_triggered();
    void on_actionMenuCut_triggered();
    void on_actionMenuPaste_triggered();
    void on_actionMenuFont_triggered();
    void on_actionMenuUndo_triggered();
    void on_actionMenuRedo_triggered();
    void on_actionMenuSelectAll_triggered();
    void on_actionMenuSyntaxHighlighting_triggered();

private:
    Ui::TextEdit *ui;
    void loadFile( QString fileName );
    void checkFileType( QString fileName );
    void syntaxHighlighter();
};

#endif // TEXTEDIT_H
