#include "textedit.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextEdit w;

    w.show();


    //mySyntaxHighLighter* highlighter = new mySyntaxHighLighter(edit->document());

    return a.exec();
}
