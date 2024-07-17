#include "SymbolicGraph.h"

SymbolicGraph& SymbolicGraph::getInstance() {
	// TODO: 在此处插入 return 语句
	static SymbolicGraph instance;
	return instance;
}

vector<SymbolicNode> SymbolicGraph::calculatePath(vector<PartialGraphNode> path) {
	vector<SymbolicNode> pathSymbolicNode;

	if (path.size() == 0) return{};
	//获取起始节点信息
	PartialGraphNode startNode = path[0];
	vector<int> trans = startNode.trans;

	vector<bool> visited(trans.size(), false);
	vector<int> pathTran;
	vector<vector<int>> result;
	this->transPair(trans, visited, pathTran, result);

	unordered_map<pair<int, int>, string, MyCompare> transitionDelta_m0;
	for (auto re : result) {
		transitionDelta_m0[pair<int, int>(re[0], re[1])] = TPN::getInstance().parametricTime[re[0]][1] + "-" + TPN::getInstance().parametricTime[re[1]][0];
		//cout << transitionDelta_m0[pair<int, int>(re[0], re[1])] << endl;
	}
	SymbolicNode node0;
	node0.node_name_ = startNode.node_name_;
	node0.marking_ = startNode.marking_;
	node0.transitionDelta = transitionDelta_m0;

	pathSymbolicNode.push_back(node0);
	if (path.size() == 1) {
		return pathSymbolicNode;
	}

	VectorXi marking_cur = node0.marking_;
	int fireTran = -1;
	for (int i = 0; i < startNode.transition_to_son_.size(); i++) {
		if (startNode.transition_to_son_[i].second == path[1].node_name_) {
			fireTran = startNode.transition_to_son_[i].first;
			break;
		}
	}
	for (int k = 1; k < path.size(); k++) {
		vector<int> nextTrans = path[k].trans;
		vector<bool> next_visited(nextTrans.size(), false);
		vector<int> next_path;
		vector<vector<int>> next_result;
		this->transPair(nextTrans, next_visited, next_path, next_result);

		unordered_map<pair<int, int>, string, MyCompare> cur_transitionDelta(pathSymbolicNode[k - 1].transitionDelta.begin(),
			pathSymbolicNode[k - 1].transitionDelta.end());

		unordered_map<pair<int, int>, string, MyCompare> next_transitionDelta;

		map<int, bool> transProperty_next = transProperty(pathSymbolicNode[k - 1].marking_,
			path[k].marking_, nextTrans, fireTran);

		for (int i = 0; i < next_result.size(); i++) {
			if (transProperty_next[next_result[i][0]] && transProperty_next[next_result[i][1]]) {
				//两个都是新使能的
				string str = TPN::getInstance().parametricTime[next_result[i][0]][1] + "-" + TPN::getInstance().parametricTime[next_result[i][1]][0];

				next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

				//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
			}

			if (transProperty_next[next_result[i][0]] && !transProperty_next[next_result[i][1]]) {
				//新使能 持续使能
				string str = TPN::getInstance().parametricTime[next_result[i][0]][1] + "+" + cur_transitionDelta[pair<int, int>(fireTran, next_result[i][1])];

				next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

				//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
			}

			if (!transProperty_next[next_result[i][0]] && transProperty_next[next_result[i][1]]) {
				//持续使能 新使能
				string str = cur_transitionDelta[pair<int, int>(next_result[i][0], fireTran)] + "-" + TPN::getInstance().parametricTime[next_result[i][1]][0];

				next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

				//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
			}

			if (!transProperty_next[next_result[i][0]] && !transProperty_next[next_result[i][1]]) {
				//持续使能 持续使能
				string str = cur_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])];

				next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

				//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
			}
		}

		SymbolicNode next_node;
		next_node.node_name_ = path[k].node_name_;
		next_node.marking_ = path[k].marking_;
		next_node.transitionDelta = next_transitionDelta;

		pathSymbolicNode.push_back(next_node);

		if (k < path.size() - 1) {
			for (int i = 0; i < path[k].transition_to_son_.size(); i++) {
				if (path[k].transition_to_son_[i].second == path[k + 1].node_name_) {
					fireTran = path[k].transition_to_son_[i].first;
					break;
				}
			}
		}
	}

	return pathSymbolicNode;
}

