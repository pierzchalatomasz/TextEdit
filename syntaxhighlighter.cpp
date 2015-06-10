#include "syntaxhighlighter.h"

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // Elementy, np. <div>
    regExpFormatting( text, "</{0,1}[A-Za-z0-9_-]*[\\s]*[A-Za-z0-9-_.\"=\\s]*[^\\s]>", Qt::magenta );

    // id
    regExpFormatting( text, "id=", Qt::cyan );

    // class
    regExpFormatting( text, "class=", Qt::yellow );

    // Wewnątrz ""
    regExpFormatting( text, "\"[A-Za-z0-9-_\\s.]*\"", Qt::green );

    // Komentarze
    regExpFormatting( text, "<!--[\\s]*[A-Za-z0-9\\s]*[\\s]*-->", Qt::gray );
}

void SyntaxHighlighter::regExpFormatting( const QString &text, QString pattern, enum Qt::GlobalColor color )
{
    QTextCharFormat markup;
    markup.setForeground(color);

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, markup);
        index = text.indexOf(expression, index + length);
    }
}
