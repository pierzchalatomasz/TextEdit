#include <file.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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

void File::save(QString str){
    QFile file(fileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&file);
    out<<str<<endl;
    file.close();
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
        QMessageBox sch ( "ERROR", "Blad otwarcia pliku.",
        QMessageBox::Warning,
        QMessageBox::Ok, 0, 0 );
        sch.exec();
        QString fail = "";
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
    else if(fileName.endsWith("txt"))
    {
        return 3;
    }
    else{
        QMessageBox sch ( "ERROR", "Edytor obsługuje pliki html, htm, css, txt",
        QMessageBox::Warning,
        QMessageBox::Ok, 0, 0 );
        sch.exec();
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

