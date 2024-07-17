#include "PetriNetTool.h"

PetriNetTool::PetriNetTool(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowIcon(QIcon(":/image/icon1.png"));

	//新建petri net信息
	connect(ui.actionNewFile, &QAction::triggered, [=]() {
		NewFileWidget* nfw;
		nfw = new NewFileWidget(this);
		this->setCentralWidget(nfw);
		//判断确认按钮是否按下
		connect(nfw->ui.pushButtonOK, &QPushButton::clicked, [=]() {
			nfw->getNewInformation();//获取文本框信息
			//判断输入信息是否合法
			if (nfw->isComplete()) {
				//信息合法
				QString fileSaveName = QFileDialog::getSaveFileName(this, "保存文件", "", "文本文件 (*.txt);;所有文件 (*)");
				if (!fileSaveName.isEmpty()) {
					// 用户选择了文件并点击了保存按钮
					// 执行您的保存操作，将数据保存到指定文件 fileName 中
					// 例如，您可以使用 QFile 类来进行文件操作
					QFile file(fileSaveName);
					if (file.open(QIODevice::WriteOnly)) {
						QTextStream out(&file);
						out << "库所数量：" << nfw->numsPlace << "\n";
						out << "变迁数量：" << nfw->numsTransition << "\n";
						out << "关联矩阵：" << "\n";
						for (int i = 0; i < nfw->incidenceMatrix.size(); i++) {
							for (int j = 0; j < nfw->incidenceMatrix[i].size(); j++) {
								out << nfw->incidenceMatrix[i][j] << " ";
							}
							out << "\n";
						}
						out << "初始标记：" << "\n";
						for (int i = 0; i < nfw->initialMarking.size(); i++) {
							out << nfw->initialMarking[i] << " ";
						}
						out << "\n";
						file.close();
					}
				}
				else {
					// 用户取消了文件保存操作
				}
			}
			else {
				//输入信息不合法，弹出提示对话框
				QMessageBox::information(this, "提示", "输入信息有误，请检查后再提交！");
			}
			});
		//如果点击的是关闭按钮
		connect(nfw->ui.pushButtonNo, &QPushButton::clicked, this, &PetriNetTool::close);
		});

	//打开文件 关联矩阵
	connect(ui.action_openFile, &QAction::triggered, [=]() {
		this->openFile();
		//this->openFileIOMatrix();
		});

	//打开文件 ioMatrix
	connect(ui.action_openFileIOMatrix, &QAction::triggered, [=]() {
		//this->openFile();
		this->openFileIOMatrix();
		});

	//展示可达图
	connect(ui.action_ReachabilityGraph, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			//文件已经打开
			this->showReachableGraph();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示标识分类
	connect(ui.action_markingClass, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			//文件已经打开
			this->showMarkingClassification();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示TBDP问题的部分可达图
	connect(ui.action_partialRG, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showTBDPpartialGraph();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示TBDP问题的死锁预防条件
	connect(ui.action_DPconditions, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showTBDPdeadlockPrevectionCons();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示SRG
	connect(ui.actionSRG, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showSRG();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示P_invariant
	connect(ui.actionP_invariant, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showP_invariant();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示T_invariant
	connect(ui.actionT_invariant, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showT_invariant();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示信标
	connect(ui.actionSiphons, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showSiphons();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示极小信标
	connect(ui.actionMS, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showMinSiphons();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示严格极小信标
	connect(ui.actionSMS, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showSMS();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示基本信标
	connect(ui.actionESMS, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showESMS();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示基于SMS的死锁预防
	connect(ui.actionDPBasedSMS, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showDPBasedSMS();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示基于ESMS的死锁预防
	connect(ui.actionDPBasedESNS, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showDPBasedESMS();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示MTSI
	connect(ui.actionMTSI, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showMTSI();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});

	//展示基于区域理论的死锁预防
	connect(ui.actionDPBasedRegion, &QAction::triggered, [=]() {
		if (this->isopenFile) {
			this->showDPBasedRegion();
		}
		else {
			QMessageBox::critical(this, "提示", "请先打开一个文件！");
		}
		});
}

void PetriNetTool::getioMatrix() {
	vector<vector<int>> matrix = this->incidenceMatric_;

	//从输入的文件信息中解析出前置矩阵、后置矩阵以及初始标记
	vector<vector<int>> iVector(matrix.size(), vector<int>(matrix[0].size(), 0));
	vector<vector<int>> oVector(matrix.size(), vector<int>(matrix[0].size(), 0));
	MatrixXi imatrix(matrix.size(), matrix[0].size());
	MatrixXi omatrix(matrix.size(), matrix[0].size());
	VectorXi m0(matrix.size());
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (matrix[i][j] < 0) {
				iVector[i][j] = -matrix[i][j];
				imatrix(i, j) = -matrix[i][j];
				omatrix(i, j) = 0;
			}
			else {
				oVector[i][j] = matrix[i][j];
				omatrix(i, j) = matrix[i][j];
				imatrix(i, j) = 0;
			}
		}
	}
	for (int i = 0; i < this->incidenceMatric_.size(); i++) {
		m0(i) = this->m0_[i];
	}

	//生成TPN对象
	TPN::getInstance().input_matrix_ = imatrix;
	TPN::getInstance().output_matrix_ = omatrix;
	TPN::getInstance().m0_ = m0;

	vector<vector<string>> parametricTime(TPN::getInstance().num_of_trans_, vector<string>(2));

	for (int i = 0; i < TPN::getInstance().num_of_trans_; i++) {
		parametricTime[i][0] = "a" + to_string(i + 1);
		parametricTime[i][1] = "b" + to_string(i + 1);

		cout << parametricTime[i][0] << ", " << parametricTime[i][1] << endl;
	}

	TPN::getInstance().parametricTime = parametricTime;

	//生成PetriNet对象
	PetriNet::getInstance().input_matrix_ = imatrix;
	PetriNet::getInstance().output_matrix_ = omatrix;
	PetriNet::getInstance().m0_ = m0;
	PetriNet::getInstance().num_of_place_ = TPN::getInstance().num_of_place_;
	PetriNet::getInstance().num_of_trans_ = TPN::getInstance().num_of_trans_;
	PetriNet::getInstance().incidenceMatrix_ = this->incidenceMatric_;

	cout << "Data parsing completed" << endl;
}

void PetriNetTool::getioMatrixIO() {
	vector<vector<int>> imatrixV = this->imatrix_;
	vector<vector<int>> omatrixV = this->omatrix_;

	//从输入的文件信息中解析出前置矩阵、后置矩阵以及初始标记
	MatrixXi imatrix(imatrixV.size(), imatrixV[0].size());
	MatrixXi omatrix(omatrixV.size(), omatrixV[0].size());
	VectorXi m0(imatrixV.size());
	for (int i = 0; i < imatrixV.size(); i++) {
		for (int j = 0; j < imatrixV[0].size(); j++) {
			imatrix(i, j) = imatrixV[i][j];
			omatrix(i, j) = omatrixV[i][j];
		}
	}
	for (int i = 0; i < imatrixV.size(); i++) {
		m0(i) = this->m0_[i];
	}

	//关联矩阵
	vector<vector<int>> incidenceMatrix(imatrixV.size(), vector<int>(imatrixV[0].size()));
	for (int i = 0; i < imatrixV.size(); i++) {
		for (int j = 0; j < imatrixV[0].size(); j++) {
			incidenceMatrix[i][j] = omatrixV[i][j] = imatrixV[i][j];
		}
	}
	this->incidenceMatric_ = incidenceMatrix;


	//生成TPN对象
	TPN::getInstance().input_matrix_ = imatrix;
	TPN::getInstance().output_matrix_ = omatrix;
	TPN::getInstance().m0_ = m0;

	vector<vector<string>> parametricTime(TPN::getInstance().num_of_trans_, vector<string>(2));

	for (int i = 0; i < TPN::getInstance().num_of_trans_; i++) {
		parametricTime[i][0] = "a" + to_string(i + 1);
		parametricTime[i][1] = "b" + to_string(i + 1);

		cout << parametricTime[i][0] << ", " << parametricTime[i][1] << endl;
	}

	TPN::getInstance().parametricTime = parametricTime;

	//生成PetriNet对象
	PetriNet::getInstance().input_matrix_ = imatrix;
	PetriNet::getInstance().output_matrix_ = omatrix;
	PetriNet::getInstance().m0_ = m0;
	PetriNet::getInstance().num_of_place_ = TPN::getInstance().num_of_place_;
	PetriNet::getInstance().num_of_trans_ = TPN::getInstance().num_of_trans_;
	PetriNet::getInstance().incidenceMatrix_ = this->incidenceMatric_;

	cout << "Data parsing completed" << endl;
}

//初始化标志位信息为false
void PetriNetTool::initFlag() {
	this->isCalcuRG = false;
	this->isCalcuMarkingClass = false;
	this->isCalcuPartialGraph = false;
	this->isCalcuDPconditions = false;
	this->isCalcuSRG = false;
	this->isCalcuT_invariant = false;
	this->isCalcuP_invariant = false;
	this->isCalcuSiphons = false;
	this->isCalcuMS = false;
	this->isCalcuSMS = false;
	this->isCalcuESMS = false;
	this->isCalcuDPBasedSMS = false;
	this->isCalcuDPBasedESMS = false;
	this->isCalcuMTSI = false;
}
//打开文件
void PetriNetTool::openFile() {
	// 创建一个Qt应用程序对象
	QTextEdit* textEdit = new QTextEdit(this);
	//将文本框设置为不可编辑
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);

	// 设置初始文本内容
	QString path = QFileDialog::getOpenFileName(this, "打开文件", this->RelativePath);
	//读取内容
	QFile file1(path);
	//设置打开方式
	if (file1.open(QIODevice::ReadOnly)) {
		QByteArray context = file1.readAll();

		textEdit->setPlainText(context);

		file1.close();

		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			//cout << "无法打开文件" << endl;
			QMessageBox::information(this, "提示", "无法打开文件！");
		}

		// 创建一个文本流
		QTextStream in(&file);

		// 创建一个二维整数数组
		vector<vector<int>> numberArray;

		int numsLine = 1;
		QString line;
		// 使用正则表达式来匹配数字
		QRegularExpression re("-?\\d+(\\.\\d+)?");//正数以及负数
		QRegularExpressionMatchIterator matchIterator;

		//1.先读取一行，读出库所数量
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			TPN::getInstance().num_of_place_ = match.captured(0).toInt();
		}
		cout << TPN::getInstance().num_of_place_ << endl;

		//2.再读取一行，读出变迁数量
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			TPN::getInstance().num_of_trans_ = match.captured(0).toInt();
		}
		cout << TPN::getInstance().num_of_trans_ << endl;

		//3.从第四行读取，读取numsPlace行，读取关联矩阵
		line = in.readLine();//此时读取的是第三行	
		for (int i = 0; i < TPN::getInstance().num_of_place_; i++) {
			line = in.readLine();//从第四行开始读取
			vector<int> row;
			matchIterator = re.globalMatch(line);
			while (matchIterator.hasNext()) {
				QRegularExpressionMatch match = matchIterator.next();
				row.push_back(match.captured(0).toInt());
			}
			numberArray.push_back(row);
		}

		this->incidenceMatric_ = numberArray;

		//4.读取初始标记
		vector<int> marking;
		line = in.readLine();//此时读取的是初始标记文字这一行
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			marking.push_back(match.captured(0).toInt());
		}
		this->m0_ = marking;

		// 输出二维整数数组
		// 输出二维整数数组
		for (const vector<int>& row : numberArray)
		{
			for (int number : row)
			{
				cout << number << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < this->m0_.size(); i++) {
			cout << this->m0_[i] << " ";
		}
		cout << endl;

		this->getioMatrix();//在打开文件的时候就将IO矩阵的信息传递出去
		//更新文件打开的状态为true
		this->isopenFile = true;
		file.close();
		this->initFlag();//在打开文件的时候初始化标志位信息
	}
}

//打开文件，网模型为IO矩阵
void PetriNetTool::openFileIOMatrix() {
	// 创建一个Qt应用程序对象
	QTextEdit* textEdit = new QTextEdit(this);
	//将文本框设置为不可编辑
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);

	// 设置初始文本内容
	QString path = QFileDialog::getOpenFileName(this, "打开文件", this->RelativePath);
	//读取内容
	QFile file1(path);
	//设置打开方式
	if (file1.open(QIODevice::ReadOnly)) {
		QByteArray context = file1.readAll();

		textEdit->setPlainText(context);

		file1.close();

		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			cout << "无法打开文件" << endl;
			QMessageBox::information(this, "提示", "无法打开文件！");
		}

		// 创建一个文本流
		QTextStream in(&file);

		// 创建一个二维整数数组
		vector<vector<int>> imatrix;
		vector<vector<int>> omatrix;

		int numsLine = 1;
		QString line;
		// 使用正则表达式来匹配数字
		QRegularExpression re("-?\\d+(\\.\\d+)?");//正数以及负数
		QRegularExpressionMatchIterator matchIterator;

		//1.先读取一行，读出库所数量
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			TPN::getInstance().num_of_place_ = match.captured(0).toInt();
		}
		cout << TPN::getInstance().num_of_place_ << endl;

		//2.再读取一行，读出变迁数量
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			TPN::getInstance().num_of_trans_ = match.captured(0).toInt();
		}
		cout << TPN::getInstance().num_of_trans_ << endl;

		//3.从第四行读取，读取numsPlace行，读取imatrix
		line = in.readLine();//此时读取的是第三行	
		for (int i = 0; i < TPN::getInstance().num_of_place_; i++) {
			line = in.readLine();//从第四行开始读取
			vector<int> row;
			matchIterator = re.globalMatch(line);
			while (matchIterator.hasNext()) {
				QRegularExpressionMatch match = matchIterator.next();
				row.push_back(match.captured(0).toInt());
			}
			imatrix.push_back(row);
		}

		this->imatrix_ = imatrix;

		//4.再读取一行
		line = in.readLine();
		for (int i = 0; i < TPN::getInstance().num_of_place_; i++) {
			line = in.readLine();//从第四行开始读取
			vector<int> row;
			matchIterator = re.globalMatch(line);
			while (matchIterator.hasNext()) {
				QRegularExpressionMatch match = matchIterator.next();
				row.push_back(match.captured(0).toInt());
			}
			omatrix.push_back(row);
		}

		this->omatrix_ = omatrix;

		//4.读取初始标记
		vector<int> marking;
		line = in.readLine();//此时读取的是初始标记文字这一行
		line = in.readLine();
		matchIterator = re.globalMatch(line);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			marking.push_back(match.captured(0).toInt());
		}
		this->m0_ = marking;

		// 输出二维整数数组
		cout << "imatrix:" << endl;
		for (const vector<int>& row : imatrix)
		{
			for (int number : row)
			{
				cout << number << " ";
			}
			cout << endl;
		}

		cout << "omatrix:" << endl;
		for (const vector<int>& row : omatrix)
		{
			for (int number : row)
			{
				cout << number << " ";
			}
			cout << endl;
		}
		cout << "m0:" << endl;
		for (int i = 0; i < this->m0_.size(); i++) {
			cout << this->m0_[i] << " ";
		}
		cout << endl;

		this->getioMatrixIO();//在打开文件的时候就将IO矩阵的信息传递出去
		//更新文件打开的状态为true
		this->isopenFile = true;
		file.close();
		this->initFlag();//在打开文件的时候初始化标志位信息
	}
}

//展示可达图
void PetriNetTool::showReachableGraph() {
	if (this->isCalcuRG == false) {//没有计算过可达图
		bool res = ReachableGraph::getInstance().BuildReachabilityGraph();
		if (res) {//计算成功
			this->isCalcuRG = true;
		}
		else {
			QMessageBox::critical(this, "提示", "可达图计算失败！");
		}
	}
	vector<MarkingNode> nodes = ReachableGraph::getInstance().GetNodes();
	// 创建一个Qt应用程序对象
	QTextEdit* textEdit = new QTextEdit(this);
	//将文本框设置为不可编辑
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);
	//保持编辑器在光标最后一行
	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);
	unsigned int len = nodes.size();
	cout << "The reachability graph is calculated successfully!" << endl;
	cout << "The Petri net has a total of " << len << "markings!" << endl;
	textEdit->insertPlainText("一共有" + QString::number(len) + "个标记！\n");
	for (int kk = 0; kk < len; kk++) {
		textEdit->insertPlainText("node(" + QString::number(nodes[kk].node_name_) + ")\n");
		textEdit->insertPlainText("marking_" + QString::number(kk) + ": ");
		for (int i = 0; i < nodes[kk].marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(nodes[kk].marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");
		for (auto nn : nodes[kk].transition_to_son_) {
			textEdit->insertPlainText("  --[t_" + QString::number(nn.first + 1) + "]--> node(" + QString::number(nn.second) + ")\n");
		}
		textEdit->insertPlainText("\n");
	}
}

//展示标识分类
void PetriNetTool::showMarkingClassification() {
	vector<MarkingNode> deadMarkings = ReachableGraph::getInstance().getDeadMarkings();//死标记
	vector<MarkingNode> badMarkings = ReachableGraph::getInstance().getBadMarkings();//坏标记
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//危险标记
	vector<MarkingNode> goodMarkings = ReachableGraph::getInstance().getGoodMarkings();//好标记
	vector<MarkingNode> legalMarkings = ReachableGraph::getInstance().getLegalMarkings();// 合法标记

	if (deadMarkings.size() == 0 && badMarkings.size() == 0 && dangerousMarkings.size() == 0 && goodMarkings.size() == 0) {
		//没有进行过标识分类
		//判断是否进行过可达图计算
		if (this->isCalcuRG == false) {
			//没有进行过可达图计算，先计算可达图
			ReachableGraph::getInstance().BuildReachabilityGraph();
			this->isCalcuRG = true;
		}
		//进行标识分类
		ReachableGraph::getInstance().markingClassification();
		this->isCalcuMarkingClass = true;
	}

	deadMarkings = ReachableGraph::getInstance().getDeadMarkings();//死标记
	badMarkings = ReachableGraph::getInstance().getBadMarkings();//坏标记
	dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//危险标记
	goodMarkings = ReachableGraph::getInstance().getGoodMarkings();//好标记
	legalMarkings = ReachableGraph::getInstance().getLegalMarkings();// 合法标记

	cout << "there are " << dangerousMarkings.size() << " dangerousMarkings" << endl;
	cout << "there are " << legalMarkings.size() << " legal Markings!" << endl;
	// 创建一个Qt应用程序对象
	QTextEdit* textEdit = new QTextEdit(this);
	//将文本框设置为不可编辑
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);

	//保持编辑器在光标最后一行
	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);

	//显示死锁标记
	int numsDead = deadMarkings.size();
	textEdit->insertPlainText("一共有" + QString::number(numsDead) + "个死锁标记！\n");
	for (int kk = 0; kk < deadMarkings.size(); kk++) {
		textEdit->insertPlainText("node(" + QString::number(deadMarkings[kk].node_name_) + ")\n");
		textEdit->insertPlainText("marking_" + QString::number(kk) + ": ");
		for (int i = 0; i < deadMarkings[kk].marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(deadMarkings[kk].marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");

		for (auto nn : deadMarkings[kk].transition_to_son_) {
			textEdit->insertPlainText("  --[t_" + QString::number(nn.first + 1) + "]--> node(" + QString::number(nn.second) + ")\n");
		}
		textEdit->insertPlainText("\n");
	}

	//显示坏标记
	int numsBad = badMarkings.size();
	textEdit->insertPlainText("一共有" + QString::number(numsBad) + "个坏标记！\n");
	for (int kk = 0; kk < badMarkings.size(); kk++) {
		textEdit->insertPlainText("node(" + QString::number(badMarkings[kk].node_name_) + ")\n");
		textEdit->insertPlainText("marking_" + QString::number(kk) + ": ");
		for (int i = 0; i < badMarkings[kk].marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(badMarkings[kk].marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");

		for (auto nn : badMarkings[kk].transition_to_son_) {
			textEdit->insertPlainText("  --[t_" + QString::number(nn.first + 1) + "]--> node(" + QString::number(nn.second) + ")\n");
		}
		textEdit->insertPlainText("\n");
	}

	//显示危险标记
	int numsDangerous = dangerousMarkings.size();
	textEdit->insertPlainText("一共有" + QString::number(numsDangerous) + "个危险标记！\n");
	for (int kk = 0; kk < dangerousMarkings.size(); kk++) {
		textEdit->insertPlainText("node(" + QString::number(dangerousMarkings[kk].node_name_) + ")\n");
		textEdit->insertPlainText("marking_" + QString::number(kk) + ": ");
		for (int i = 0; i < dangerousMarkings[kk].marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(dangerousMarkings[kk].marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");

		for (auto nn : dangerousMarkings[kk].transition_to_son_) {
			textEdit->insertPlainText("  --[t_" + QString::number(nn.first + 1) + "]--> node(" + QString::number(nn.second) + ")\n");
		}
		textEdit->insertPlainText("\n");
	}

	//显示好标记
	int numsGood = goodMarkings.size();
	textEdit->insertPlainText("一共有" + QString::number(numsGood) + "个好标记！\n");
	for (int kk = 0; kk < goodMarkings.size(); kk++) {
		textEdit->insertPlainText("node(" + QString::number(goodMarkings[kk].node_name_) + ")\n");
		textEdit->insertPlainText("marking_" + QString::number(kk) + ": ");
		for (int i = 0; i < goodMarkings[kk].marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(goodMarkings[kk].marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");

		for (auto nn : goodMarkings[kk].transition_to_son_) {
			textEdit->insertPlainText("  --[t_" + QString::number(nn.first + 1) + "]--> node(" + QString::number(nn.second) + ")\n");
		}
		textEdit->insertPlainText("\n");
	}
}

//展示TBDP问题的部分可达图
void PetriNetTool::showTBDPpartialGraph() {
	//判断是否计算过可达图
	if (this->isCalcuRG == false) {
		ReachableGraph::getInstance().BuildReachabilityGraph();
		this->isCalcuRG = true;
	}
	//判断是否进行过标识分类
	if (this->isCalcuMarkingClass == false) {
		ReachableGraph::getInstance().markingClassification();
		this->isCalcuMarkingClass = true;
	}
	//获取危险标记集合
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();
	if (dangerousMarkings.size() == 0) {
		QMessageBox::critical(this, "提示", "此Petri网模型的TBDP问题无解或者该网模型无死锁");
	}
	else {
		if (this->isCalcuPartialGraph == false) {
			TBDP::getInstance().calculateAllPartialGraph();
			this->isCalcuPartialGraph = true;
		}
		vector<vector<PartialGraphNode>> allPartialGraphs = TBDP::getInstance().getAllPartialGraphs();
		vector<vector<int>> startNodes = TBDP::getInstance().getStartNodes();
		QTextEdit* textEdit = new QTextEdit(this);
		textEdit->setReadOnly(true);
		this->setCentralWidget(textEdit);
		QTextCursor cursor = textEdit->textCursor();
		cursor.movePosition(QTextCursor::End);
		textEdit->setTextCursor(cursor);
		textEdit->insertPlainText("一共有 " + QString::number(dangerousMarkings.size()) + " 个危险标记，因此一共有 " +
			QString::number(dangerousMarkings.size()) + " 个部分可达图\n ");
		for (int k = 0; k < allPartialGraphs.size(); k++) {
			int dangerousMarking_name = allPartialGraphs[k][0].node_name_;
			textEdit->insertPlainText("影响危险标记 M" + QString::number(dangerousMarking_name) + " 下使能变迁发射时间域的部分可达图如下：\n");
			for (int i = 0; i < allPartialGraphs[k].size(); i++) {
				cout << allPartialGraphs[k][i].node_name_ << endl;
				textEdit->insertPlainText("M" + QString::number(allPartialGraphs[k][i].node_name_) + "\n");
				textEdit->insertPlainText("trans: ");
				cout << "trans: ";
				for (int j = 0; j < allPartialGraphs[k][i].trans.size(); j++) {
					cout << allPartialGraphs[k][i].trans[j] << " ";
					textEdit->insertPlainText("t" + QString::number(allPartialGraphs[k][i].trans[j] + 1) + " ");
				}
				cout << endl;
				textEdit->insertPlainText("\n");
				cout << "tran_to_son: " << endl;
				textEdit->insertPlainText("tran_to_son: \n");
				for (int j = 0; j < allPartialGraphs[k][i].transition_to_son_.size(); j++) {
					cout << allPartialGraphs[k][i].transition_to_son_[j].first << " -> " << allPartialGraphs[k][i].transition_to_son_[j].second << endl;
					textEdit->insertPlainText("t" + QString::number(allPartialGraphs[k][i].transition_to_son_[j].first + 1) + " -> " + "M" + QString::number(allPartialGraphs[k][i].transition_to_son_[j].second) + "\n");
				}
				cout << endl;
				textEdit->insertPlainText("\n");
			}
			textEdit->insertPlainText("start nodes: ");
			for (int i = 0; i < startNodes[k].size(); i++) {
				textEdit->insertPlainText("M" + QString::number(startNodes[k][i]) + " ");
			}
			textEdit->insertPlainText("\n");
			textEdit->insertPlainText("\n");
		}
	}
}

//展示TBDO问题的死锁预防条件
void PetriNetTool::showTBDPdeadlockPrevectionCons() {
	//判断是否计算过可达图
	if (this->isCalcuRG == false) {
		ReachableGraph::getInstance().BuildReachabilityGraph();
		this->isCalcuRG = true;
	}
	//判断是否进行过标识分类
	if (this->isCalcuMarkingClass == false) {
		ReachableGraph::getInstance().markingClassification();
		this->isCalcuMarkingClass = true;
	}
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//获取危险标记集合
	if (dangerousMarkings.size() == 0) {
		QMessageBox::critical(this, "提示", "此Petri网模型的TBDP问题无解或者该网模型无死锁");
	}
	else {
		if (this->isCalcuPartialGraph == false) {//判断是否计算过TBDP问题的死锁预防条件
			TBDP::getInstance().calculateAllPartialGraph();
			this->isCalcuPartialGraph = true;
		}
		// 创建一个Qt应用程序对象
		QTextEdit* textEdit = new QTextEdit(this);
		//将文本框设置为不可编辑
		textEdit->setReadOnly(true);
		this->setCentralWidget(textEdit);
		//保持编辑器在光标最后一行
		QTextCursor cursor = textEdit->textCursor();
		cursor.movePosition(QTextCursor::End);
		textEdit->setTextCursor(cursor);
		vector<vector<PartialGraphNode>> allPartialGraphs = TBDP::getInstance().getAllPartialGraphs();
		vector<vector<int>> allStartNodes = TBDP::getInstance().getStartNodes();

		for (int i = 0; i < allPartialGraphs.size(); i++) {
			cout << "i am " << i << endl;
			int node_name = allPartialGraphs[i][0].node_name_;
			cout << node_name << endl;
			textEdit->insertPlainText("危险标记 M" + QString::number(node_name) + " 下的Delta如下：\n");
			cout << "findSingleGraphPath" << endl;
			TBDP::getInstance().findSingleGraphPath(allPartialGraphs[i], allStartNodes[i]);
			cout << "findMergepath" << endl;
			TBDP::getInstance().mergePath();
			vector<vector<PartialGraphNode>> singlePaths = TBDP::getInstance().getSinglePaths();
			for (int j = 0; j < singlePaths.size(); j++) {
				vector<SymbolicNode> nodesSRG = SymbolicGraph::getInstance().calculatePath(singlePaths[j]);
				for (auto transDelta : nodesSRG[nodesSRG.size() - 1].transitionDelta) {
					int t1 = transDelta.first.first;
					int t2 = transDelta.first.second;
					string delta1 = transDelta.second;
					QString delta2 = QString::fromStdString(delta1);
					textEdit->insertPlainText("(" + QString::number(t1) + "," + QString::number(t2) + "): " + delta2 + "\n");
				}
			}
			vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> pathsMapping = TBDP::getInstance().getPathsMapping();
			TBDP::getInstance().calculateCirclePathSRG(pathsMapping);
			vector<vector<string>> delta = TBDP::getInstance().getMapDelta_();
			for (auto transDelta : delta) {
				string t1 = transDelta[0];
				string t2 = transDelta[1];
				string s1 = transDelta[2];
				QString::fromStdString(s1);
				textEdit->insertPlainText("(" + QString::fromStdString(t1) + "," + QString::fromStdString(t2) + "): " + QString::fromStdString(s1) + "\n");
			}
			textEdit->insertPlainText("\n");
			textEdit->insertPlainText("\n");
		}
	}
}

//展示SRG
void PetriNetTool::showSRG() {
	if (this->isCalcuSRG == false) {
		SymbolicGraph::getInstance().buildGraph();
		this->isCalcuSRG = true;
	}
	vector<StateNode> nodes = SymbolicGraph::getInstance().getSRG();
	QTextEdit* textEdit = new QTextEdit(this);
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);
	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);
	cout << nodes.size() << endl;
	for (auto node : nodes) {
		cout << "state: " << node.node_name_ << ": " << node.marking_.transpose() << endl;
		textEdit->insertPlainText("state " + QString::number(node.node_name_) + " : ");
		for (int i = 0; i < node.marking_.rows(); i++) {
			textEdit->insertPlainText(QString::number(node.marking_(i)) + " ");
		}
		textEdit->insertPlainText("\n");
		std::cout << "Transition Delta:" << std::endl;
		textEdit->insertPlainText("Transition Delta:");
		textEdit->insertPlainText("\n");
		for (const auto& entry : node.transitionDelta_temp) {
			std::cout << "(" << entry.first.first + 1 << ", " << entry.first.second + 1 << "): " << entry.second << std::endl;

			textEdit->insertPlainText("(" + QString::number(entry.first.first + 1) + ", " + QString::number(entry.first.second + 1)
				+ "): " + QString::fromStdString(entry.second));
			textEdit->insertPlainText("\n");
		}
		std::cout << "Child Nodes:" << std::endl;
		textEdit->insertPlainText("Child Nodes:");
		textEdit->insertPlainText("\n");
		for (const auto& entry : node.tranSon) {
			std::cout << entry.first + 1 << " -> " << entry.second << std::endl; // Assuming printing pointer addresses
			textEdit->insertPlainText(QString::number(entry.first + 1) + " -> " + QString::number(entry.second));
			textEdit->insertPlainText("\n");
		}
		textEdit->insertPlainText("\n");
	}
}

//展示P_不变式
void PetriNetTool::showP_invariant() {
	if (this->isCalcuP_invariant == false) {
		StructuralPro::getInstance().computePInvariant(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuP_invariant = true;
	}
	vector<vector<int>> P_invariant = StructuralPro::getInstance().get_P_invariant();
	QTextEdit* textEditP_invariant = new QTextEdit(this);
	textEditP_invariant->setReadOnly(true);
	this->setCentralWidget(textEditP_invariant);
	textEditP_invariant->setPlainText("P_invariant\n");
	QTextCursor cursor = textEditP_invariant->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditP_invariant->setTextCursor(cursor);
	for (int i = 0; i < P_invariant.size(); i++) {
		for (int j = 0; j < P_invariant[0].size(); j++) {
			textEditP_invariant->insertPlainText(QString::number(P_invariant[i][j]) + " ");//textedit控件显示
			cout << P_invariant[i][j] << " ";//控制台输出
		}
		textEditP_invariant->insertPlainText("\n");
		cout << endl;
	}
}

//展示T_不变式
void PetriNetTool::showT_invariant() {
	if (this->isCalcuT_invariant == false) {
		StructuralPro::getInstance().computeTInvariant(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuT_invariant = true;
	}
	vector<vector<int>> P_invariant = StructuralPro::getInstance().get_T_invariant();
	QTextEdit* textEditP_invariant = new QTextEdit(this);
	textEditP_invariant->setReadOnly(true);
	this->setCentralWidget(textEditP_invariant);
	textEditP_invariant->setPlainText("T_invariant\n");
	QTextCursor cursor = textEditP_invariant->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditP_invariant->setTextCursor(cursor);
	for (int i = 0; i < P_invariant.size(); i++) {
		for (int j = 0; j < P_invariant[0].size(); j++) {
			textEditP_invariant->insertPlainText(QString::number(P_invariant[i][j]) + " ");//textedit控件显示
			cout << P_invariant[i][j] << " ";//控制台输出
		}
		textEditP_invariant->insertPlainText("\n");
		cout << endl;
	}
}

//展示信标
void PetriNetTool::showSiphons() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	vector<vector<int>> si = Siphon::getInstance().getSiphons();
	cout << "siphonCount: " << si.size() << endl;
	QTextEdit* textEditOriSiphon = new QTextEdit(this);
	textEditOriSiphon->setReadOnly(true);
	this->setCentralWidget(textEditOriSiphon);
	textEditOriSiphon->setPlainText("信标：\n");
	QTextCursor cursor = textEditOriSiphon->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditOriSiphon->setTextCursor(cursor);
	for (const auto& combination : si) {
		for (int num : combination) {
			textEditOriSiphon->insertPlainText("p" + QString::number(num + 1) + " ");//textedit控件显示
			cout << num + 1 << " ";
		}
		textEditOriSiphon->insertPlainText("\n");
		cout << std::endl;
	}
}

//展示极小信标
void PetriNetTool::showMinSiphons() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	if (this->isCalcuMS == false) {
		Siphon::getInstance().minSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuMS = true;
	}
	vector<vector<int>> si = Siphon::getInstance().getMinSiphons();
	QTextEdit* textEditMinSiphon = new QTextEdit(this);
	textEditMinSiphon->setReadOnly(true);
	this->setCentralWidget(textEditMinSiphon);
	textEditMinSiphon->setPlainText("极小信标：\n");
	QTextCursor cursor = textEditMinSiphon->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditMinSiphon->setTextCursor(cursor);
	for (const auto& combination : si) {
		for (int num : combination) {
			textEditMinSiphon->insertPlainText("p" + QString::number(num + 1) + " ");//textedit控件显示
			cout << num + 1 << " ";
		}
		textEditMinSiphon->insertPlainText("\n");
		cout << std::endl;
	}
}

//展示严格极小信标
void PetriNetTool::showSMS() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	if (this->isCalcuMS == false) {
		Siphon::getInstance().minSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuMS = true;
	}
	if (this->isCalcuSMS == false) {
		Siphon::getInstance().strictMinSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSMS = true;
	}
	vector<vector<int>> si = Siphon::getInstance().getSMS();
	QTextEdit* textEditStrictMinSiphon = new QTextEdit(this);
	textEditStrictMinSiphon->setReadOnly(true);
	this->setCentralWidget(textEditStrictMinSiphon);
	textEditStrictMinSiphon->setPlainText("严格极小信标：\n");
	QTextCursor cursor = textEditStrictMinSiphon->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditStrictMinSiphon->setTextCursor(cursor);
	for (int i = 0; i < si.size(); i++) {
		for (int j = 0; j < si[i].size(); j++) {
			if (si[i][j] != 0) {
				textEditStrictMinSiphon->insertPlainText("p" + QString::number(j + 1) + " ");//textedit控件显示
			}
			cout << si[i][j] << " ";
		}
		textEditStrictMinSiphon->insertPlainText("\n");
		cout << std::endl;
	}
}

//展示基本信标
void PetriNetTool::showESMS() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	if (this->isCalcuMS == false) {
		Siphon::getInstance().minSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuMS = true;
	}
	if (this->isCalcuSMS == false) {
		Siphon::getInstance().strictMinSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSMS = true;
	}
	if (this->isCalcuESMS == false) {
		Siphon::getInstance().elemSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuESMS = true;
	}
	vector<vector<int>> si = Siphon::getInstance().getESMS();
	QTextEdit* textEditElemSiphon = new QTextEdit(this);
	textEditElemSiphon->setReadOnly(true);
	this->setCentralWidget(textEditElemSiphon);
	textEditElemSiphon->setPlainText("基本信标：\n");
	QTextCursor cursor = textEditElemSiphon->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditElemSiphon->setTextCursor(cursor);
	for (int i = 0; i < si.size(); i++) {
		for (int j = 0; j < si[i].size(); j++) {
			if (si[i][j] != 0) {
				textEditElemSiphon->insertPlainText("p" + QString::number(j + 1) + " ");//textedit控件显示
			}
			cout << si[i][j] << " ";
		}
		textEditElemSiphon->insertPlainText("\n");
		cout << std::endl;
	}
}

//展示基于SMS的死锁预防
void PetriNetTool::showDPBasedSMS() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	if (this->isCalcuMS == false) {
		Siphon::getInstance().minSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuMS = true;
	}
	if (this->isCalcuSMS == false) {
		Siphon::getInstance().strictMinSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSMS = true;
	}
	if (this->isCalcuESMS == false) {
		Siphon::getInstance().elemSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuESMS = true;
	}

	if (this->isCalcuDPBasedSMS == false) {
		DeadlockPrevention::getInstance().SMSdeadlock();
		this->isCalcuDPBasedSMS = true;
	}
	QTextEdit* textEditDPSMS = new QTextEdit(this);
	textEditDPSMS->setReadOnly(true);
	this->setCentralWidget(textEditDPSMS);
	textEditDPSMS->setPlainText("基于严格极小信标的死锁预防\n");
	QTextCursor cursor = textEditDPSMS->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEditDPSMS->setTextCursor(cursor);
	textEditDPSMS->insertPlainText("受控后网的关联矩阵\n");
	vector<vector<int>> DPSMSmatrix = DeadlockPrevention::getInstance().getDPSMSmatrix();
	vector<int> DPSMSmarking = DeadlockPrevention::getInstance().getDPSMSmarking();
	for (int i = 0; i < DPSMSmatrix.size(); i++) {
		for (int j = 0; j < DPSMSmatrix[0].size(); j++) {
			textEditDPSMS->insertPlainText(QString::number(DPSMSmatrix[i][j]) + " ");
		}
		textEditDPSMS->insertPlainText("\n");
	}
	textEditDPSMS->insertPlainText("受控后网的初始标记\n");
	for (int i = 0; i < DPSMSmarking.size(); i++) {
		textEditDPSMS->insertPlainText(QString::number(DPSMSmarking[i]) + " ");
	}
}

//展示基于ESMS的死锁预防
void PetriNetTool::showDPBasedESMS() {
	if (this->isCalcuSiphons == false) {
		Siphon::getInstance().siphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSiphons = true;
	}
	if (this->isCalcuMS == false) {
		Siphon::getInstance().minSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuMS = true;
	}
	if (this->isCalcuSMS == false) {
		Siphon::getInstance().strictMinSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuSMS = true;
	}
	if (this->isCalcuESMS == false) {
		Siphon::getInstance().elemSiphons(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuESMS = true;
	}
	bool res = DeadlockPrevention::getInstance().ESMSdeadlock();
	if (res) {
		//死锁问题解决
		QTextEdit* textEditDPESMS = new QTextEdit(this);
		textEditDPESMS->setReadOnly(true);
		this->setCentralWidget(textEditDPESMS);
		textEditDPESMS->setPlainText("基于基本信标的死锁预防\n");
		QTextCursor cursor = textEditDPESMS->textCursor();
		cursor.movePosition(QTextCursor::End);
		textEditDPESMS->setTextCursor(cursor);
		textEditDPESMS->insertPlainText("受控后网的关联矩阵\n");
		vector<vector<int>> DPESMSmatrix = DeadlockPrevention::getInstance().getDPESMSmatrix();
		vector<int> DPESMSmarking = DeadlockPrevention::getInstance().getDPESMSmarking();
		for (int i = 0; i < DPESMSmatrix.size(); i++) {
			for (int j = 0; j < DPESMSmatrix[0].size(); j++) {
				textEditDPESMS->insertPlainText(QString::number(DPESMSmatrix[i][j]) + " ");
			}
			textEditDPESMS->insertPlainText("\n");
		}

		textEditDPESMS->insertPlainText("受控后网的初始标记\n");
		for (int i = 0; i < DPESMSmarking.size(); i++) {
			textEditDPESMS->insertPlainText(QString::number(DPESMSmarking[i]) + " ");
		}
	}
	else {
		//死锁没有解决
		QMessageBox::information(this, "提示", "无法使用ESMS进行死锁预防，请选择其他方式");
	}
}

//展示MTSI
void PetriNetTool::showMTSI() {
	if (this->isCalcuRG == false) {
		ReachableGraph::getInstance().BuildReachabilityGraph();
		this->isCalcuRG = true;
	}
	if (this->isCalcuMarkingClass == false) {
		ReachableGraph::getInstance().markingClassification();
		this->isCalcuMarkingClass = true;
	}
	vector<MarkingNode> deadMarkings = ReachableGraph::getInstance().getDeadMarkings();//死标记
	vector<MarkingNode> badMarkings = ReachableGraph::getInstance().getBadMarkings();//坏标记
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//危险标记
	vector<MarkingNode> goodMarkings = ReachableGraph::getInstance().getGoodMarkings();//好标记
	vector<MarkingNode> legalMarkings = ReachableGraph::getInstance().getLegalMarkings();// 合法标记
	if (this->isCalcuMTSI == false) {
		DeadlockPrevention::getInstance().calcuMTSI(dangerousMarkings, badMarkings, deadMarkings);
		this->isCalcuMTSI = true;
	}
	vector<pair<int, int>> v = DeadlockPrevention::getInstance().getMTSI();
	NewMTSIWidget* nmtsi = new NewMTSIWidget(this);
	//清空文本框内容，并设置为不可编辑的状态
	if (nmtsi->ui.lineEditNumsMTSI->text().isEmpty()) {
		nmtsi->ui.lineEditNumsMTSI->setText("");
		nmtsi->ui.lineEditNumsMTSI->setReadOnly("true");
	}
	if (nmtsi->ui.textEditMTSIshow->document()->isEmpty()) {
		nmtsi->ui.textEditMTSIshow->setText("");
		nmtsi->ui.textEditMTSIshow->setReadOnly("true");
	}
	this->setCentralWidget(nmtsi);
	cout << "MTSI:" << endl;
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << "   " << v[i].second << endl;
	}
	int numsMTSI = v.size();
	nmtsi->ui.lineEditNumsMTSI->setText(QString::number(numsMTSI));//输出MTSI数量
	nmtsi->ui.textEditMTSIshow->setPlainText("标识\t变迁\n");//\t表示水平制表，跳到下一个Tab位置
	QTextCursor cursor1 = nmtsi->ui.textEditMTSIshow->textCursor();
	cursor1.movePosition(QTextCursor::End);
	nmtsi->ui.textEditMTSIshow->setTextCursor(cursor1);
	for (int i = 0; i < numsMTSI; i++) {
		nmtsi->ui.textEditMTSIshow->insertPlainText("M" + QString::number(v[i].first) + "\tt" + QString::number(v[i].second) + "\n");
	}
}

//展示基于区域理论的死锁预防
void PetriNetTool::showDPBasedRegion() {
	if (this->isCalcuT_invariant == false) {
		StructuralPro::getInstance().computeTInvariant(PetriNet::getInstance().incidenceMatrix_);
		this->isCalcuT_invariant = true;
	}
	if (this->isCalcuRG == false) {
		ReachableGraph::getInstance().BuildReachabilityGraph();
		this->isCalcuRG = true;
	}
	if (this->isCalcuMarkingClass == false) {
		ReachableGraph::getInstance().markingClassification();
		this->isCalcuMarkingClass = true;
	}
	vector<MarkingNode> deadMarkings = ReachableGraph::getInstance().getDeadMarkings();//死标记
	vector<MarkingNode> badMarkings = ReachableGraph::getInstance().getBadMarkings();//坏标记
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//危险标记
	vector<MarkingNode> goodMarkings = ReachableGraph::getInstance().getGoodMarkings();//好标记
	vector<MarkingNode> legalMarkings = ReachableGraph::getInstance().getLegalMarkings();// 合法标记
	if (this->isCalcuMTSI == false) {
		DeadlockPrevention::getInstance().calcuMTSI(dangerousMarkings, badMarkings, deadMarkings);
		this->isCalcuMTSI = true;
	}

	cout << "theoryofregion:" << endl;
	TheoryOfRegion::getInstance().calculateLegalPath();
	TheoryOfRegion::getInstance().constraints();

	//获取T不变式条件，可达性条件以及禁止条件
	vector<string> T_InvariantsConditions_ = TheoryOfRegion::getInstance().getT_InvariantsConditions_();
	vector<string> iLegalConditions_ = TheoryOfRegion::getInstance().getiLegalConditions_();
	vector<vector<string>> legalConditions_ = TheoryOfRegion::getInstance().getlegalConditions_();

	// 创建一个Qt应用程序对象
	QTextEdit* textEdit = new QTextEdit(this);
	//将文本框设置为不可编辑
	textEdit->setReadOnly(true);
	this->setCentralWidget(textEdit);
	//保持编辑器在光标最后一行
	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	textEdit->setTextCursor(cursor);

	textEdit->insertPlainText("T_InvariantsConditions_:\n");
	for (int i = 0; i < T_InvariantsConditions_.size(); i++) {
		textEdit->insertPlainText(QString::fromStdString(T_InvariantsConditions_[i]) + ";\n");
	}
	textEdit->insertPlainText("\n");

	for (int i = 0; i < iLegalConditions_.size(); i++) {
		textEdit->insertPlainText("控制器" + QString::number(i + 1) + "的约束条件:\n");
		textEdit->insertPlainText(QString::fromStdString(iLegalConditions_[i]) + ";\n");
		for (int j = 0; j < legalConditions_[i].size(); j++) {
			textEdit->insertPlainText(QString::fromStdString(legalConditions_[i][j]) + ";\n");
		}
		textEdit->insertPlainText("\n");
		textEdit->insertPlainText("\n");
	}

	//在lingo中，默认变量为非负数，这里除了控制器的初始标记其余应该为任意数
	textEdit->insertPlainText("初始化变量为任意实数:\n");
	int nums = PetriNet::getInstance().num_of_trans_;
	for (int i = 0; i < nums; i++) {
		textEdit->insertPlainText("@free(t" + QString::number(i) + ");\n");
	}
}

void PetriNetTool::closeEvent(QCloseEvent* event) {
	QMessageBox::StandardButton btn = QMessageBox::question(this, "提示", "确认退出吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
	if (btn == QMessageBox::Yes) {
		event->accept();
	}
	else {
		event->ignore();
	}
}

PetriNetTool::~PetriNetTool()
{

}
