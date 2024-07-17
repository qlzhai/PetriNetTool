/********************************************************************************
** Form generated from reading UI file 'NewMTSIWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMTSIWIDGET_H
#define UI_NEWMTSIWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMTSIWidgetClass
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *lineEditNumsMTSI;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textEditMTSIshow;

    void setupUi(QWidget *NewMTSIWidgetClass)
    {
        if (NewMTSIWidgetClass->objectName().isEmpty())
            NewMTSIWidgetClass->setObjectName("NewMTSIWidgetClass");
        NewMTSIWidgetClass->resize(600, 400);
        gridLayout_2 = new QGridLayout(NewMTSIWidgetClass);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(NewMTSIWidgetClass);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEditNumsMTSI = new QLineEdit(NewMTSIWidgetClass);
        lineEditNumsMTSI->setObjectName("lineEditNumsMTSI");

        horizontalLayout->addWidget(lineEditNumsMTSI);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        textEditMTSIshow = new QTextEdit(NewMTSIWidgetClass);
        textEditMTSIshow->setObjectName("textEditMTSIshow");

        gridLayout->addWidget(textEditMTSIshow, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(NewMTSIWidgetClass);

        QMetaObject::connectSlotsByName(NewMTSIWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *NewMTSIWidgetClass)
    {
        NewMTSIWidgetClass->setWindowTitle(QCoreApplication::translate("NewMTSIWidgetClass", "NewMTSIWidget", nullptr));
        label->setText(QCoreApplication::translate("NewMTSIWidgetClass", "MTSI\344\270\252\346\225\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMTSIWidgetClass: public Ui_NewMTSIWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMTSIWIDGET_H