//将使能变迁两两排列
void SymbolicGraph::transPair(vector<int> firable_trans, vector<bool>& visited, vector<int>& path, vector<vector<int>>& result) {
	if (path.size() == 2) {
		result.push_back(path);
		return;
	}

	for (int i = 0; i < firable_trans.size(); i++) {
		if (visited[i] == true) continue;
		path.push_back(firable_trans[i]);
		visited[i] = true;
		transPair(firable_trans, visited, path, result);
		path.pop_back();
		visited[i] = false;
	}
}

bool SymbolicGraph::isNewEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran) {
	if (fireTran == curFireTran) {
		return true;
	}
	else {
		VectorXi temp1 = marking_cur - TPN::getInstance().input_matrix_.col(fireTran);
		VectorXi temp2 = TPN::getInstance().input_matrix_.col(curFireTran);
		VectorXi temp3 = temp1 - temp2;

		//TODO:此处可优化，改用稀疏矩阵判断是否可激发
		for (auto& j : temp3) {
			if (j < 0) return true;
		}
	}
	return false;
}

bool SymbolicGraph::isContinuousEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran) {
	if (this->isNewEnabledTransition(marking_cur, marking_next, fireTran, curFireTran)) {
		return false;
	}
	return true;
}

map<int, bool> SymbolicGraph::transProperty(VectorXi marking_cur, VectorXi marking_next, vector<int> firable_trans, int tran) {
	map<int, bool> transProperty_;
	for (int i = 0; i < firable_trans.size(); i++) {
		transProperty_[firable_trans[i]] = isNewEnabledTransition(marking_cur, marking_next, tran, firable_trans[i]);
	}
	return transProperty_;
}

// 更新当前可用激发：marking改变后皆需调用此函数
void SymbolicGraph::FreshFirableTransition(VectorXi marking_) {
	Eigen::VectorXi vector_temp(TPN::getInstance().num_of_place_);
	std::vector<int> firable_trans;
	for (int i = 0; i < TPN::getInstance().num_of_trans_; i++) {
		vector_temp = marking_ - TPN::getInstance().input_matrix_.col(i);
		bool flag = true;
		//TODO:此处可优化，改用稀疏矩阵判断是否可激发
		for (auto& j : vector_temp) {
			flag = (j >= 0) & flag;
		}
		if (flag) firable_trans.emplace_back(i);
	}
	this->enabled_trans = firable_trans;
}

//发射一个变迁
VectorXi SymbolicGraph::fireAtransition(VectorXi marking, int tran) {
	VectorXi next_marking = marking - TPN::getInstance().input_matrix_.col(tran) + TPN::getInstance().output_matrix_.col(tran);
	return next_marking;
}

