#ifndef LINENUMBERING_H
#define LINENUMBERING_H
#include <QTextEdit>

class LineNumbering
{
public:
    LineNumbering();
    void updateLineNumberArea(QTextEdit *lineNumberArea);
};

#endif // LINENUMBERING_H
