/********************************************************************************
** Form generated from reading UI file 'BIlibiliComic.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILIBILICOMIC_H
#define UI_BILIBILICOMIC_H

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

class Ui_BIlibiliComicClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BIlibiliComicClass)
    {
        if (BIlibiliComicClass->objectName().isEmpty())
            BIlibiliComicClass->setObjectName(QStringLiteral("BIlibiliComicClass"));
        BIlibiliComicClass->resize(600, 400);
        menuBar = new QMenuBar(BIlibiliComicClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BIlibiliComicClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BIlibiliComicClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BIlibiliComicClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BIlibiliComicClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BIlibiliComicClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BIlibiliComicClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BIlibiliComicClass->setStatusBar(statusBar);

        retranslateUi(BIlibiliComicClass);

        QMetaObject::connectSlotsByName(BIlibiliComicClass);
    } // setupUi

    void retranslateUi(QMainWindow *BIlibiliComicClass)
    {
        BIlibiliComicClass->setWindowTitle(QApplication::translate("BIlibiliComicClass", "BIlibiliComic", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BIlibiliComicClass: public Ui_BIlibiliComicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILIBILICOMIC_H
