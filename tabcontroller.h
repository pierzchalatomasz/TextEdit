#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QTabWidget>
#include <QObject>

class TabController : public QObject
{
    Q_OBJECT

public:
    TabController();
    ~TabController();
    void newTab(QString fileName);
    void init(QTabWidget *&getTabWidget);
    QTextEdit *currentTextEdit();
    QTextEdit *currentLineNumberArea();
private:
    QTabWidget *tabWidget;
private slots:
    void onCloseTab();
};

#endif // TABCONTROLLER_H
