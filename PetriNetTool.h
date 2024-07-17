#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PetriNetTool.h"

#include <QGuiApplication>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <qfiledialog.h>
#include <QStringList>
#include <qfile.h>
#include <qdebug.h>
#include <qstring.h>
#include <qvector.h>
#include <qregularexpression.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <queue>
#include <algorithm>
#include <QTextEdit>

#include "PetriNet.h"
#include "TPN.h"
#include "ReachableGraph.h"
#include "SymbolicGraph.h"
#include "TBDP.h"
#include "StructuralPro.h"
#include "Siphon.h"
#include "DeadlockPrevention.h"
#include "NewMTSIWidget.h"
#include "NewFileWidget.h"

#include "TheoryOfRegion.h"

using namespace std;
using namespace Eigen;

class PetriNetTool : public QMainWindow
{
	Q_OBJECT

public:
	PetriNetTool(QWidget* parent = nullptr);
	~PetriNetTool();
	bool isopenFile = false;//判断是否打开文件，默认状态是没有打开
	//打开文件，网模型为关联矩阵
	void openFile();
	//打开文件，网模型为IO矩阵
	void openFileIOMatrix();
	//展示可达图
	void showReachableGraph();
	//展示标识分类
	void showMarkingClassification();
	//展示TBDP问题的部分可达图
	void showTBDPpartialGraph();
	//展示TBDO问题的死锁预防条件
	void showTBDPdeadlockPrevectionCons();
	//展示SRG
	void showSRG();
	//展示P_不变式
	void showP_invariant();
	//展示T_不变式
	void showT_invariant();
	//展示信标
	void showSiphons();
	//展示极小信标
	void showMinSiphons();
	//展示严格极小信标
	void showSMS();
	//展示基本信标
	void showESMS();
	//展示基于SMS的死锁预防
	void showDPBasedSMS();
	//展示基于ESMS的死锁预防
	void showDPBasedESMS();
	//展示MTSI
	void showMTSI();
	//展示基于区域理论的死锁预防
	void showDPBasedRegion();
private:
	Ui::PetriNetToolClass ui;

	QString RelativePath = "D:\\桌面";//相对路径

	vector<vector<int>> incidenceMatric_;//关联矩阵

	vector<vector<int>> imatrix_;
	vector<vector<int>> omatrix_;

	vector<int> m0_;//初始标记

	bool isCalcuRG = false;//用于记录是否计算过可达图
	bool isCalcuMarkingClass = false;//用于记录是否进行过标识分类
	bool isCalcuPartialGraph = false;//用于记录是否计算过TBDP问题的部分可达图
	bool isCalcuDPconditions = false;//用于记录是否计算过TBDP问题的死锁预防条件
	bool isCalcuSRG = false;//用于记录是否计算过SRG
	bool isCalcuP_invariant = false;//用于记录是否计算过P_invariant
	bool isCalcuT_invariant = false;//用于记录是否计算过T_invariant
	bool isCalcuSiphons = false;//用于记录是否计算过信标
	bool isCalcuMS = false;//用于记录是否计算过极小信标
	bool isCalcuSMS = false;//用于记录是否计算过严格极小信标
	bool isCalcuESMS = false;//用于记录是否计算过基本信标
	bool isCalcuDPBasedSMS = false;//用于记录是否计算过基于SMS的死锁预防
	bool isCalcuDPBasedESMS = false;//用于记录是否计算过基于ESMS的死锁预防
	bool isCalcuMTSI = false;//用于记录是否计算过MTSI
	//解析文件信息 关联矩阵
	void getioMatrix();

	//解析文件信息 io矩阵
	void getioMatrixIO();

	//初始化标志位
	void initFlag();

protected:
	void closeEvent(QCloseEvent* event);
};
