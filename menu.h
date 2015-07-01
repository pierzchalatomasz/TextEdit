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
    void zoomIn(QTextEdit *editor);
    void zoomOut(QTextEdit *editor);
    void selectFont(QTextEdit *editor, QTextEdit *lineNum);
    void toggleSyntaxHighlighting(QTextEdit *editor);

};

#endif // MENU_H
