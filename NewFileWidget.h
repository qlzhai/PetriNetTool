#pragma once

#include <QWidget>
#include "ui_NewFileWidget.h"
#include <iostream>
#include <vector>
#include <qtextedit.h>
#include <QTextBlock>
#include <qdebug.h>

using namespace std;

class NewFileWidget : public QWidget
{
	Q_OBJECT

public:
	int numsPlace;
	int numsTransition;
	int numsTextEdit;
	int numsLineText;
	vector<vector<int>> incidenceMatrix;
	vector<int> initialMarking;

	NewFileWidget(QWidget* parent = nullptr);
	~NewFileWidget();

	bool getNewInformation();//获取文本框中的信息
	bool isComplete();//判断是否输入完成

	Ui::NewFileWidgetClass ui;
};
