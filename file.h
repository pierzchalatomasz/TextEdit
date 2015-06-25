#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QFile>

class File
{
public:
    File(QString fileName);
    ~File();
    QString getFileContent();
private:
    QFile file;
};

#endif // FILE_H
