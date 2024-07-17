#include "DeadlockPrevention.h"

DeadlockPrevention& DeadlockPrevention::getInstance() {
	static DeadlockPrevention instance;
	return instance;
}

//计算死锁标记的数量
int DeadlockPrevention::numsDeadMarking(vector<int> marking, vector<vector<int>> matrix) {
	int numDead = 0;
	queue<vector<int>> q;  // 用于BFS的队列
	set<vector<int>> visited;  // 记录已访问的标记向量

	// 将初始标记加入队列和已访问集合
	q.push(marking);
	visited.insert(marking);
	int numState = 1;
	while (!q.empty()) {
		vector<int> currentMarking = q.front();
		q.pop();

		//计算当前标记下的使能变迁集
		vector<bool> mayfireTransition(matrix[0].size(), 0);
		bool flag = 0;
		for (int i = 0; i < matrix[0].size(); i++) {
			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[j][i] < 0) {
					if (currentMarking[j] < -matrix[j][i]) {
						flag = 0;
						break;
					}
					else
					{
						flag = 1;
					}
				}
			}
			if (flag == 0) {
				mayfireTransition[i] = 0;
				//fireTransition.push_back(0);
			}
			else {
				mayfireTransition[i] = 1;
				//fireTransition.push_back(1);
			}
		}
		//计算死锁状态
		//也就是说，如果当前标记下的使能变迁集的容器均为0，则该状态为死锁状态
		bool flag_deadlock = 1;
		for (vector<bool>::iterator it = mayfireTransition.begin(); it != mayfireTransition.end(); it++) {
			if (*it == 1) {
				//该标记下有变迁能触发
				flag_deadlock = 0;
				break;
			}
		}

		if (flag_deadlock == 1)
		{
			numDead++;
			flag_deadlock == 0;
		}

		// 计算下一个可能的标记向量
		//vector<int> nextMarking(incidenceMatrix.size(), 0);
		vector<bool> fireTransition(matrix[0].size(), 0);
		for (int i = 0; i < matrix[0].size(); i++) {
			//cout << i << endl;
			if (mayfireTransition[i] == 0) {
				continue;
			}
			if (mayfireTransition[i] == 1) {
				vector<int> nextMarking(matrix.size(), 0);
				fireTransition[i] = 1;

				vector<vector<bool>> fireTransition2(matrix[0].size(), vector<bool>(1, 0));
				for (int i = 0; i < matrix[0].size(); i++) {
					fireTransition2[i][0] = fireTransition[i];
				}
				int index = 0;
				for (int a = 0; a < matrix.size(); a++)//a为A矩阵的行标
				{
					for (int b = 0; b < 1; b++)//b为B矩阵的列标
					{
						for (int c = 0; c < matrix[0].size(); c++)//c为B矩阵的行标、A矩阵的列标
						{
							nextMarking[index] += matrix[a][c] * fireTransition2[c][b];
						}
						index++;
					}
				}
				for (int i = 0; i < matrix.size(); ++i) {
					nextMarking[i] += currentMarking[i];
				}

				fireTransition[i] = 0;

				// 判断下一个标记向量是否已访问过
				if (visited.find(nextMarking) == visited.end()) {
					//cout << "下一个标记未被访问" << endl;
					//下一个标记未被访问
					q.push(nextMarking);
					visited.insert(nextMarking);
				}
			}
		}
	}
	return numDead;
}

