#include "textformatter.h"

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

// Taby wewnątrz elementów
void TextFormatter::tabsInsideElements(QTextEdit *&textEdit)
{
    QTextBlock currentLine = textEdit->textCursor().block();
    if(currentLine.text().isEmpty() && currentLine.userState() == -1)
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
    }
}

// Zamykanie elementów
void TextFormatter::elementsClosing(QTextEdit *&textEdit)
{
    QTextBlock currentLine = textEdit->textCursor().block();

    currentLine.text();

    QRegExp expression("<div.*>");
    int index = currentLine.text().indexOf(expression);

    if (index >= 0 && currentLine.userState() == -1)
    {
        currentLine.setUserState(0);
        currentLine.next().setUserState(0);

        QString tab = "\t";
        int tabsNumber = 0;
        int tabsCounter = currentLine.text().indexOf(tab);

        while(tabsCounter >= 0)
        {
            tabsNumber++;
            tabsCounter = currentLine.text().indexOf(tab, tabsCounter + tab.length());
        }

        QString tabs;
        int i = 0;
        while(i < tabsNumber)
        {
            tabs.append("\t");
            i++;
        }

        textEdit->textCursor().insertText("\n\n");
        textEdit->textCursor().insertText(tabs);
        textEdit->textCursor().insertText("</div>");
        textEdit->moveCursor(QTextCursor::Up);
        textEdit->textCursor().insertText("\t");

        currentLine.setUserState(1);
    }
}
