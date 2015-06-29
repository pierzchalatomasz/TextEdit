#include <file.h>
#include <QFile>
#include <QTextStream>

File::File(QString fileName) : file(fileName)
{
    file.open(QIODevice::ReadWrite);
    File::fileName = fileName;
}

// Otwiera plik w ostatniej karcie
void File::openInCard(QTabWidget *&tabWidget)
{
    int tabIndex = tabWidget->count();
    QList<QTextEdit *> allTextEdits = tabWidget->widget(tabIndex - 1)->findChildren<QTextEdit *>();
    QTextEdit *currentTextEdit = allTextEdits[0];

    currentTextEdit->setPlainText(this->getFileContent());
    // Przenieś na kartę z otwieranym plikiem
    tabWidget->setCurrentIndex(tabIndex - 1);
}

// Zwraca treść pliku
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

//sprawdzenie typu pliku
int File::checkFileType()
{
    if(fileName.endsWith("html")||fileName.endsWith("htm"))
    {
        return 1;
    }
    else if(fileName.endsWith("css"))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

//skraca nazwe pliku w kartach
QString File::cutFileName(){
    QString shortFileName;
    int lastIndex;

    lastIndex=fileName.lastIndexOf(QRegExp("/"));

    for(int i=lastIndex+1; i<fileName.length(); i++)
    {
        shortFileName=shortFileName+fileName[i];
    }
    return shortFileName;
}

File::~File()
{
    file.close();
}

