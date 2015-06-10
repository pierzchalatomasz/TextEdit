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

private:
    Ui::TextEdit *ui;
    void loadFile( QString fileName );
    void syntaxHighlighter();
};

#endif // TEXTEDIT_H
