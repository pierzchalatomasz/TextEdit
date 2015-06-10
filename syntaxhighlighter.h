#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include "textedit.h"

class SyntaxHighlighter: public QSyntaxHighlighter
{

public:
    SyntaxHighlighter(QTextDocument* document): QSyntaxHighlighter(document)
    {};

    ~SyntaxHighlighter()
    {};

    void highlightBlock(const QString &text);
    void regExpFormatting(const QString &text, QString pattern, Qt::GlobalColor color );
};

#endif // SYNTAXHIGHLIGHTER_H
