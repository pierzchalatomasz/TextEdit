#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QTabWidget>

class TabController
{
public:
    TabController();
    void newTab(QString fileName);
    void init(QTabWidget *&getTabWidget);
    QTextEdit *currentTextEdit();
private:
    QTabWidget *tabWidget;
};

#endif // TABCONTROLLER_H
