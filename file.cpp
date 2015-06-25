#include <file.h>
#include <QFile>
#include <QTextStream>

File::File(QString fileName) : file(fileName)
{
    file.open(QIODevice::ReadWrite);
}

QString File::getFileContent()
{
    if( !file.error() && file.exists() )
    {
        QTextStream fileStream(&file);
        QString fileString = fileStream.readAll();

        return fileString;
    }
    else
    {
        QString fail = "Nie udało się";
        return fail;
    }
}

File::~File()
{
    file.close();
}

