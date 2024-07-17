/********************************************************************************
** Form generated from reading UI file 'NewFileWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFILEWIDGET_H
#define UI_NEWFILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewFileWidgetClass
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPlace;
    QSpinBox *spinBoxPlace;
    QSpacerItem *horizontalSpacer;
    QLabel *labelTransition;
    QSpinBox *spinBoxTransition;
    QPushButton *pushButtonNo;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelMarking;
    QLineEdit *lineEditMarking;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonOK;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelMatrix;
    QPlainTextEdit *plainTextMatrix;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *NewFileWidgetClass)
    {
        if (NewFileWidgetClass->objectName().isEmpty())
            NewFileWidgetClass->setObjectName("NewFileWidgetClass");
        NewFileWidgetClass->resize(432, 452);
        gridLayout = new QGridLayout(NewFileWidgetClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(NewFileWidgetClass);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        labelPlace = new QLabel(widget);
        labelPlace->setObjectName("labelPlace");

        horizontalLayout->addWidget(labelPlace);

        spinBoxPlace = new QSpinBox(widget);
        spinBoxPlace->setObjectName("spinBoxPlace");

        horizontalLayout->addWidget(spinBoxPlace);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelTransition = new QLabel(widget);
        labelTransition->setObjectName("labelTransition");

        horizontalLayout->addWidget(labelTransition);

        spinBoxTransition = new QSpinBox(widget);
        spinBoxTransition->setObjectName("spinBoxTransition");

        horizontalLayout->addWidget(spinBoxTransition);


        gridLayout->addWidget(widget, 1, 2, 1, 1);

        pushButtonNo = new QPushButton(NewFileWidgetClass);
        pushButtonNo->setObjectName("pushButtonNo");

        gridLayout->addWidget(pushButtonNo, 4, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 4, 0, 1, 1);

        widget_3 = new QWidget(NewFileWidgetClass);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelMarking = new QLabel(widget_3);
        labelMarking->setObjectName("labelMarking");

        horizontalLayout_2->addWidget(labelMarking);

        lineEditMarking = new QLineEdit(widget_3);
        lineEditMarking->setObjectName("lineEditMarking");

        horizontalLayout_2->addWidget(lineEditMarking);


        gridLayout->addWidget(widget_3, 3, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 4, 2, 1, 1);

        pushButtonOK = new QPushButton(NewFileWidgetClass);
        pushButtonOK->setObjectName("pushButtonOK");

        gridLayout->addWidget(pushButtonOK, 4, 1, 1, 1);

        widget_2 = new QWidget(NewFileWidgetClass);
        widget_2->setObjectName("widget_2");
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        labelMatrix = new QLabel(widget_2);
        labelMatrix->setObjectName("labelMatrix");

        verticalLayout->addWidget(labelMatrix);

        plainTextMatrix = new QPlainTextEdit(widget_2);
        plainTextMatrix->setObjectName("plainTextMatrix");

        verticalLayout->addWidget(plainTextMatrix);


        gridLayout->addWidget(widget_2, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 4, 1, 1);


        retranslateUi(NewFileWidgetClass);

        QMetaObject::connectSlotsByName(NewFileWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *NewFileWidgetClass)
    {
        NewFileWidgetClass->setWindowTitle(QCoreApplication::translate("NewFileWidgetClass", "NewFileWidget", nullptr));
        labelPlace->setText(QCoreApplication::translate("NewFileWidgetClass", "\345\272\223\346\211\200\346\225\260\351\207\217\357\274\232", nullptr));
        labelTransition->setText(QCoreApplication::translate("NewFileWidgetClass", "\345\217\230\350\277\201\346\225\260\351\207\217\357\274\232", nullptr));
        pushButtonNo->setText(QCoreApplication::translate("NewFileWidgetClass", "\345\205\263\351\227\255", nullptr));
        labelMarking->setText(QCoreApplication::translate("NewFileWidgetClass", "\345\210\235\345\247\213\346\240\207\350\256\260\357\274\232", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("NewFileWidgetClass", "\347\241\256\350\256\244", nullptr));
        labelMatrix->setText(QCoreApplication::translate("NewFileWidgetClass", "\345\205\263\350\201\224\347\237\251\351\230\265\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewFileWidgetClass: public Ui_NewFileWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFILEWIDGET_H
