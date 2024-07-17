#include "ReachableGraph.h"

// 向可达图中添加节点
bool ReachableGraph::AddNode(const int& node_name,
	const Eigen::VectorXi& marking,
	const std::vector<std::pair<int, int>>& transition_to_son) {
	MarkingNode node;
	node.node_name_ = node_name;
	node.marking_ = marking;
	node.transition_to_son_ = transition_to_son;
	nodes_.emplace_back(node);
	return REACHABILITY_GRAPH_SUCCESS;
}
bool ReachableGraph::AddNode(const int& node_name, const Eigen::VectorXi& marking) {// 重载，两个参数
	MarkingNode node(node_name, marking);
	nodes_.emplace_back(node);
	return REACHABILITY_GRAPH_SUCCESS;
}
// Eigen vector转换为string
std::string ReachableGraph::Vector2String(Eigen::VectorXi Eigen_vector_int) {
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
int ReachableGraph::GetNodeNumberInVOld(const Eigen::VectorXi& mark) const {
	std::string mark_str = Vector2String(mark);
	auto iter = v_old_.find(mark_str);
	if (iter == v_old_.end()) {
		return -1;
	}
	return iter->second.second;// 编号
}
// 查询V_Old_某个状态是否已遍历激发
bool ReachableGraph::GetNodeStatusInVOld(const Eigen::VectorXi& mark) const {
	std::string mark_str = Vector2String(mark);
	auto iter = v_old_.find(mark_str);
	if (iter == v_old_.end()) {
		return REACHABILITY_GRAPH_FAIL;
	}
	return iter->second.first;// 激发状态
}
// 修改V_Old_中某状态的激发
bool ReachableGraph::SetNodeFiredInVOld(const Eigen::VectorXi& mark) {
	std::string mark_str = Vector2String(mark);
	auto iter = v_old_.find(mark_str);
	if (iter == v_old_.end()) {
		return REACHABILITY_GRAPH_FAIL;
	}
	iter->second.first = true;
	return REACHABILITY_GRAPH_SUCCESS;
}

ReachableGraph& ReachableGraph::getInstance() {
	// TODO: 在此处插入 return 语句
	static ReachableGraph instance;
	return instance;
}

bool ReachableGraph::isNewEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran) {
	if (fireTran == curFireTran) {
		return true;
	}
	else {
		VectorXi temp1 = marking_cur - PetriNet::getInstance().input_matrix_.col(fireTran);
		VectorXi temp2 = PetriNet::getInstance().input_matrix_.col(curFireTran);
		VectorXi temp3 = temp1 - temp2;

		for (auto& j : temp3) {
			if (j < 0) return true;
		}
	}
	return false;
}

bool ReachableGraph::isContinuousEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran) {
	if (this->isNewEnabledTransition(marking_cur, marking_next, fireTran, curFireTran)) {
		return false;
	}
	return true;
}

vector<int> ReachableGraph::FreshFirableTransition(VectorXi marking_) {
	Eigen::VectorXi vector_temp(PetriNet::getInstance().num_of_place_);
	std::vector<int> firable_trans;
	for (int i = 0; i < PetriNet::getInstance().num_of_trans_; i++) {
		vector_temp = marking_ - PetriNet::getInstance().input_matrix_.col(i);
		bool flag = true;
		for (auto& j : vector_temp) {
			flag = (j >= 0) & flag;
		}
		if (flag) firable_trans.emplace_back(i);
	}
	return firable_trans;
}

// 激发一个transition，并改变petri net的marking
VectorXi ReachableGraph::FiringATransition(VectorXi cur_marking, int t)
{
	VectorXi marking_ = cur_marking - PetriNet::getInstance().input_matrix_.col(t) + PetriNet::getInstance().output_matrix_.col(t);
	return marking_;
}

bool ReachableGraph::BuildReachabilityGraph() {
	this->nodes_.clear();
	v_new_.clear();
	v_old_.clear();
	marking_number_ = 0;
	//添加m_0
	Eigen::VectorXi marking_zero = PetriNet::getInstance().m0_;
	v_new_.emplace_back(marking_zero);
	v_old_.emplace(Vector2String(marking_zero), std::make_pair(false, marking_number_));// status=false: 未激发
	AddNode(marking_number_, marking_zero);// 添加M0节点
	int nnnn = 1;
	while (!v_new_.empty()) {// 清空v_new
		Eigen::VectorXi present_marking = v_new_.back();// 本节点的状态
		v_new_.pop_back();

		int present_index = GetNodeNumberInVOld(present_marking);// 本节点的编号

		std::vector<int> firable_t = this->FreshFirableTransition(present_marking);// 获得此状态下firable的t
		unsigned int length = firable_t.size();
		for (int i = 0; i < length; i++) {// 遍历激发
			int transition_name = firable_t[i];

			Eigen::VectorXi follow_marking = this->FiringATransition(present_marking, transition_name);
			int follow_index = GetNodeNumberInVOld(follow_marking);// 校验激发后状态
			if (follow_index == -1) {// 若marking没出现过会返回-1
				marking_number_++;// 出现全新状态，计数器+1
				v_new_.emplace_back(follow_marking); // 加入v_new_等待激发
				cout << "this is " << nnnn++ << endl;
				v_old_.emplace(Vector2String(follow_marking), std::make_pair(false, marking_number_));// 加入v_old_记录编号，状态设置为未激发
				AddNode(marking_number_, follow_marking);// 可达图新增节点
				follow_index = marking_number_;
			}
			// 因为是不同的激发（遍历），即使子节点状态相同，应该也要新增弧（意思是无需校验子节点与前面是否相同）
			nodes_[present_index].transition_to_son_.emplace_back(std::make_pair(transition_name, follow_index));
		}
		SetNodeFiredInVOld(present_marking);
	}
	return REACHABILITY_GRAPH_SUCCESS;
}

