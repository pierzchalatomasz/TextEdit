#include "textblockuserdata.h"
#include <QTextBlockUserData>

TextBlockUserData::TextBlockUserData()
{
    openings = 0;
    closings = 0;
}

void TextBlockUserData::addOpening()
{
    openings++;
}

void TextBlockUserData::addClosing()
{
    closings++;
}

bool TextBlockUserData::compareOpeningClosing()
{
    /*if( openings > closings )
    {
        return false;
    }
    else {
        return true;
    }*/
    if(closings > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
TextBlockUserData TextBlockUserData::operator=(const QTextBlockUserData *data)
{
    *this = &data;
    return *this;
}
*/


