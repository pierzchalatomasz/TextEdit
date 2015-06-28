#include "linenumbering.h"
#include <QScrollBar>

LineNumbering::LineNumbering()
{

}

void LineNumbering::updateLineNumberArea(QTextEdit *lineNumberArea, int num){
    lineNumberArea->clear();
    for(int i = 1; i < num; ++i){
        //QString s = "ok";
        QString s = QString::number(i);
        lineNumberArea->append(s);
    }
    //tymczasowo
    lineNumberArea->verticalScrollBar()->setValue(0);
}

