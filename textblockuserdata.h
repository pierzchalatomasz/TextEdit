#ifndef TEXTBLOCKUSERDATA_H
#define TEXTBLOCKUSERDATA_H
#include <QTextBlockUserData>

class TextBlockUserData: public QTextBlockUserData
{
public:
    TextBlockUserData();
    //TextBlockUserData(QTextBlockUserData*);
    void addOpening();
    void addClosing();
    bool compareOpeningClosing();
    //TextBlockUserData operator=(const QTextBlockUserData *);

private:
    int openings;
    int closings;
};

#endif // TEXTBLOCKUSERDATA_H
