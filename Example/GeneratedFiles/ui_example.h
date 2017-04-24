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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExampleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExampleClass)
    {
        if (ExampleClass->objectName().isEmpty())
            ExampleClass->setObjectName(QStringLiteral("ExampleClass"));
        ExampleClass->resize(600, 400);
        menuBar = new QMenuBar(ExampleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ExampleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExampleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ExampleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ExampleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ExampleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ExampleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ExampleClass->setStatusBar(statusBar);

        retranslateUi(ExampleClass);

        QMetaObject::connectSlotsByName(ExampleClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExampleClass)
    {
        ExampleClass->setWindowTitle(QApplication::translate("ExampleClass", "Example", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExampleClass: public Ui_ExampleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXAMPLE_H
