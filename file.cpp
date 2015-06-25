#include <file.h>
#include <QFile>
#include <QTextStream>

File::File(QString fileName) : file(fileName)
{
    file.open(QIODevice::ReadWrite);
}

void File::openInCard(QTabWidget *&tabWidget)
{
    int tabIndex = tabWidget->count();
    QList<QTextEdit *> allTextEdits = tabWidget->widget(tabIndex - 1)->findChildren<QTextEdit *>();
    QTextEdit *currentTextEdit = allTextEdits[0];

    currentTextEdit->setPlainText(this->getFileContent());
    // Przenieś na kartę z otwieranym plikiem
    tabWidget->setCurrentIndex(tabIndex - 1);
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