//计算环路径
vector<vector<MarkingNode>> ReachableGraph::CalculateCircularPath(vector<MarkingNode> nodes) {
	int n = nodes.size();
	vector<bool> visited(n, false);
	vector<vector<MarkingNode>> cycles;

	for (MarkingNode node : nodes) {
		vector<MarkingNode> path;
		this->dfs(nodes, node, node, visited, path, cycles);
	}

	int i = 1;
	for (auto cycle : cycles) {
		cout << "cycle " << i << " :";
		for (auto c : cycle) {
			cout << c.node_name_ << " ";
		}
		i++;
		cout << endl;
	}

	return cycles;
}

void ReachableGraph::dfs(vector<MarkingNode> nodes, MarkingNode start, MarkingNode current, vector<bool>& visited, vector<MarkingNode>& path, vector<vector<MarkingNode>>& cycles) {
	visited[current.node_name_] = true;
	path.emplace_back(current);

	for (pair<int, int> tran_to_son : current.transition_to_son_) {
		if (tran_to_son.second == start.node_name_ && path.size() > 1) {
			for (int i = 0; i < path.size(); i++) {
				cout << path[i].node_name_ << " ";
			}
			cout << endl;

			bool res = this->isSafeCirPath(path);
			if (res == false) {
				this->SRGinfinite = true;
				cout << "SRG is infinite" << endl;
			}
			else {
				cout << "this path is safety" << endl;
			}

			cycles.emplace_back(path);
		}
		else if (!visited[tran_to_son.second]) {
			for (MarkingNode n : nodes) {
				if (n.node_name_ == tran_to_son.second) {
					dfs(nodes, start, n, visited, path, cycles);
				}
			}
		}
	}

	path.pop_back();
	visited[current.node_name_] = false;
}

bool ReachableGraph::isSafeCirPath(vector<MarkingNode> nodes) {
	MarkingNode start = nodes[0];
	MarkingNode end = nodes[nodes.size() - 1];

	vector<bool> temp;
	for (int i = 0; i < nodes.size() - 1; i++) {
		MarkingNode left = nodes[i];
		MarkingNode right = nodes[i + 1];

		bool res = this->isExistContinuousTran(left, right);
		temp.push_back(res);
	}

	bool res = this->isExistContinuousTran(end, start);
	temp.push_back(res);

	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == false) {
			return true;
		}
	}

	return false;
}

bool ReachableGraph::isExistContinuousTran(MarkingNode left, MarkingNode right)
{
	//找到left->right所发射的变迁
	int fireTran = -1;
	for (int j = 0; j < left.transition_to_son_.size(); j++) {
		if (left.transition_to_son_[j].second == right.node_name_) {
			fireTran = left.transition_to_son_[j].first;
			break;
		}
	}

	//判断发射fireTran之后right标记中是否存在持续使能的变迁
	for (int j = 0; j < right.transition_to_son_.size(); j++) {
		//存在持续使能的变迁
		bool res = this->isContinuousEnabledTransition(left.marking_, right.marking_, fireTran, right.transition_to_son_[j].first);
		if (res == true) {
			return true;
		}
	}
	return false;
}

bool ReachableGraph::isSRGinfinite(vector<vector<MarkingNode>> circularPaths) {
	for (auto path : circularPaths) {
		bool res = isSafeCirPath(path);
		if (res == false) {
			return true;
		}
	}

	return false;
}

bool ReachableGraph::isSRGinfinite() {
	return this->SRGinfinite;
}

