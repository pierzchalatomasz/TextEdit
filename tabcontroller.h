#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QTabWidget>
#include <QObject>
#include <QScrollBar>
#include <QApplication>

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
    QString currentFileName();
    QString cutFileName(QString fileName);
private:
    QTabWidget *tabWidget;
    QList<QString> fileNames;
    void saveFileName(QString fileName);
private slots:
    void onCloseTab();
};

#endif // TABCONTROLLER_H
