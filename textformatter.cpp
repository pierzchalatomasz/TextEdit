#include "textformatter.h"
#include <QKeyEvent>

TextFormatter::TextFormatter()
{}

// Podświetlanie aktualnej linii
void TextFormatter::lineHighlighter(QTextEdit *textEdit)
{
    QTextEdit::ExtraSelection lineHighlight;
    lineHighlight.cursor = textEdit->textCursor();
    lineHighlight.format.setProperty(QTextFormat::FullWidthSelection, true);
    QColor color;
    color.setRgb(60, 60, 60);
    QBrush brush(color);
    lineHighlight.format.setBackground(brush);

    QList<QTextEdit::ExtraSelection> extras;
    extras << lineHighlight;
    textEdit->setExtraSelections( extras );
}

// Wcięcia wewnątrz elementów
void TextFormatter::tabsInsideElements(QTextEdit *textEdit)
{
    QTextBlock currentLine = textEdit->textCursor().block();
    if(currentLine.text().isEmpty() && !currentLine.text().contains("\t") && currentLine.userState() == -1)
    {
        QString tab = "\t";
        int tabsNumber = 0;
        int tabsCounter = currentLine.previous().text().indexOf(tab);

        while(tabsCounter >= 0)
        {
            tabsNumber++;
            tabsCounter = currentLine.previous().text().indexOf(tab, tabsCounter + tab.length());
        }

        QString tabs;
        int i = 0;
        while(i < tabsNumber)
        {
            tabs.append("\t");
            i++;
        }
        textEdit->textCursor().insertText(tabs);
        currentLine.setUserState(0);
    }
}
