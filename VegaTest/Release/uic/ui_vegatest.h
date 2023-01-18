/********************************************************************************
** Form generated from reading UI file 'vegatest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEGATEST_H
#define UI_VEGATEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VegaTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VegaTestClass)
    {
        if (VegaTestClass->objectName().isEmpty())
            VegaTestClass->setObjectName(QString::fromUtf8("VegaTestClass"));
        VegaTestClass->resize(600, 400);
        menuBar = new QMenuBar(VegaTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        VegaTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VegaTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VegaTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(VegaTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        VegaTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VegaTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VegaTestClass->setStatusBar(statusBar);

        retranslateUi(VegaTestClass);

        QMetaObject::connectSlotsByName(VegaTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *VegaTestClass)
    {
        VegaTestClass->setWindowTitle(QCoreApplication::translate("VegaTestClass", "VegaTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VegaTestClass: public Ui_VegaTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEGATEST_H
