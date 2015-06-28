#include "syntaxhighlighter.h"

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // Elementy, np. <div>
    regExpFormatting( text, "</{0,1}[A-Za-z0-9_-]*[\\s]*[A-Za-z0-9-_.\"=\\s#;:]*[^\\s]>", QColor(160, 86, 255) );

    // id
    regExpFormatting( text, "id=", QColor(86, 136, 255) );

    // class
    regExpFormatting( text, "class=", QColor(249, 247, 142 ) );

    // Wewnątrz ""
    regExpFormatting( text, "\"[A-Za-z0-9-_\\s.;:#]*\"", QColor(72, 155, 70) );

    // Komentarze
    regExpFormatting( text, "<!--[\\s]*.*[\\s]*-->", Qt::gray );
}

// Kolorowanie określonego wyrażenia regularnego
void SyntaxHighlighter::regExpFormatting( const QString &text, QString pattern, QColor color )
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
