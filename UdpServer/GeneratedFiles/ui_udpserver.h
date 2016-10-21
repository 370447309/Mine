/********************************************************************************
** Form generated from reading UI file 'udpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDPSERVER_H
#define UI_UDPSERVER_H

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

class Ui_UdpServerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UdpServerClass)
    {
        if (UdpServerClass->objectName().isEmpty())
            UdpServerClass->setObjectName(QStringLiteral("UdpServerClass"));
        UdpServerClass->resize(600, 400);
        menuBar = new QMenuBar(UdpServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        UdpServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UdpServerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UdpServerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(UdpServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        UdpServerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(UdpServerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UdpServerClass->setStatusBar(statusBar);

        retranslateUi(UdpServerClass);

        QMetaObject::connectSlotsByName(UdpServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *UdpServerClass)
    {
        UdpServerClass->setWindowTitle(QApplication::translate("UdpServerClass", "UdpServer", 0));
    } // retranslateUi

};

namespace Ui {
    class UdpServerClass: public Ui_UdpServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDPSERVER_H
