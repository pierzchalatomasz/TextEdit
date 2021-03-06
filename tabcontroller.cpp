#include "tabcontroller.h"

TabController::TabController()
{}

// tabWidget staje się referencją do ui->tabWidget
void TabController::init(QTabWidget *&getTabWidget)
{
    tabWidget = getTabWidget;
    tabWidget->setTabsClosable(true);
    QObject::connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(onCloseTab(int)));
}

// Tworzy nową kartę (layout z designera)
void TabController::newTab(QString fileName)
{
    QWidget *newTab = new QWidget;

    QGridLayout *gridLayout = new QGridLayout(newTab);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    QTextEdit *textEdit = new QTextEdit(newTab);
    textEdit->setObjectName(QStringLiteral("textEdit"));

    QFont font1;
    font1.setFamily(QStringLiteral("Consolas"));
    font1.setPointSize(11);
    textEdit->setFont(font1);
    textEdit->setStyleSheet(QLatin1String("border: none;\n"
    "background: #444;\n"
    "color: #ccc;"));
    textEdit->setTabStopWidth(20);
    textEdit->setProperty("currentIndex", QVariant(0));

    gridLayout->addWidget(textEdit, 0, 1, 1, 1);

    QTextEdit *lineNumberArea = new QTextEdit();
    lineNumberArea->setObjectName(QStringLiteral("lineNumberArea"));
    lineNumberArea->setMaximumSize(QSize(40, 16777215));
    lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setAlignment(Qt::AlignRight);
    lineNumberArea->setFont(font1);
    lineNumberArea->setReadOnly(true);
    lineNumberArea->verticalScrollBar()->setDisabled(1);
    lineNumberArea->setStyleSheet(QStringLiteral("background: #494949;"));

    gridLayout->addWidget(lineNumberArea, 0, 0, 1, 1);

    newTab->setObjectName(QStringLiteral("tab"));
    newTab->setAcceptDrops(false);
    newTab->setStyleSheet(QLatin1String("background: #444;\n"
    "color: #fff;\n"
    "padding: 0;"));

    newTab->setLayout(gridLayout);
    tabWidget->addTab(newTab, cutFileName(fileName));

    saveFileName(fileName);
}

void TabController::saveFileName(QString fileName)
{
    fileNames << fileName;
}

//skraca nazwe pliku w kartach
QString TabController::cutFileName(QString fileName){
    QString shortFileName;
    int lastIndex;

    lastIndex=fileName.lastIndexOf(QRegExp("/"));

    for(int i=lastIndex+1; i<fileName.length(); i++)
    {
        shortFileName=shortFileName+fileName[i];
    }
    return shortFileName;
}

// zwraca nazwę pliku z aktywnej karty
QString TabController::currentFileName()
{
    return fileNames.at(tabWidget->currentIndex());
}

// zwraca wskaźnik do textEdit z otwartej karty
QTextEdit *TabController::currentTextEdit()
{
    int currentIndex = tabWidget->currentIndex();

    QList<QTextEdit *> allTextEdits = tabWidget->widget(currentIndex)->findChildren<QTextEdit *>("textEdit");
    QTextEdit *currentTextEdit = allTextEdits[0];

    return currentTextEdit;
}

// zwraca wskaźnik do pola z numerami linii w otwartej karcie
QTextEdit *TabController::currentLineNumberArea()
{
    int currentIndex = tabWidget->currentIndex();

    QList<QTextEdit *> allLineNumberAreas = tabWidget->widget(currentIndex)->findChildren<QTextEdit *>("lineNumberArea");
    QTextEdit *currentLineNumberArea = allLineNumberAreas[0];

    return currentLineNumberArea;
}

// zamykanie karty
void TabController::onCloseTab(int index)
{
    QList<QTextEdit *> allLineNumberAreas = tabWidget->findChildren<QTextEdit *>("lineNumberArea");
    if(allLineNumberAreas.length() > 1)
    {
        QWidget *tab = tabWidget->widget(index);
        tabWidget->removeTab(index);
        delete tab;
        fileNames.removeAt(index);
    }
}

TabController::~TabController()
{}
