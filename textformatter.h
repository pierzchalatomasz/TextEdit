#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H
#include <QTextEdit>
#include <QTextBlock>
#include <QList>

class TextFormatter
{
public:
    TextFormatter();
    void lineHighlighter(QTextEdit *textEdit);
    void tabsInsideElements(QTextEdit *textEdit);
};

#endif // TEXTFORMATTER_H
