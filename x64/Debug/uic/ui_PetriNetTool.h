/********************************************************************************
** Form generated from reading UI file 'PetriNetTool.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETRINETTOOL_H
#define UI_PETRINETTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetriNetToolClass
{
public:
    QAction *action_openFile;
    QAction *action_ReachabilityGraph;
    QAction *action_markingClass;
    QAction *action_partialRG;
    QAction *action_DPconditions;
    QAction *actionSRG;
    QAction *actionP_invariant;
    QAction *actionT_invariant;
    QAction *actionSiphons;
    QAction *actionMS;
    QAction *actionSMS;
    QAction *actionESMS;
    QAction *actionDPBasedSMS;
    QAction *actionDPBasedESNS;
    QAction *actionMTSI;
    QAction *actionNewFile;
    QAction *action_openFileIOMatrix;
    QAction *actionDPBasedRegion;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuTBDP;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menu_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PetriNetToolClass)
    {
        if (PetriNetToolClass->objectName().isEmpty())
            PetriNetToolClass->setObjectName("PetriNetToolClass");
        PetriNetToolClass->resize(600, 400);
        action_openFile = new QAction(PetriNetToolClass);
        action_openFile->setObjectName("action_openFile");
        action_ReachabilityGraph = new QAction(PetriNetToolClass);
        action_ReachabilityGraph->setObjectName("action_ReachabilityGraph");
        action_markingClass = new QAction(PetriNetToolClass);
        action_markingClass->setObjectName("action_markingClass");
        action_partialRG = new QAction(PetriNetToolClass);
        action_partialRG->setObjectName("action_partialRG");
        action_DPconditions = new QAction(PetriNetToolClass);
        action_DPconditions->setObjectName("action_DPconditions");
        actionSRG = new QAction(PetriNetToolClass);
        actionSRG->setObjectName("actionSRG");
        actionP_invariant = new QAction(PetriNetToolClass);
        actionP_invariant->setObjectName("actionP_invariant");
        actionT_invariant = new QAction(PetriNetToolClass);
        actionT_invariant->setObjectName("actionT_invariant");
        actionSiphons = new QAction(PetriNetToolClass);
        actionSiphons->setObjectName("actionSiphons");
        actionMS = new QAction(PetriNetToolClass);
        actionMS->setObjectName("actionMS");
        actionSMS = new QAction(PetriNetToolClass);
        actionSMS->setObjectName("actionSMS");
        actionESMS = new QAction(PetriNetToolClass);
        actionESMS->setObjectName("actionESMS");
        actionDPBasedSMS = new QAction(PetriNetToolClass);
        actionDPBasedSMS->setObjectName("actionDPBasedSMS");
        actionDPBasedESNS = new QAction(PetriNetToolClass);
        actionDPBasedESNS->setObjectName("actionDPBasedESNS");
        actionMTSI = new QAction(PetriNetToolClass);
        actionMTSI->setObjectName("actionMTSI");
        actionNewFile = new QAction(PetriNetToolClass);
        actionNewFile->setObjectName("actionNewFile");
        action_openFileIOMatrix = new QAction(PetriNetToolClass);
        action_openFileIOMatrix->setObjectName("action_openFileIOMatrix");
        actionDPBasedRegion = new QAction(PetriNetToolClass);
        actionDPBasedRegion->setObjectName("actionDPBasedRegion");
        centralWidget = new QWidget(PetriNetToolClass);
        centralWidget->setObjectName("centralWidget");
        PetriNetToolClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PetriNetToolClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName("menu_2");
        menuTBDP = new QMenu(menuBar);
        menuTBDP->setObjectName("menuTBDP");
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName("menu_3");
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName("menu_4");
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName("menu_5");
        PetriNetToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PetriNetToolClass);
        mainToolBar->setObjectName("mainToolBar");
        PetriNetToolClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PetriNetToolClass);
        statusBar->setObjectName("statusBar");
        PetriNetToolClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menuTBDP->menuAction());
        menu->addAction(action_openFile);
        menu->addAction(action_openFileIOMatrix);
        menu->addAction(actionNewFile);
        menu_2->addAction(action_ReachabilityGraph);
        menu_2->addAction(action_markingClass);
        menu_2->addAction(actionMTSI);
        menuTBDP->addAction(action_partialRG);
        menuTBDP->addAction(action_DPconditions);
        menuTBDP->addAction(actionSRG);
        menu_3->addAction(actionP_invariant);
        menu_3->addAction(actionT_invariant);
        menu_4->addAction(actionSiphons);
        menu_4->addAction(actionMS);
        menu_4->addAction(actionSMS);
        menu_4->addAction(actionESMS);
        menu_5->addAction(actionDPBasedSMS);
        menu_5->addAction(actionDPBasedESNS);
        menu_5->addAction(actionDPBasedRegion);

        retranslateUi(PetriNetToolClass);

        QMetaObject::connectSlotsByName(PetriNetToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *PetriNetToolClass)
    {
        PetriNetToolClass->setWindowTitle(QCoreApplication::translate("PetriNetToolClass", "PetriNetTool", nullptr));
        action_openFile->setText(QCoreApplication::translate("PetriNetToolClass", "\346\211\223\345\274\200\346\226\207\344\273\266(\345\205\263\350\201\224\347\237\251\351\230\265)", nullptr));
        action_ReachabilityGraph->setText(QCoreApplication::translate("PetriNetToolClass", "\345\217\257\350\276\276\345\233\276", nullptr));
        action_markingClass->setText(QCoreApplication::translate("PetriNetToolClass", "\346\240\207\350\257\206\345\210\206\347\261\273", nullptr));
        action_partialRG->setText(QCoreApplication::translate("PetriNetToolClass", "\351\203\250\345\210\206\345\217\257\350\276\276\345\233\276", nullptr));
        action_DPconditions->setText(QCoreApplication::translate("PetriNetToolClass", "\346\255\273\351\224\201\351\242\204\351\230\262\346\235\241\344\273\266", nullptr));
        actionSRG->setText(QCoreApplication::translate("PetriNetToolClass", "SRG", nullptr));
        actionP_invariant->setText(QCoreApplication::translate("PetriNetToolClass", "P_invariant", nullptr));
        actionT_invariant->setText(QCoreApplication::translate("PetriNetToolClass", "T_invariant", nullptr));
        actionSiphons->setText(QCoreApplication::translate("PetriNetToolClass", "\344\277\241\346\240\207", nullptr));
        actionMS->setText(QCoreApplication::translate("PetriNetToolClass", "\346\236\201\345\260\217\344\277\241\346\240\207", nullptr));
        actionSMS->setText(QCoreApplication::translate("PetriNetToolClass", "\344\270\245\346\240\274\346\236\201\345\260\217\344\277\241\346\240\207", nullptr));
        actionESMS->setText(QCoreApplication::translate("PetriNetToolClass", "\345\237\272\346\234\254\344\277\241\346\240\207", nullptr));
        actionDPBasedSMS->setText(QCoreApplication::translate("PetriNetToolClass", "\345\237\272\344\272\216SMS\347\232\204\346\255\273\351\224\201\351\242\204\351\230\262", nullptr));
        actionDPBasedESNS->setText(QCoreApplication::translate("PetriNetToolClass", "\345\237\272\344\272\216ESMS\347\232\204\346\255\273\351\224\201\351\242\204\351\230\262", nullptr));
        actionMTSI->setText(QCoreApplication::translate("PetriNetToolClass", "MTSI", nullptr));
        actionNewFile->setText(QCoreApplication::translate("PetriNetToolClass", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
        action_openFileIOMatrix->setText(QCoreApplication::translate("PetriNetToolClass", "\346\211\223\345\274\200\346\226\207\344\273\266(IOMatrix)", nullptr));
        actionDPBasedRegion->setText(QCoreApplication::translate("PetriNetToolClass", "\345\237\272\344\272\216\345\214\272\345\237\237\347\220\206\350\256\272\347\232\204\346\255\273\351\224\201\351\242\204\351\230\262", nullptr));
        menu->setTitle(QCoreApplication::translate("PetriNetToolClass", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("PetriNetToolClass", "\347\212\266\346\200\201\347\251\272\351\227\264\345\210\206\346\236\220", nullptr));
        menuTBDP->setTitle(QCoreApplication::translate("PetriNetToolClass", "TBDP", nullptr));
        menu_3->setTitle(QCoreApplication::translate("PetriNetToolClass", "\347\273\223\346\236\204\347\211\271\346\200\247", nullptr));
        menu_4->setTitle(QCoreApplication::translate("PetriNetToolClass", "\344\277\241\346\240\207\345\210\206\346\236\220", nullptr));
        menu_5->setTitle(QCoreApplication::translate("PetriNetToolClass", "\346\255\273\351\224\201\351\242\204\351\230\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetriNetToolClass: public Ui_PetriNetToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETRINETTOOL_H
