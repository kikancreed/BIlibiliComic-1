/********************************************************************************
** Form generated from reading UI file 'BIlibiliComic.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BIlibiliComicClass
{
public:
    QWidget *centralWidget;
    QLineEdit *savePathLineEdit;
    QPushButton *chooseSavePathBtn;
    QLabel *label;
    QLineEdit *comicIDLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *jumpCapLineEdit;
    QPushButton *startWorkBtn;
    QTextEdit *cookieTextEdit;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BIlibiliComicClass)
    {
        if (BIlibiliComicClass->objectName().isEmpty())
            BIlibiliComicClass->setObjectName(QStringLiteral("BIlibiliComicClass"));
        BIlibiliComicClass->resize(426, 190);
        centralWidget = new QWidget(BIlibiliComicClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        savePathLineEdit = new QLineEdit(centralWidget);
        savePathLineEdit->setObjectName(QStringLiteral("savePathLineEdit"));
        savePathLineEdit->setGeometry(QRect(100, 40, 211, 20));
        chooseSavePathBtn = new QPushButton(centralWidget);
        chooseSavePathBtn->setObjectName(QStringLiteral("chooseSavePathBtn"));
        chooseSavePathBtn->setGeometry(QRect(330, 40, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 71, 16));
        comicIDLineEdit = new QLineEdit(centralWidget);
        comicIDLineEdit->setObjectName(QStringLiteral("comicIDLineEdit"));
        comicIDLineEdit->setGeometry(QRect(100, 10, 211, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 81, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 81, 16));
        jumpCapLineEdit = new QLineEdit(centralWidget);
        jumpCapLineEdit->setObjectName(QStringLiteral("jumpCapLineEdit"));
        jumpCapLineEdit->setGeometry(QRect(100, 70, 211, 20));
        startWorkBtn = new QPushButton(centralWidget);
        startWorkBtn->setObjectName(QStringLiteral("startWorkBtn"));
        startWorkBtn->setGeometry(QRect(330, 120, 75, 23));
        cookieTextEdit = new QTextEdit(centralWidget);
        cookieTextEdit->setObjectName(QStringLiteral("cookieTextEdit"));
        cookieTextEdit->setGeometry(QRect(100, 100, 211, 61));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 130, 54, 12));
        BIlibiliComicClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BIlibiliComicClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 426, 23));
        BIlibiliComicClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BIlibiliComicClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BIlibiliComicClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BIlibiliComicClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BIlibiliComicClass->setStatusBar(statusBar);

        retranslateUi(BIlibiliComicClass);

        QMetaObject::connectSlotsByName(BIlibiliComicClass);
    } // setupUi

    void retranslateUi(QMainWindow *BIlibiliComicClass)
    {
        BIlibiliComicClass->setWindowTitle(QApplication::translate("BIlibiliComicClass", "BIlibiliComic", Q_NULLPTR));
        chooseSavePathBtn->setText(QApplication::translate("BIlibiliComicClass", "\351\200\211\346\213\251", Q_NULLPTR));
        label->setText(QApplication::translate("BIlibiliComicClass", "\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("BIlibiliComicClass", "\350\276\223\345\205\245\346\274\253\347\224\273ID\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("BIlibiliComicClass", "\350\267\263\347\253\240\344\270\213\350\275\275\357\274\232", Q_NULLPTR));
        jumpCapLineEdit->setText(QApplication::translate("BIlibiliComicClass", "0", Q_NULLPTR));
        startWorkBtn->setText(QApplication::translate("BIlibiliComicClass", "\345\274\200\345\247\213", Q_NULLPTR));
        label_4->setText(QApplication::translate("BIlibiliComicClass", "Cookie\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BIlibiliComicClass: public Ui_BIlibiliComicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILIBILICOMIC_H
