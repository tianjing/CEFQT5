/********************************************************************************
** Form generated from reading UI file 'example.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXAMPLE_H
#define UI_EXAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExampleClass
{
public:
    QAction *action_2;
    QAction *action_test;
    QWidget *centralWidget;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuJs;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExampleClass)
    {
        if (ExampleClass->objectName().isEmpty())
            ExampleClass->setObjectName(QStringLiteral("ExampleClass"));
        ExampleClass->resize(600, 400);
        action_2 = new QAction(ExampleClass);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_test = new QAction(ExampleClass);
        action_test->setObjectName(QStringLiteral("action_test"));
        centralWidget = new QWidget(ExampleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setGeometry(QRect(50, 30, 511, 301));
        mdiArea->setFrameShape(QFrame::NoFrame);
        mdiArea->setViewMode(QMdiArea::SubWindowView);
        ExampleClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ExampleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuJs = new QMenu(menuBar);
        menuJs->setObjectName(QStringLiteral("menuJs"));
        ExampleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExampleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ExampleClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ExampleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ExampleClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuJs->menuAction());
        menu->addSeparator();
        menu->addAction(action_2);
        menuJs->addAction(action_test);

        retranslateUi(ExampleClass);

        QMetaObject::connectSlotsByName(ExampleClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExampleClass)
    {
        ExampleClass->setWindowTitle(QApplication::translate("ExampleClass", "Example", Q_NULLPTR));
        action_2->setText(QApplication::translate("ExampleClass", "\346\211\223\345\274\200\347\231\276\345\272\246", Q_NULLPTR));
        action_test->setText(QApplication::translate("ExampleClass", "\350\260\203\347\224\250test", Q_NULLPTR));
        menu->setTitle(QApplication::translate("ExampleClass", "\346\226\260\346\265\217\350\247\210\345\231\250", Q_NULLPTR));
        menuJs->setTitle(QApplication::translate("ExampleClass", "js", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExampleClass: public Ui_ExampleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMPLE_H
