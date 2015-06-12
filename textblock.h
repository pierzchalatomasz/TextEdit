#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H
#include <QTextBlock>
#include <textblockuserdata.h>

class TextBlock: public QTextBlock
{
public:
    TextBlock();
    TextBlock(const QTextBlock &block)
    {
        *this = block;
    }

    TextBlockUserData *userData()
    {
        return this->userData();
    }
    TextBlock &operator=(const QTextBlock textBlock)
    {
        *this = static_cast<TextBlock>(textBlock);
        return *this;
    }
};

#endif // TEXTBLOCK_H
