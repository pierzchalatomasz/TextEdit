#include "styles.h"
#include <QApplication>

Styles::Styles()
{
    qApp->setStyleSheet("QTabBar::tab, QTabBar::tab:first, QTabBar::tab:middle, QTabBar::tab:last, QTabBar::tab:previous--selected, QTabBar::tab:next-selected, QTabBar::tab:!selected { background-color: #555; padding: 10px 30px; border: none; color: #fff; }");
    qApp->setStyleSheet("QTabBar::tab:only-one { background-color: #555; padding: 10px 30px; border-right: 3px solid #219fd1; color: #fff; }");
    qApp->setStyleSheet("QTabBar::tab:selected { background-color: #555; padding: 10px 30px; border-right: 3px solid #219fd1; color: #fff; }");
}

