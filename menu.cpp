#include "menu.h"
#include "textedit.h"

Menu::Menu()
{

}

void Menu::selectFont(QTextEdit *editor){
    bool font;
    QFont currentFont = editor->currentFont();
    QFont selectedFont = QFontDialog::getFont(&font,currentFont,0,"Wybór czcionki");
    if(!font)
        return;
    else
        editor->setFont(selectedFont);
}

void Menu::toggleSyntaxHighlighting(QTextEdit *editor){
    static int mode = 1; // kolorowanie wł = 1, wył = -1
    mode = -mode;

    if(mode == -1){
        foreach(QSyntaxHighlighter* highlighter,
                editor->findChildren<QSyntaxHighlighter*>()) {
            delete highlighter;
        }

        QColor defaultcolor;
        defaultcolor.setRgb(60, 60, 60);
        editor->setTextColor(defaultcolor);
    }
    //else
    //   editor->syntaxHighlighter();
}   //(??? czemu) syntaxHighlighter us not a member of 'QTextEdit'

void Menu::zoomIn(QTextEdit *editor){
    editor->zoomIn(2);
}

void Menu::zoomOut(QTextEdit *editor){
    editor->zoomOut(2);
}

//do poprawienia
void Menu::paste(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_V, Qt::ControlModifier));
}

void Menu::copy(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_C, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_C, Qt::ControlModifier));
}

void Menu::cut(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_X, Qt::ControlModifier));
}

void Menu::undo(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_Z, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_Z, Qt::ControlModifier));
}

void Menu::redo(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_Y, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_Y, Qt::ControlModifier));
}

void Menu::selectAll(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_A, Qt::ControlModifier));
}