//采用严格极小信标的方式预防死锁
bool DeadlockPrevention::SMSdeadlock() {
	//1.为每一个严格极小信标添加一个控制库所
	vector<vector<int>> SMS = Siphon::getInstance().getSMS();

	int numsControlPlaces = SMS.size();
	//2.更新关联矩阵，依次将基本信标对应的特征T-vector添加到关联矩阵中
	vector<vector<int>> ControlIncidenceMatrix; //添加控制库所之后的关联矩阵
	vector<int> ControlMarking(PetriNet::getInstance().incidenceMatrix_.size() + numsControlPlaces, 0);//添加控制库所之后的初始标记
	for (int i = 0; i < PetriNet::getInstance().incidenceMatrix_.size(); i++) {
		ControlMarking[i] = PetriNet::getInstance().m0_(i);
	}
	ControlIncidenceMatrix = PetriNet::getInstance().incidenceMatrix_;
	MatrixXd SMS_T_vector = Siphon::getInstance().getSMS_T_vector();
	vector<vector<int>> v_SMSTvector(SMS_T_vector.rows(), vector<int>(SMS_T_vector.cols()));
	//cout << this->S.SMS_T_vector << endl;
	//将特征T向量矩阵转换成vector数组
	for (int i = 0; i < SMS_T_vector.rows(); i++) {
		for (int j = 0; j < SMS_T_vector.cols(); j++) {
			v_SMSTvector[i][j] = SMS_T_vector(i, j);
		}
	}
	for (int i = 0; i < v_SMSTvector.size(); i++) {
		ControlIncidenceMatrix.push_back(v_SMSTvector[i]);
	}

	//求出初始标记下基本信标中的托肯总数
	vector<int> tokenSMS;
	for (int i = 0; i < SMS.size(); i++) {
		int tokens = 0;
		for (int j = 0; j < SMS[0].size(); j++) {
			if (SMS[i][j] > 0) {
				tokens = tokens + PetriNet::getInstance().m0_(j);
			}
		}
		tokenSMS.push_back(tokens);
	}
	int maxtokens = *max_element(tokenSMS.begin(), tokenSMS.end());

	vector<int> currentCombination;
	vector<vector<int>> result;
	Siphon::getInstance().combinations(1, 0, maxtokens - 1, numsControlPlaces, currentCombination, result);
	//combinations(1, 0, 100, numsControlPlaces, currentCombination, result);

	//依次将result中的结果的个数放入控制库所中
	int numDeadMarking = 0;
	for (int i = 0; i < result.size(); i++) {
		numDeadMarking = 0;
		for (int j = 0; j < result[0].size(); j++) {
			ControlMarking[j + PetriNet::getInstance().incidenceMatrix_.size()] = result[i][j];
		}
		//判断添加控制库所后的那个标记是无死锁的 就需要求可达图
		numDeadMarking = numsDeadMarking(ControlMarking, ControlIncidenceMatrix);
		//cout << "numDeadMarking = " << numDeadMarking << endl;
		if (numDeadMarking == 0) {
			//cout << "ControlMarking" << endl;
			//无死锁
			/*for (int i = 0; i < ControlMarking.size(); i++) {
				cout << ControlMarking[i] << " ";
			}
			cout << endl;*/
			break;
		}
	}

	this->DPSMSmatrix = ControlIncidenceMatrix;
	this->DPSMSmarking = ControlMarking;

	if (numDeadMarking == 0) {
		return true;//死锁问题解决 返回true
	}
	return false;//死锁问题没有解决 返回false
}

vector<vector<int>> DeadlockPrevention::getDPSMSmatrix() {
	return this->DPSMSmatrix;
}
vector<int> DeadlockPrevention::getDPSMSmarking() {
	return this->DPSMSmarking;
}

vector<vector<int>> DeadlockPrevention::getDPESMSmatrix() {
	return this->DPESMSmatrix;
}
vector<int> DeadlockPrevention::getDPESMSmarking() {
	return this->DPESMSmarking;
}

