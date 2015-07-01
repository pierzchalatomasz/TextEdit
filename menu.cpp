#include "menu.h"
#include "textedit.h"
#include<QShortcut>

Menu::Menu()
{

}

void Menu::selectFont(QTextEdit *editor, QTextEdit *lineNum){
    bool font;
    QFont currentFont = editor->currentFont();
    QFont selectedFont = QFontDialog::getFont(&font,currentFont,0,"Wybór czcionki");
    if(!font)
        return;
    else{
        editor->setFont(selectedFont);
        lineNum->setFont(selectedFont);
    }
}

// wyłaczenie kolorowania składni, włączenie przebiega w textedit.cpp
void Menu::toggleSyntaxHighlighting(QTextEdit *editor){
        foreach(QSyntaxHighlighter* highlighter,
                editor->findChildren<QSyntaxHighlighter*>()) {
            delete highlighter;
        }
        QColor defaultcolor;
        defaultcolor.setRgb(60, 60, 60);
        editor->setTextColor(defaultcolor);
}

void Menu::zoomIn(QTextEdit *editor, QTextEdit *lineNum){
    editor->zoomIn(2);
    lineNum->zoomIn(2);
}

void Menu::zoomOut(QTextEdit *editor, QTextEdit *lineNum){
    editor->zoomOut(2);
    lineNum->zoomOut(2);
}

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
void Menu::save(QTextEdit *editor){
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyPress, Qt::Key_S, Qt::ControlModifier));
    QApplication::postEvent( editor, new QKeyEvent
                             (QEvent::KeyRelease, Qt::Key_S, Qt::ControlModifier));

}


// wstawia prosty szablon html
void Menu::InsertHTMLTemplate(QTextEdit *editor){
    editor->insertPlainText("<!DOCTYPE html>\n");
    editor->insertPlainText("<html>\n");
    editor->insertPlainText("<head>\n");
    editor->insertPlainText("\t<title></title>\n");
    editor->insertPlainText("\t<meta charset=\"UTF-8\">\n");
    //editor->insertPlainText("<link rel=\"stylesheet\" type=\"text/css\" href=\"\">\n");
    editor->insertPlainText("</head>\n");
    editor->insertPlainText("<body>\n");
    editor->insertPlainText("</body>\n");
    editor->insertPlainText("</html>");
}
