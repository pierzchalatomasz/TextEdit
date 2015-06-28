#ifndef MENU_H
#define MENU_H

#include <QTextEdit>
#include <QFontDialog>
#include <QSyntaxHighlighter>
#include <QApplication>

class Menu
{
public:
    Menu();

    // Edycja
    void paste(QTextEdit *editor);
    void copy(QTextEdit *editor);
    void cut(QTextEdit *editor);
    void undo(QTextEdit *editor);
    void redo(QTextEdit *editor);
    void selectAll(QTextEdit *editor);

    // Ustawienia
    void zoomIn(QTextEdit *editor);
    void zoomOut(QTextEdit *editor);
    void selectFont(QTextEdit *editor, QTextEdit *lineNum);
    void toggleSyntaxHighlighting(QTextEdit *editor);

};

#endif // MENU_H
