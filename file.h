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
private:
    QFile file;
};

#endif // FILE_H