//采用基本信标的方式进行死锁预防
bool DeadlockPrevention::ESMSdeadlock() {
	//1.为每一个基本信标添加一个控制库所
	vector<vector<int>> ESMS = Siphon::getInstance().getESMS();
	int numsControlPlaces = ESMS.size();
	//2.更新关联矩阵，依次将基本信标对应的特征T-vector添加到关联矩阵中
	vector<vector<int>> ControlIncidenceMatrix; //添加控制库所之后的关联矩阵
	vector<int> ControlMarking(PetriNet::getInstance().incidenceMatrix_.size() + numsControlPlaces, 0);//添加控制库所之后的初始标记
	for (int i = 0; i < PetriNet::getInstance().incidenceMatrix_.size(); i++) {
		ControlMarking[i] = PetriNet::getInstance().m0_(i);
	}
	ControlIncidenceMatrix = PetriNet::getInstance().incidenceMatrix_;
	MatrixXd ESMS_T_vector = Siphon::getInstance().getESMS_T_vector();
	vector<vector<int>> v_ESMSTvector(ESMS_T_vector.rows(), vector<int>(ESMS_T_vector.cols()));
	//将特征T向量矩阵转换成vector数组
	for (int i = 0; i < ESMS_T_vector.rows(); i++) {
		for (int j = 0; j < ESMS_T_vector.cols(); j++) {
			v_ESMSTvector[i][j] = ESMS_T_vector(i, j);
		}
	}
	for (int i = 0; i < v_ESMSTvector.size(); i++) {
		ControlIncidenceMatrix.push_back(v_ESMSTvector[i]);
	}

	//求出初始标记下基本信标中的托肯总数
	vector<int> tokenESMS;
	for (int i = 0; i < ESMS.size(); i++) {
		int tokens = 0;
		for (int j = 0; j < ESMS[0].size(); j++) {
			if (ESMS[i][j] > 0) {
				tokens = tokens + PetriNet::getInstance().m0_(j);
			}
		}
		tokenESMS.push_back(tokens);
	}
	int maxtokens = *max_element(tokenESMS.begin(), tokenESMS.end());

	vector<int> currentCombination;
	vector<vector<int>> result;
	Siphon::getInstance().combinations(1, 0, maxtokens - 1, numsControlPlaces, currentCombination, result);
	//combinations(1, 0, 100, numsControlPlaces, currentCombination, result);

	//依次将result中的结果的个数放入控制库所中
	int numDeadMarking = 0;
	for (int i = 0; i < result.size(); i++) {
		numDeadMarking = 0;
		for (int j = 0; j < result[0].size(); j++) {
			ControlMarking[j + PetriNet::getInstance().incidenceMatrix_.size()] = result[i][j];
		}
		//判断添加控制库所后的那个标记是无死锁的 就需要求可达图
		numDeadMarking = numsDeadMarking(ControlMarking, ControlIncidenceMatrix);
		if (numDeadMarking == 0) {
			break;
		}
	}
	this->DPESMSmatrix = ControlIncidenceMatrix;
	this->DPESMSmarking = ControlMarking;
	if (numDeadMarking == 0) {
		return true;
	}
	return false;
}

/*
	状态变迁分离实例：就是那些从危险标记到达坏标记或者死锁标记的标记变迁对
	遍历所有的危险标记，找到从危险标记到达坏标记或者死锁标记的变迁对
	返回值：vector<pair<int,int>> 第一个int表示当前危险标记的标号，第二个int表示当前标记到达坏标记或者死锁标记的变迁号
*/
vector<pair<int, int>> DeadlockPrevention::calcuMTSI(vector<MarkingNode> legalMarking, vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking) {
	vector<pair<int, int>> mtsi;
	vector<MarkingNode> FBM;
	for (int i = 0; i < legalMarking.size(); i++) {
		MarkingNode node = legalMarking[i];
		for (int kk = 0; kk < node.transition_to_son_.size(); kk++) {
			for (int j = 0; j < badMarking.size(); j++) {
				if (node.transition_to_son_[kk].second == badMarking[j].node_name_) {
					//是状态变迁分离实例
					mtsi.push_back(make_pair(node.node_name_, node.transition_to_son_[kk].first + 1));
					FBM.push_back(badMarking[j]);
				}
			}
		}

		for (int kk = 0; kk < node.transition_to_son_.size(); kk++) {
			for (int j = 0; j < deadMarking.size(); j++) {
				if (node.transition_to_son_[kk].second == deadMarking[j].node_name_) {
					//是状态变迁分离实例
					mtsi.push_back(make_pair(node.node_name_, node.transition_to_son_[kk].first + 1));
					FBM.push_back(deadMarking[j]);
				}
			}
		}
	}
	this->MTSI_ = mtsi;
	this->FBM_ = FBM;
	return mtsi;
}

vector<pair<int, int>> DeadlockPrevention::getMTSI() {
	return this->MTSI_;
}

vector<MarkingNode> DeadlockPrevention::getFBM() {
	return this->FBM_;
}

