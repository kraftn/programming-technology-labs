/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_change;
    QAction *action_save;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QPushButton *pushButton_comeIn;
    QLabel *label_2;
    QTextEdit *textEdit_message;
    QLineEdit *lineEdit_enterName;
    QPushButton *pushButton_send;
    QLabel *label;
    QPushButton *pushButton_exit;
    QTextEdit *textEdit_chat;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(358, 302);
        action_change = new QAction(MainWindow);
        action_change->setObjectName(QStringLiteral("action_change"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QStringLiteral("action_save"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        pushButton_comeIn = new QPushButton(centralwidget);
        pushButton_comeIn->setObjectName(QStringLiteral("pushButton_comeIn"));

        gridLayout->addWidget(pushButton_comeIn, 1, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        textEdit_message = new QTextEdit(centralwidget);
        textEdit_message->setObjectName(QStringLiteral("textEdit_message"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit_message->sizePolicy().hasHeightForWidth());
        textEdit_message->setSizePolicy(sizePolicy);

        gridLayout->addWidget(textEdit_message, 5, 0, 1, 2);

        lineEdit_enterName = new QLineEdit(centralwidget);
        lineEdit_enterName->setObjectName(QStringLiteral("lineEdit_enterName"));

        gridLayout->addWidget(lineEdit_enterName, 1, 0, 1, 1);

        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_send->sizePolicy().hasHeightForWidth());
        pushButton_send->setSizePolicy(sizePolicy1);
        pushButton_send->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(pushButton_send, 5, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));

        gridLayout->addWidget(pushButton_exit, 1, 2, 1, 1);

        textEdit_chat = new QTextEdit(centralwidget);
        textEdit_chat->setObjectName(QStringLiteral("textEdit_chat"));
        textEdit_chat->setReadOnly(true);

        gridLayout->addWidget(textEdit_chat, 3, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 358, 17));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(action_change);
        menu->addAction(action_save);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_change->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        action_save->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\222\320\260\321\210\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265:", nullptr));
        pushButton_comeIn->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\247\320\260\321\202:", nullptr));
        pushButton_send->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\222\320\260\321\210\320\265 \320\270\320\274\321\217:", nullptr));
        pushButton_exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
