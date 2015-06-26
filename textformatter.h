#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H
#include <QTextEdit>
#include <QTextBlock>

class TextFormatter
{
public:
    TextFormatter();
    void lineHighlighter(QTextEdit *textEdit);
    void tabsInsideElements(QTextEdit *&textEdit);
    void elementsClosing(QTextEdit *&textEdit);
};

#endif // TEXTFORMATTER_H
