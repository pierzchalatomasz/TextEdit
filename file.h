#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QFile>
#include <QTextEdit>
#include <QTableWidget>

class File
{
public:
    File(QString fileName);
    ~File();
    QString getFileContent();
    void openInCard(QTabWidget *&tabWidget);
    int checkFileType();
    QString cutFileName();
private:
    QFile file;
    QString fileName;
};

#endif // FILE_H
