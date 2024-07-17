#include "NewFileWidget.h"

NewFileWidget::NewFileWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

bool NewFileWidget::getNewInformation() {
	this->numsPlace = ui.spinBoxPlace->value();
	this->numsTransition = ui.spinBoxTransition->value();

	vector<vector<int>> matrix(this->numsPlace, vector<int>(this->numsTransition, 0));
	//更新关联矩阵
	// 将文本框中的内容更新到下拉表中
	QTextDocument* docMatrix = ui.plainTextMatrix->document();
	int nCnt = docMatrix->blockCount();
	this->numsTextEdit = nCnt;
	// 使用正则表达式来匹配数字
	QRegularExpression re("-?\\d+(\\.\\d+)?");//正数以及负数
	QRegularExpressionMatchIterator matchIterator;
	for (int i = 0; i < nCnt; i++)
	{
		QTextBlock textBlock = docMatrix->findBlockByNumber(i);
		QString strtext = textBlock.text();
		//筛选出strtext中的数字，将其写入关联矩阵中
		matchIterator = re.globalMatch(strtext);
		vector<int> row;//创建一个vector数组，用来存储每一行的数据
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			row.push_back((match.captured(0).toInt()));
		}
		//保证row数组不为空
		if (row.size() != 0) {
			for (int j = 0; j < this->numsTransition; j++) {
				matrix[i][j] = row[j];
			}
		}
	}
	this->incidenceMatrix = matrix;

	//更新初始标记
	vector<int> mark(this->numsPlace);
	QString marking = ui.lineEditMarking->text();
	matchIterator = re.globalMatch(marking);
	int index = 0;
	while (matchIterator.hasNext()) {
		QRegularExpressionMatch match = matchIterator.next();
		mark[index++] = match.captured(0).toInt();
	}

	this->initialMarking = mark;
	this->numsLineText = this->initialMarking.size();
	return true;
}

bool NewFileWidget::isComplete() {
	//如果四个输入框中有一个为0.则说明没有输入完成
	if (this->numsPlace == 0 || this->numsTransition == 0 || this->numsTextEdit == 0 || this->numsLineText == 0)
		return false;
	//判断输入是否合法
	if (this->numsPlace != this->numsLineText || this->numsPlace != this->numsTextEdit || this->numsTransition != this->incidenceMatrix[0].size()) {
		return false;
	}
	//判断所输入的关联矩阵的每一行的数据个数是否等于变迁数
	for (int i = 0; i < incidenceMatrix.size(); i++) {
		if (this->numsTransition != incidenceMatrix[i].size()) {
			return false;
		}
	}
	return true;
}

NewFileWidget::~NewFileWidget()
{}
