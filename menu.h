#ifndef MENU_H
#define MENU_H

#include <QTextEdit>
#include <QFontDialog>
#include <QSyntaxHighlighter>
#include <QApplication>
#include <QObject>

class Menu : public QObject
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
    void save(QTextEdit *editor);
    // Ustawienia
    void zoomIn(QTextEdit *editor, QTextEdit *lineNum);
    void zoomOut(QTextEdit *editor, QTextEdit *lineNum);
    void selectFont(QTextEdit *editor, QTextEdit *lineNum);
    void toggleSyntaxHighlighting(QTextEdit *editor);
    // Inne
    void InsertHTMLTemplate(QTextEdit *editor);

};

#endif // MENU_H