StateNode* SymbolicGraph::buildGraph()
{
	//求出初始标记的使能变迁集合
	this->FreshFirableTransition(TPN::getInstance().m0_);

	vector<bool> visited(this->enabled_trans.size(), false);
	vector<int> path;
	vector<vector<int>> result;
	this->transPair(this->enabled_trans, visited, path, result);

	unordered_map<pair<int, int>, string, MyCompare> transitionDelta_m0;
	for (auto re : result) {
		transitionDelta_m0[pair<int, int>(re[0], re[1])] = TPN::getInstance().parametricTime[re[0]][1] + "-" + TPN::getInstance().parametricTime[re[1]][0];
	}


	//将初始节点信息添加至可达图中
	StateNode* node = new StateNode;
	this->state_number = 0;
	node->node_name_ = this->state_number;
	node->marking_ = TPN::getInstance().m0_;
	node->transitionDelta = transitionDelta_m0;
	node->transitionDelta_temp = transitionDelta_m0;

	//用来记录已经求过的状态
	vector<StateNode> oldState;
	StateNode nodeM0;
	nodeM0.node_name_ = node->node_name_;
	nodeM0.marking_ = node->marking_;
	nodeM0.transitionDelta = node->transitionDelta;
	nodeM0.transitionDelta_temp = node->transitionDelta_temp;
	nodeM0.childerdNode = node->childerdNode;
	oldState.push_back(nodeM0);

	//队列
	queue<StateNode*> q_new;
	q_new.push(node);

	while (!q_new.empty()) {
		StateNode* cur_node = q_new.front();
		q_new.pop();

		FreshFirableTransition(cur_node->marking_);//获取当前节点的可发射变迁集合

		vector<int> cur_enabledTrans = this->enabled_trans;

		StateNode nodeCur;
		nodeCur.node_name_ = cur_node->node_name_;
		nodeCur.marking_ = cur_node->marking_;
		nodeCur.transitionDelta = cur_node->transitionDelta;
		nodeCur.transitionDelta_temp = cur_node->transitionDelta_temp;

		//以此发射变迁
		for (int i = 0; i < cur_enabledTrans.size(); i++) {
			int transition_name = cur_enabledTrans[i];
			VectorXi next_marking = this->fireAtransition(cur_node->marking_, transition_name);
			//cout << "下一个标记：" << next_marking.transpose() << endl;
			FreshFirableTransition(next_marking);//获取下一个节点的可发射变迁集合
			vector<int> next_enabledTrans = this->enabled_trans;

			if (next_enabledTrans.size() <= 1) {
				//使能变迁数<=1 没有transitionDelta
				//生成节点以及节点编号
				StateNode* next_node = new StateNode;
				next_node->marking_ = next_marking;
				//next_node->transitionDelta = {};

				cur_node->childerdNode[transition_name] = next_node;

				StateNode temp;
				temp.marking_ = next_node->marking_;
				//temp.transitionDelta = next_node->transitionDelta;
				//temp.childerdNode = next_node->childerdNode;

				if (find(oldState.begin(), oldState.end(), temp) == oldState.end()) {
					//cout << "不存在" << endl;
					this->state_number++;
					temp.node_name_ = this->state_number;
					next_node->node_name_ = this->state_number;
					//cur_node->tranSon[transition_name] = this->state_number;
					auto iterOld = find(oldState.begin(), oldState.end(), nodeCur);
					iterOld->tranSon[transition_name] = this->state_number;
					oldState.push_back(temp);
					q_new.push(next_node);
				}
				else {
					auto iter = find(oldState.begin(), oldState.end(), temp);
					int nextNodeIndex = iter->node_name_;
					auto iterOld = find(oldState.begin(), oldState.end(), nodeCur);
					iterOld->tranSon[transition_name] = nextNodeIndex;
				}
			}
			else {
				vector<bool> next_visited(next_enabledTrans.size(), false);
				vector<int> next_path;
				vector<vector<int>> next_result;
				this->transPair(next_enabledTrans, next_visited, next_path, next_result);

				unordered_map<pair<int, int>, string, MyCompare> cur_transitionDelta(cur_node->transitionDelta.begin(), cur_node->transitionDelta.end());
				//unordered_map<pair<int, int>, string, MyCompare> cur_transitionDelta_temp(cur_node->transitionDelta_temp.begin(), cur_node->transitionDelta_temp.end());

				unordered_map<pair<int, int>, string, MyCompare> next_transitionDelta;
				unordered_map<pair<int, int>, string, MyCompare> next_transitionDelta_temp;

				map<int, bool> transProperty_next = transProperty(cur_node->marking_, next_marking, next_enabledTrans, cur_enabledTrans[i]);

				for (int i = 0; i < next_result.size(); i++) {
					if (transProperty_next[next_result[i][0]] && transProperty_next[next_result[i][1]]) {
						//两个都是新使能的
						string str = TPN::getInstance().parametricTime[next_result[i][0]][1] + "-" + TPN::getInstance().parametricTime[next_result[i][1]][0];

						next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						str = MyString::getInstance().getStringDelta(str);

						next_transitionDelta_temp[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
					}

					if (transProperty_next[next_result[i][0]] && !transProperty_next[next_result[i][1]]) {
						//新使能 持续使能
						string str = TPN::getInstance().parametricTime[next_result[i][0]][1] + "+" + cur_transitionDelta[pair<int, int>(transition_name, next_result[i][1])];

						next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						str = MyString::getInstance().getStringDelta(str);

						next_transitionDelta_temp[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
					}

					if (!transProperty_next[next_result[i][0]] && transProperty_next[next_result[i][1]]) {
						//持续使能 新使能
						string str = cur_transitionDelta[pair<int, int>(next_result[i][0], transition_name)] + "-" + TPN::getInstance().parametricTime[next_result[i][1]][0];

						next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						str = MyString::getInstance().getStringDelta(str);

						next_transitionDelta_temp[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
					}

					if (!transProperty_next[next_result[i][0]] && !transProperty_next[next_result[i][1]]) {
						//持续使能 持续使能
						string str = cur_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])];

						next_transitionDelta[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						str = MyString::getInstance().getStringDelta(str);

						next_transitionDelta_temp[pair<int, int>(next_result[i][0], next_result[i][1])] = str;

						//cout << "<" << next_result[i][0] << ", " << next_result[i][1] << "> : " << str << endl;
					}
				}
				StateNode* next_node = new StateNode;
				next_node->marking_ = next_marking;

				next_node->transitionDelta = next_transitionDelta;

				next_node->transitionDelta_temp = next_transitionDelta_temp;

				cur_node->childerdNode[transition_name] = next_node;

				StateNode temp;
				temp.marking_ = next_node->marking_;
				temp.transitionDelta = next_node->transitionDelta;
				temp.transitionDelta_temp = next_node->transitionDelta_temp;
				//temp.childerdNode = next_node->childerdNode;

				if (find(oldState.begin(), oldState.end(), temp) == oldState.end()) {
					this->state_number++;
					temp.node_name_ = this->state_number;
					next_node->node_name_ = this->state_number;
					/*if (iterOld == oldState.end()) {
						cout << "iterOld == oldState.end()" << endl;
					}*/
					auto iterOld = find(oldState.begin(), oldState.end(), nodeCur);
					if (iterOld != oldState.end()) {
						iterOld->tranSon[transition_name] = this->state_number;
					}

					oldState.push_back(temp);
					q_new.push(next_node);
				}
				else {
					auto iter = find(oldState.begin(), oldState.end(), temp);
					int nextNodeIndex = iter->node_name_;
					auto iterOld = find(oldState.begin(), oldState.end(), nodeCur);
					iterOld->tranSon[transition_name] = nextNodeIndex;
				}
			}
		}
	}

	this->nodes = oldState;

	/*cout << "printStateNode" << endl;
	for (const auto& node : oldState) {
		printStateNode(node);
		cout << endl;
	}*/

	return node;
}

vector<StateNode> SymbolicGraph::getSRG() {
	return this->nodes;
}
void SymbolicGraph::printTransitionDelta(unordered_map<pair<int, int>, string, MyCompare> cur_transitionDelta) {
	for (auto& delta : cur_transitionDelta) {
		cout << "<" << delta.first.first << " , " << delta.first.second << "> = " << delta.second << endl;
	}
}

void SymbolicGraph::printStateNode(const StateNode& node) {
	// Print marking
	cout << "state: " << node.node_name_ << ": " << node.marking_.transpose() << endl;

	// Print transitionDelta
	std::cout << "Transition Delta:" << std::endl;
	for (const auto& entry : node.transitionDelta_temp) {
		std::cout << "(" << entry.first.first + 1 << ", " << entry.first.second + 1 << "): " << entry.second << std::endl;
	}

	// Print child nodes
	std::cout << "Child Nodes:" << std::endl;
	//cout << node.tranSon.size() << endl;
	for (const auto& entry : node.tranSon) {
		std::cout << entry.first + 1 << " -> " << entry.second << std::endl; // Assuming printing pointer addresses
	}
}

// Eigen vector转换为string
string SymbolicGraph::Vector2String(Eigen::VectorXi Eigen_vector_int) {
	//std::vector<int>
	std::vector<int> arg(&Eigen_vector_int[0],
		Eigen_vector_int.data() + Eigen_vector_int.cols() * Eigen_vector_int.rows());
	std::string strVec;
	for (auto data : arg) {
		strVec += std::to_string(data) + ",";
	}
	strVec = strVec.substr(0, strVec.size() - 1);
	return strVec;
}
// 查询V_Old_为某个状态分配的编号
int SymbolicGraph::GetNodeNumberInVOld(const Eigen::VectorXi& mark) const {
	std::string mark_str = Vector2String(mark);
	auto iter = v_old_.find(mark_str);
	if (iter == v_old_.end()) {
		return -1;
	}
	return iter->second.second;// 编号
}
