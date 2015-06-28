#ifndef LINENUMBERING_H
#define LINENUMBERING_H
#include <QTextEdit>

class LineNumbering
{
public:
    LineNumbering();
    void updateLineNumberArea(QTextEdit *lineNumberArea, int num);
};

#endif // LINENUMBERING_H
