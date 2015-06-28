#include "tabcontroller.h"

TabController::TabController()
{}

// Tworzy nową kartę (layout skopiowany z designera)
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

    QScrollArea *scrollArea = new QScrollArea(newTab);
    scrollArea->setObjectName(QStringLiteral("scrollArea"));
    scrollArea->setMaximumSize(QSize(30, 16777215));
    scrollArea->setStyleSheet(QStringLiteral("background: #494949;"));
    scrollArea->setWidgetResizable(true);

    QWidget *scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 30, 313));
    scrollArea->setWidget(scrollAreaWidgetContents);

    gridLayout->addWidget(scrollArea, 0, 0, 1, 1);


    QTextEdit *lineNumberArea = new QTextEdit(scrollArea);
    lineNumberArea->setObjectName(QStringLiteral("lineNumberArea"));
    lineNumberArea->setMaximumSize(QSize(30, 16777215));
    lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setAlignment(Qt::AlignRight);
    lineNumberArea->setFont(font1);

    newTab->setObjectName(QStringLiteral("tab"));
    newTab->setAcceptDrops(false);
    newTab->setStyleSheet(QLatin1String("background: #444;\n"
    "color: #fff;\n"
    "padding: 0;"));

    newTab->setLayout(gridLayout);
    tabWidget->addTab(newTab, fileName);
}

// tabWidget staje się referencją do ui->tabWidget
void TabController::init(QTabWidget *&getTabWidget)
{
    tabWidget = getTabWidget;
    tabWidget->setTabsClosable(true);
    QObject::connect(tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(onCloseTab()));
}

// zwraca wskaźnik do textEdit z otwartej karty
QTextEdit *TabController::currentTextEdit()
{
    int currentIndex = tabWidget->currentIndex();

    QList<QTextEdit *> allTextEdits = tabWidget->widget(currentIndex)->findChildren<QTextEdit *>("textEdit");
    QTextEdit *currentTextEdit = allTextEdits[0];

    return currentTextEdit;
}

// [~] zwraca wskaźnik do pola z numerami linii w otwartej karcie (niepoprawnie)
QTextEdit *TabController::currentLineNumberArea(){
    int currentIndex = tabWidget->currentIndex();

    QList<QTextEdit *> allLineNumberAreas = tabWidget->widget(currentIndex)->findChildren<QTextEdit *>("lineNumberArea");
    QTextEdit *currentLineNumberArea = allLineNumberAreas[0];

    return currentLineNumberArea;
}

// zamykanie karty
void TabController::onCloseTab()
{
    tabWidget->removeTab(tabWidget->currentIndex());
}

TabController::~TabController()
{}
