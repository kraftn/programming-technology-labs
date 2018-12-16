/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_port1;
    QLineEdit *lineEdit_port2;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QLineEdit *lineEdit_IPAddress;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(262, 144);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        lineEdit_port1 = new QLineEdit(Dialog);
        lineEdit_port1->setObjectName(QStringLiteral("lineEdit_port1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_port1->sizePolicy().hasHeightForWidth());
        lineEdit_port1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_port1, 3, 0, 1, 1);

        lineEdit_port2 = new QLineEdit(Dialog);
        lineEdit_port2->setObjectName(QStringLiteral("lineEdit_port2"));
        sizePolicy1.setHeightForWidth(lineEdit_port2->sizePolicy().hasHeightForWidth());
        lineEdit_port2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_port2, 3, 1, 1, 1);

        pushButton_save = new QPushButton(Dialog);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_save->sizePolicy().hasHeightForWidth());
        pushButton_save->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButton_save, 4, 0, 1, 1);

        pushButton_cancel = new QPushButton(Dialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        sizePolicy2.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButton_cancel, 4, 1, 1, 1);

        lineEdit_IPAddress = new QLineEdit(Dialog);
        lineEdit_IPAddress->setObjectName(QStringLiteral("lineEdit_IPAddress"));
        sizePolicy1.setHeightForWidth(lineEdit_IPAddress->sizePolicy().hasHeightForWidth());
        lineEdit_IPAddress->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_IPAddress, 1, 0, 1, 2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog", "IP-\320\260\320\264\321\200\320\265\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260:", nullptr));
        label_2->setText(QApplication::translate("Dialog", "\320\237\320\276\321\200\321\202 1:", nullptr));
        label_3->setText(QApplication::translate("Dialog", "\320\237\320\276\321\200\321\202 2:", nullptr));
        pushButton_save->setText(QApplication::translate("Dialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_cancel->setText(QApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