vector<int> visited(INT16_MAX, 0);
int stack[INT16_MAX];
int top = 0;
//求两点之间的路径 剔除环 路过的节点
void DeadlockPrevention::pathAtoB(MarkingNode nodeA, MarkingNode nodeB, vector<MarkingNode> RGnodes) {
	if (nodeA.node_name_ == nodeB.node_name_) {
		//达到终点
		/*cout << "path:" << endl;
		for (int i = 0; i < top; i++)
			cout << stack[i] << endl;
		cout << nodeB.node_name_ << endl;*/

		cout << "path::::::::::::" << endl;
		this->pathNode.push_back(nodeB);
		this->allPathNode.push_back(pathNode);
		//this->legalPathNode.insert(pair<MarkingNode, vector<MarkingNode>>(nodeB, pathNode));
		for (int i = 0; i < pathNode.size(); i++) {
			cout << pathNode[i].node_name_ << endl;
		}
		pathTransition(pathNode, 27);
		this->pathNode.pop_back();
		return;
	}

	visited[nodeA.node_name_] = 1;//标记被访问过 主要是为了避免环的存在

	//把经过的节点加入队列
	this->pathNode.push_back(nodeA);
	//stack[top++] = nodeA.node_name_;
	for (int j = 0; j < nodeA.transition_to_son_.size(); j++) {
		int nextNodeName = nodeA.transition_to_son_[j].second;//找到了下一个节点的序号
		//如果nodeA的下一个节点和nodeB的下一个节点指向了同一个节点，则说明可能会出现环 剔除T-不变式
		/*for (int z = 0; z < nodeB.transition_to_son_.size(); z++) {
			if (nextNodeName == nodeB.transition_to_son_[z].second) {
				goto breakLoop;
			}
		}*/
		//从可达图中寻找该序号的节点
		for (int i = 0; i < RGnodes.size(); i++) {
			//找到了该节点，且该节点没有被访问过
			if (RGnodes[i].node_name_ == nextNodeName && !visited[RGnodes[i].node_name_]) {
				//cout << "path:" << RGnodes[i].node_name_ << endl;
				this->pathAtoB(RGnodes[i], nodeB, RGnodes);
			}
		}
	}

breakLoop:
	this->pathNode.pop_back();
	visited[nodeA.node_name_] = 0;
	//top--;
}

//环路径
int nums = 0;
void DeadlockPrevention::pathAtoA(MarkingNode nodeA, MarkingNode nodeB, vector<MarkingNode> RGnodes) {
	for (int j = 0; j < nodeB.transition_to_son_.size(); j++) {
		if (nodeA.node_name_ == nodeB.transition_to_son_[j].second) {
			//达到终点
			cout << "path:" << nums++ << endl;
			for (int i = 0; i < top; i++)
				cout << stack[i] << endl;
			cout << nodeB.node_name_ << endl;
			return;
		}
	}

	visited[nodeB.node_name_] = 1;
	//this->visited.push_back(nodeA);//标记被访问过

	//把经过的路径加入队列
	stack[top++] = nodeB.node_name_;
	for (int j = 0; j < nodeB.transition_to_son_.size(); j++) {
		int nextNodeName = nodeB.transition_to_son_[j].second;//找到了下一个节点的序号
		//从可达图中寻找该序号的节点
		for (int i = 0; i < RGnodes.size(); i++) {
			//找到了该节点，且该节点没有被访问过
			if (RGnodes[i].node_name_ == nextNodeName && !visited[RGnodes[i].node_name_]) {
				//cout << "path111111111111:" << RGnodes[i].node_name_ << endl;
				this->pathAtoA(nodeA, RGnodes[i], RGnodes);
			}
		}
	}
	//v[nodeB.node_name_] = 0;
	top--;
}

//某节点路径的变迁路径
vector<int> DeadlockPrevention::pathTransition(vector<MarkingNode> node, int numsTransition) {
	//vector<int> result(numsTransition, 0);//
	vector<int> result;//
	if (node.size() == 1) {
		return result;
	}
	int n = 1;
	for (int i = 0; i < node.size() - 1; i++) {
		MarkingNode cur = node[i];
		for (int j = 0; j < cur.transition_to_son_.size(); j++) {
			if (cur.transition_to_son_[j].second == node[i + 1].node_name_) {
				//result[cur.transition_to_son_[j].first]++;
				cout << "transition" << n++ << ": " << cur.transition_to_son_[j].first + 1 << endl;
				result.push_back(cur.transition_to_son_[j].first + 1);
			}
		}
	}
	return result;
}


