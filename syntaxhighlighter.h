#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextEdit>
#include "textedit.h"

class SyntaxHighlighter: public QSyntaxHighlighter
{

public:
    SyntaxHighlighter(QTextDocument* document): QSyntaxHighlighter(document)
    {};

    ~SyntaxHighlighter()
    {};

    void highlightBlock(const QString &text);
    void regExpFormatting(const QString &text, QString pattern, QColor color );
};

#endif // SYNTAXHIGHLIGHTER_H