//判断当前标记是否是合法标记，也就是能否回到初始标记
bool ReachableGraph::isLegalMarking(VectorXi saveM0) {
	this->nodes_.clear();
	v_new_.clear();
	v_old_.clear();

	marking_number_ = 0;
	//添加m_0
	Eigen::VectorXi marking_zero = PetriNet::getInstance().m0_;
	v_new_.emplace_back(marking_zero);
	v_old_.emplace(Vector2String(marking_zero), std::make_pair(false, marking_number_));// status=false: 未激发
	AddNode(marking_number_, marking_zero);// 添加M0节点
	while (!v_new_.empty()) {// 清空v_new
		Eigen::VectorXi present_marking = v_new_.back();// 本节点的状态
		v_new_.pop_back();

		int present_index = GetNodeNumberInVOld(present_marking);// 本节点的编号

		std::vector<int> firable_t = this->FreshFirableTransition(present_marking);// 获得此状态下firable的t
		unsigned int length = firable_t.size();
		for (int i = 0; i < length; i++) {// 遍历激发
			int transition_name = firable_t[i];

			Eigen::VectorXi follow_marking = this->FiringATransition(present_marking, transition_name);
			if (follow_marking == saveM0) return true;
			int follow_index = GetNodeNumberInVOld(follow_marking);// 校验激发后状态
			if (follow_index == -1) {// 若marking没出现过会返回-1
				marking_number_++;// 出现全新状态，计数器+1
				v_new_.emplace_back(follow_marking); // 加入v_new_等待激发
				v_old_.emplace(Vector2String(follow_marking), std::make_pair(false, marking_number_));// 加入v_old_记录编号，状态设置为未激发
				AddNode(marking_number_, follow_marking);// 可达图新增节点
				follow_index = marking_number_;
			}
			// 因为是不同的激发（遍历），即使子节点状态相同，应该也要新增弧（意思是无需校验子节点与前面是否相同）
			nodes_[present_index].transition_to_son_.emplace_back(std::make_pair(transition_name, follow_index));
		}
		SetNodeFiredInVOld(present_marking);
	}
	return false;
}

//判断node节点是否是危险标记
bool ReachableGraph::isDangerousMarking(MarkingNode node) {
	for (int i = 0; i < node.transition_to_son_.size(); i++) {
		for (int j = 0; j < this->badMarkings_.size(); j++) {
			if (node.transition_to_son_[i].second == this->badMarkings_[j].node_name_) return true;
		}
		for (int j = 0; j < this->deadMarkings_.size(); j++) {
			if (node.transition_to_son_[i].second == this->deadMarkings_[j].node_name_) return true;
		}
	}
	return false;
}

//标识分类
void ReachableGraph::markingClassification() {
	vector<MarkingNode> nodes = this->nodes_;
	unsigned int len = nodes.size();

	vector<MarkingNode> deadMarkings;
	vector<MarkingNode> badMarkings;
	vector<MarkingNode> dangerousMarkings;
	vector<MarkingNode> goodMarkings;
	vector<MarkingNode> legalMarkings;

	//记录初始标记信息
	VectorXi saveM0 = nodes[0].marking_;

	for (int kk = 0; kk < len; kk++) {
		if (nodes[kk].transition_to_son_.size() == 0) {
			//死标记
			deadMarkings.push_back(nodes[kk]);
			continue;
		}
		//如果不是死锁节点，获取当前节点的信息
		VectorXi curM0 = nodes[kk].marking_;

		PetriNet::getInstance().m0_ = curM0;
		bool res = this->isLegalMarking(saveM0);
		if (res) {
			//是合法标记
			legalMarkings.push_back(nodes[kk]);
		}
		else {
			//坏标记
			badMarkings.push_back(nodes[kk]);
		}
	}

	PetriNet::getInstance().m0_ = saveM0;
	cout << "M0: " << saveM0.transpose() << endl;
	this->nodes_ = nodes;

	this->deadMarkings_ = deadMarkings;
	this->legalMarkings_ = legalMarkings;
	this->badMarkings_ = badMarkings;

	for (int i = 0; i < legalMarkings.size(); i++) {
		if (this->isDangerousMarking(legalMarkings[i])) {
			dangerousMarkings.push_back(legalMarkings[i]);
		}
		else {
			goodMarkings.push_back(legalMarkings[i]);
		}
	}
	this->goodMarkings_ = goodMarkings;
	this->dangerousMarkings_ = dangerousMarkings;
}

// 外部获取可达图
const std::vector<MarkingNode>& ReachableGraph::GetNodes() const {
	return this->nodes_;
}
vector<MarkingNode> ReachableGraph::getDeadMarkings() {
	return this->deadMarkings_;
}
vector<MarkingNode> ReachableGraph::getDangerousMarkings() {
	return this->dangerousMarkings_;
}
vector<MarkingNode> ReachableGraph::getBadMarkings() {
	return this->badMarkings_;
}
vector<MarkingNode> ReachableGraph::getGoodMarkings() {
	return this->goodMarkings_;
}
vector<MarkingNode> ReachableGraph::getLegalMarkings() {
	return this->legalMarkings_;
}