//基于时间约束的死锁预防策略
void DeadlockPrevention::modifyTimePlaceSupervisor(vector<MarkingNode> RGnodes, vector<MarkingNode> legalMarking, vector<MarkingNode> dangerousMarking,
	vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking, int numsTransition) {
	vector<int> legalTransition;
	vector<int> Imatrix(numsTransition, 0);
	vector<int> Omatrix(numsTransition, 0);

	for (int i = 0; i < legalMarking.size(); i++) {
		for (int j = 0; j < legalMarking[i].transition_to_son_.size(); j++) {
			int nodeName = legalMarking[i].transition_to_son_[j].second;
			for (int z = 0; z < legalMarking.size(); z++) {
				if (nodeName == legalMarking[z].node_name_) {
					legalTransition.push_back(legalMarking[i].transition_to_son_[j].first);
				}

				//在该标记下发射变迁能到达初始标记
				if (nodeName == 0) {
					Imatrix[legalMarking[i].transition_to_son_[j].first] = 1;
					Omatrix[legalMarking[i].transition_to_son_[j].first] = 1;
				}
			}
		}
	}

	for (int i = 0; i < dangerousMarking.size(); i++) {
		MarkingNode node = dangerousMarking[i];
		vector<int> badTransition;
		vector<int> goodTransition;
		for (int j = 0; j < node.transition_to_son_.size(); j++) {
			int nextNode = node.transition_to_son_[j].second;
			//cout << nextNode << endl;
			for (int z = 0; z < badMarking.size(); z++) {
				if (nextNode == badMarking[z].node_name_) {
					if (find(badTransition.begin(), badTransition.end(), node.transition_to_son_[j].first) == badTransition.end()) {
						badTransition.push_back(node.transition_to_son_[j].first);
					}
				}
			}

			for (int z = 0; z < deadMarking.size(); z++) {
				if (nextNode == deadMarking[z].node_name_) {
					if (find(badTransition.begin(), badTransition.end(), node.transition_to_son_[j].first) == badTransition.end()) {
						badTransition.push_back(node.transition_to_son_[j].first);
					}
				}
			}
		}

		for (int j = 0; j < node.transition_to_son_.size(); j++) {
			if (find(badTransition.begin(), badTransition.end(), node.transition_to_son_[j].first) == badTransition.end()) {
				goodTransition.push_back(node.transition_to_son_[j].first);
			}
		}

		bool flagBadT = 0;
		bool flagGoodT = 0;
		for (int j = 0; j < badTransition.size(); j++) {
			if (find(legalTransition.begin(), legalTransition.end(), badTransition[j]) != legalTransition.end()) {
				flagBadT = true;
				break;
			}
		}

		for (int j = 0; j < goodTransition.size(); j++) {
			if (find(legalTransition.begin(), legalTransition.end(), goodTransition[j]) != legalTransition.end()) {
				flagGoodT = true;
				break;
			}
		}

		if (flagBadT && flagGoodT) {
			for (int j = 0; j < RGnodes.size(); j++) {
				for (int z = 0; z < RGnodes[j].transition_to_son_.size(); z++) {
					if (RGnodes[j].transition_to_son_[z].second == node.node_name_) {
						Imatrix[RGnodes[j].transition_to_son_[z].first] = 1;
						Omatrix[RGnodes[j].transition_to_son_[z].first] = 1;
					}
				}
			}
		}
	}

	cout << "PlaceSupervisor" << endl;
	for (int i = 0; i < Imatrix.size(); i++) {
		cout << Imatrix[i] << " ";
	}
	cout << endl;
	cout << "PlaceSupervisor" << endl;
}

void DeadlockPrevention::modifyTimePlaceSupervisor2(vector<MarkingNode> RGnodes, vector<MarkingNode> legalMarking, vector<MarkingNode> dangerousMarking,
	vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking, int numsTransition) {
	vector<vector<int>> pair;
	vector<int> Imatrix(numsTransition, 0);
	vector<int> Omatrix(numsTransition, 0);

	for (int i = 0; i < legalMarking.size(); i++) {
		vector<int> legalTransition;
		for (int j = 0; j < legalMarking[i].transition_to_son_.size(); j++) {
			int nodeName = legalMarking[i].transition_to_son_[j].second;

			for (int z = 0; z < legalMarking.size(); z++) {
				if (nodeName == legalMarking[z].node_name_) {
					legalTransition.push_back(legalMarking[i].transition_to_son_[j].first);
				}
			}

			//在该标记下发射变迁能到达初始标记
			if (nodeName == 0) {
				Imatrix[legalMarking[i].transition_to_son_[j].first] = 1;
				Omatrix[legalMarking[i].transition_to_son_[j].first] = 1;
			}
		}

	}

	cout << "PlaceSupervisor" << endl;
	for (int i = 0; i < Imatrix.size(); i++) {
		cout << Imatrix[i] << " ";
	}
	cout << endl;
	cout << "PlaceSupervisor" << endl;
}