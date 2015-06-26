#include "tabcontroller.h"

TabController::TabController()
{}

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

    newTab->setObjectName(QStringLiteral("tab"));
    newTab->setAcceptDrops(false);
    newTab->setStyleSheet(QLatin1String("background: #444;\n"
    "color: #fff;\n"
    "padding: 0;"));

    newTab->setLayout(gridLayout);
    tabWidget->addTab(newTab, fileName);
}

void TabController::init(QTabWidget *&getTabWidget)
{
    tabWidget = getTabWidget;
}

QTextEdit *TabController::currentTextEdit()
{
    int currentIndex = tabWidget->currentIndex();

    QList<QTextEdit *> allTextEdits = tabWidget->widget(currentIndex)->findChildren<QTextEdit *>();
    QTextEdit *currentTextEdit = allTextEdits[0];

    return currentTextEdit;
}
