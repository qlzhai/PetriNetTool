#include "TBDP.h"

TBDP& TBDP::getInstance() {
	// TODO: 在此处插入 return 语句
	static TBDP instance;
	return instance;
}

void TBDP::init() {
	this->allPartialGraph_.clear();
	this->startNodes_.clear();
	this->noCyclePaths_.clear();
	this->cyclePaths_.clear();
	this->mergePaths_.clear();
	this->singlePaths_.clear();
	this->pathsMapping_.clear();
}
void TBDP::calculatePartialGraph(MarkingNode node) {
	set<int> startNode_name;
	//计算node标记下的使能变迁的集合
	vector<int> nodeEnabledTrans;
	for (int i = 0; i < node.transition_to_son_.size(); i++) {
		nodeEnabledTrans.push_back(node.transition_to_son_[i].first);
	}

	PartialGraphNode nodeD;
	nodeD.marking_ = node.marking_;
	nodeD.node_name_ = node.node_name_;
	nodeD.trans = nodeEnabledTrans;

	queue<PartialGraphNode> q_new;
	q_new.push(nodeD);

	vector<MarkingNode> nodes = ReachableGraph::getInstance().GetNodes();
	vector<PartialGraphNode> partialGraph;
	partialGraph.push_back(nodeD);

	while (!q_new.empty()) {
		PartialGraphNode curNode = q_new.front();
		q_new.pop();
		int curIndex = curNode.node_name_;//当前节点的标号
		VectorXi curMarking = curNode.marking_;//当前标记
		vector<int> curTrans = curNode.trans;//部分可达图中当前节点标号需要的使能变迁集

		for (int i = 0; i < nodes.size(); i++) {
			VectorXi nextMarking = nodes[i].marking_;
			int nextIndex = nodes[i].node_name_;

			PartialGraphNode nextNode;
			nextNode.node_name_ = nextIndex;
			nextNode.marking_ = nextMarking;

			for (int j = 0; j < nodes[i].transition_to_son_.size(); j++) {
				if (nodes[i].transition_to_son_[j].second == curIndex) {
					int fireTran = nodes[i].transition_to_son_[j].first;//发射的变迁

					for (int k = 0; k < curTrans.size(); k++) {
						bool flag = ReachableGraph::getInstance().isNewEnabledTransition(nextMarking, curMarking, fireTran, curTrans[k]);
						if (flag == false) {
							if (find(nextNode.trans.begin(), nextNode.trans.end(), fireTran) == nextNode.trans.end()) {
								nextNode.trans.push_back(fireTran);
							}
							if (find(nextNode.trans.begin(), nextNode.trans.end(), curTrans[k]) == nextNode.trans.end()) {
								nextNode.trans.push_back(curTrans[k]);
							}
							pair<int, int> pairTemp = pair<int, int>(fireTran, curIndex);
							if (find(nextNode.transition_to_son_.begin(), nextNode.transition_to_son_.end(), pairTemp) == nextNode.transition_to_son_.end()) {
								nextNode.transition_to_son_.push_back(pair<int, int>(fireTran, curIndex));
							}
						}
					}

					if (!nextNode.trans.empty()) {
						if (find(partialGraph.begin(), partialGraph.end(), nextNode) == partialGraph.end()) {
							//nextNode不存在
							if (nextNode.node_name_ == 0) {
								startNode_name.insert(0);
							}
							q_new.push(nextNode);
							partialGraph.push_back(nextNode);
						}
						else {
							//nextNode存在，但是nextNode的其他数据可能不相等
							/*for (auto tran_son : nextNode.transition_to_son_) {
								auto it = find(partialGraph.begin(), partialGraph.end(), nextNode);
								if (find(it->transition_to_son_.begin(), it->transition_to_son_.end(), tran_son) == it->transition_to_son_.end()) {
									cout << "i am here" << endl;
									it->transition_to_son_.push_back(tran_son);
								}
							}*/

							//修改原因：nextNode中的transition_to_son_中的成员可能重复
							for (auto tran_son : nextNode.transition_to_son_) {
								auto it = find(partialGraph.begin(), partialGraph.end(), nextNode);
								bool testExistTran_to_Son = false;
								for (int kk = 0; kk < it->transition_to_son_.size(); kk++) {
									if (it->transition_to_son_[kk].first == tran_son.first) {
										testExistTran_to_Son = true;
										break;
									}
								}
								if (testExistTran_to_Son == false) {
									it->transition_to_son_.push_back(tran_son);
								}
							}

							//修改原因，可能缺少nextNode中的tran可能缺少成员
							for (auto tran : nextNode.trans) {
								auto it = find(partialGraph.begin(), partialGraph.end(), nextNode);
								bool testExistTran = false;
								for (int kk = 0; kk < it->trans.size(); kk++) {
									if (it->trans[kk] == tran) {
										testExistTran = true;
										break;
									}
								}
								if (testExistTran == false) {
									it->trans.push_back(tran);
								}
							}
						}
					}
					else {
						//如果nextNode.trans为空，则说明存在一个nextNode节点，该节点下的使能变迁的发射时间域不会影响curNode.trans的变迁的发射时间域
						startNode_name.insert(curIndex);
					}
				}
			}
		}
	}
	this->allPartialGraph_.push_back(partialGraph);
	vector<int> startNode(startNode_name.begin(), startNode_name.end());
	this->startNodes_.push_back(startNode);
}

void TBDP::calculateAllPartialGraph() {
	this->init();
	int index = 1;
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();
	for (int i = 0; i < dangerousMarkings.size(); i++) {
		TBDP::getInstance().calculatePartialGraph(dangerousMarkings[i]);
	}
}

vector<vector<PartialGraphNode>> TBDP::getAllPartialGraphs() {
	return this->allPartialGraph_;
}
vector<vector<int>> TBDP::getStartNodes() {
	return this->startNodes_;
}

void TBDP::dfs(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode target, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths) {
	visited[start.node_name_] = true;
	path.push_back(start);

	if (start == target) {
		for (int i = 0; i < path.size(); i++) {
			cout << path[i].node_name_ << " ";
		}
		cout << endl;
		paths.push_back(path);
	}
	else {
		for (int i = 0; i < partialGraph.size(); i++) {
			if (partialGraph[i].node_name_ == start.node_name_) {
				for (int j = 0; j < partialGraph[i].transition_to_son_.size(); j++) {
					if (!visited[partialGraph[i].transition_to_son_[j].second]) {
						for (int k = 0; k < partialGraph.size(); k++) {
							if (partialGraph[k].node_name_ == partialGraph[i].transition_to_son_[j].second) {
								dfs(partialGraph, partialGraph[k], target, visited, path, paths);
							}
						}
					}
				}
			}
		}
	}

	path.pop_back();
	visited[start.node_name_] = false;
}

void TBDP::dfs2(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode target, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths) {
	if (start == target) {
		path.push_back(target);
		for (int i = 0; i < path.size(); i++) {
			cout << path[i].node_name_ << " ";
		}
		cout << endl;
		paths.push_back(path);
		path.pop_back();
		return;
	}

	for (int i = 0; i < start.transition_to_son_.size(); i++) {
		if (visited[start.node_name_] == false) {
			for (int j = 0; j < partialGraph.size(); j++) {
				if (partialGraph[j].node_name_ == start.transition_to_son_[i].second) {
					path.push_back(start);
					visited[start.node_name_] = true;
					dfs2(partialGraph, partialGraph[j], target, visited, path, paths);
					path.pop_back();
					visited[start.node_name_] = false;
				}
			}
		}
	}
}

void TBDP::dfsCircle(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode current, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths) {
	path.push_back(current);
	visited[current.node_name_] = true;

	for (pair<int, int> tran_to_son : current.transition_to_son_) {
		if (visited[tran_to_son.second] == false) {
			for (PartialGraphNode n : partialGraph) {
				if (n.node_name_ == tran_to_son.second) {
					dfsCircle(partialGraph, start, n, visited, path, paths);
				}
			}
		}
		else if (tran_to_son.second == start.node_name_) {
			paths.push_back(path);
		}
	}
	path.pop_back();
	visited[current.node_name_] = false;
}

//计算单个部分可达图的路径
void TBDP::findSingleGraphPath(vector<PartialGraphNode> partialGraph, vector<int> startNode) {
	vector<PartialGraphNode> starPartialtNode;
	for (int i = 0; i < partialGraph.size(); i++) {
		int index = partialGraph[i].node_name_;
		if (find(startNode.begin(), startNode.end(), index) != startNode.end()) {
			starPartialtNode.push_back(partialGraph[i]);
		}
	}

	//寻找所有的非环路径
	int n = ReachableGraph::getInstance().GetNodes().size();
	vector<vector<PartialGraphNode>> paths;
	for (int i = 0; i < starPartialtNode.size(); i++) {
		cout << "startNode: " << starPartialtNode[i].node_name_ << endl;
		vector<PartialGraphNode> path;
		vector<bool> visited(n, false);
		dfs2(partialGraph, starPartialtNode[i], partialGraph[0], visited, path, paths);
	}
	this->noCyclePaths_ = paths;
	for (int i = 0; i < paths.size(); i++) {
		for (int j = 0; j < paths[i].size(); j++) {
			cout << paths[i][j].node_name_ << " ";
		}
		cout << endl;
	}

	//寻找所有的环路径
	vector<vector<PartialGraphNode>> circularPaths;
	vector<bool> visitedCircle(n, false);
	for (int i = 0; i < startNode.size(); i++) {
		vector<PartialGraphNode> path;
		dfsCircle(partialGraph, starPartialtNode[i], starPartialtNode[i], visitedCircle, path, circularPaths);
	}
	this->cyclePaths_ = circularPaths;
	cout << "dfsCircle " << endl;
	for (int i = 0; i < circularPaths.size(); i++) {
		for (int j = 0; j < circularPaths[i].size(); j++) {
			cout << circularPaths[i][j].node_name_ << " ";
		}
		cout << endl;
	}
}

void TBDP::mergePath() {
	vector<vector<PartialGraphNode>> mergePaths;
	vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> pathsMapping;
	vector<vector<PartialGraphNode>> singlePaths;

	//先遍历非循环路径，再遍历循环路径
	for (int i = 0; i < this->noCyclePaths_.size(); i++) {
		vector<PartialGraphNode> noCyclePath = this->noCyclePaths_[i];
		bool resSingle = true;
		for (int j = 0; j < this->cyclePaths_.size(); j++) {
			vector<PartialGraphNode> cyclePath = this->cyclePaths_[j];
			if (noCyclePath[0] == cyclePath[0]) {
				resSingle = false;
				cout << "resSingle: " << resSingle << endl;
				vector<PartialGraphNode> mergePath(cyclePath.begin(), cyclePath.end());
				for (int k = 0; k < noCyclePath.size(); k++) {
					mergePath.push_back(noCyclePath[k]);
				}
				mergePaths.push_back(mergePath);
				pathsMapping.push_back(pair<vector<PartialGraphNode>, vector<PartialGraphNode>>(noCyclePath, mergePath));
			}
		}
		if (resSingle) {
			singlePaths.push_back(noCyclePath);
		}
	}

	//另一种遍历方式，先遍历循环路径，再遍历非循环路径
	/*for (int i = 0; i < this->cyclePaths_.size(); i++) {
		vector<PartialGraphNode> cyclePath = this->cyclePaths_[i];
		for (int j = 0; j < this->noCyclePaths_.size(); j++) {
			vector<PartialGraphNode> noCyclePath = this->noCyclePaths_[j];
			if (noCyclePath[0] == cyclePath[0]) {
				vector<PartialGraphNode> mergePath(cyc
				lePath.begin(), cyclePath.end());
				for (int k = 0; k < noCyclePath.size(); k++) {
					mergePath.push_back(noCyclePath[k]);
				}
				mergePaths.push_back(mergePath);
				pathsMapping.push_back(pair<vector<PartialGraphNode>, vector<PartialGraphNode>>(noCyclePath, mergePath));
			}
		}
	}*/
	this->mergePaths_ = mergePaths;
	this->pathsMapping_ = pathsMapping;
	this->singlePaths_ = singlePaths;
}

void TBDP::calculateSignalPathSRG(vector<vector<PartialGraphNode>> singlePaths) {
	for (int i = 0; i < singlePaths.size(); i++) {
		vector<SymbolicNode> nodesSRG = SymbolicGraph::getInstance().calculatePath(singlePaths[i]);
	}
}

void TBDP::calculateCirclePathSRG(vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> pathsMapping)
{
	vector<vector<string>> mapDelta;
	for (int i = 0; i < pathsMapping.size(); i++) {
		vector<SymbolicNode> first = SymbolicGraph::getInstance().calculatePath(pathsMapping[i].first);
		vector<SymbolicNode> second = SymbolicGraph::getInstance().calculatePath(pathsMapping[i].second);
		for (auto itFirst = first[first.size() - 1].transitionDelta.begin(), itSecond = second[second.size() - 1].transitionDelta.begin();
			itFirst != first[first.size() - 1].transitionDelta.end(), itSecond != second[second.size() - 1].transitionDelta.end();
			itFirst++, itSecond++) {
			map<string, int, CompareABString> a_map_first;
			map<string, int, CompareABString> b_map_first;
			map<string, int, CompareABString> a_map_second;
			map<string, int, CompareABString> b_map_second;
			MyPathString::getInstance().mySplit(itFirst->second, a_map_first, b_map_first);
			MyPathString::getInstance().mySplit(itSecond->second, a_map_second, b_map_second);

			string str = "";
			for (auto it = b_map_second.begin(); it != b_map_second.end(); it++) {
				string temp = it->first;
				if (b_map_first.find(temp) == b_map_first.end()) {
					//没有找到，说明是新出现的
					if (it->second == 1) {
						str = str + "+" + temp;
					}
					else {
						str = str + "+" + to_string(it->second) + "*" + temp;
					}
				}
				else {
					//不是新出现的，判断系数是否相等
					int b_first = b_map_first[temp];
					int b_second = it->second;
					if (b_first != b_second) {
						//系数不相等，也肯定是b_second大
						int b = b_second - b_first;
						if (b == 1) {
							str = str + "+" + temp;
						}
						else {
							str = str + "+" + to_string(b) + "*" + temp;
						}
					}
				}
			}

			for (auto it = a_map_second.begin(); it != a_map_second.end(); it++) {
				string temp = it->first;
				if (a_map_first.find(temp) == a_map_first.end()) {
					//没有找到，说明是新出现的
					if (it->second == 1) {
						str = str + "-" + temp;
					}
					else {
						str = str + "-" + to_string(it->second) + "*" + temp;
					}
				}
				else {
					//不是新出现的，判断系数是否相等
					int a_first = a_map_first[temp];
					int a_second = it->second;
					if (a_first != a_second) {
						//系数不相等，也肯定是b_second大
						int a = a_second - a_first;
						if (a == 1) {
							str = str + "-" + temp;
						}
						else {
							str = str + "-" + to_string(a) + "*" + temp;
						}
					}
				}
			}
			if (str.size() > 1) {
				//str = str.substr(1);
				cout << "(" << itFirst->first.first << ", " << itFirst->first.second << "): " << str << endl;
			}
			else {
				cout << "(" << itFirst->first.first << ", " << itFirst->first.second << "): " << "str.size() <= 1---------->: "
					<< TPN::getInstance().parametricTime[itFirst->first.first][1] << "-" << TPN::getInstance().parametricTime[itFirst->first.second][1] << endl;;
			}

			cout << "final result: " << endl;
			if (str.size() > 1) {
				int t1 = itFirst->first.first;
				int t2 = itFirst->first.second;
				string delta = itFirst->second + " + n * (" + str + ")";
				string s1 = to_string(t1);
				string s2 = to_string(t2);
				vector<string> temp;
				temp.push_back(s1);
				temp.push_back(s2);
				temp.push_back(delta);
				mapDelta.push_back(temp);
				//str = str.substr(1);
				cout << "(" << itFirst->first.first << ", " << itFirst->first.second << "): " << itFirst->second << " + n * (" << str << ")" << endl;
			}
			else {
				cout << "(" << itFirst->first.first << ", " << itFirst->first.second << "): " << "str.size() <= 1---------->: "
					<< TPN::getInstance().parametricTime[itFirst->first.first][1] << "-" << TPN::getInstance().parametricTime[itFirst->first.second][1] << endl;;
				int t1 = itFirst->first.first;
				int t2 = itFirst->first.second;
				string delta = itFirst->second;
				string s1 = to_string(t1);
				string s2 = to_string(t2);
				vector<string> temp;
				temp.push_back(s1);
				temp.push_back(s2);
				temp.push_back(delta);
				mapDelta.push_back(temp);
			}
		}
	}
	this->mapDelta_ = mapDelta;
}

vector<vector<string>> TBDP::getMapDelta_() {
	return this->mapDelta_;
}

void TBDP::calculateAllSRG() {
	vector<vector<PartialGraphNode>> allPartialGraphs = this->allPartialGraph_;
	vector<vector<int>> startNodes = this->startNodes_;
	for (int i = 0; i < allPartialGraphs.size(); i++) {
		this->findSingleGraphPath(allPartialGraphs[i], startNodes[i]);
		this->mergePath();
		this->calculateSignalPathSRG(this->singlePaths_);
		this->calculateCirclePathSRG(this->pathsMapping_);
	}
}

vector<vector<PartialGraphNode>> TBDP::getNoCyclePaths() {
	return this->noCyclePaths_;
}

vector<vector<PartialGraphNode>> TBDP::getCyclePaths() {
	return this->cyclePaths_;
}

vector<vector<PartialGraphNode>> TBDP::getMergePaths() {
	return this->mergePaths_;
}

vector<vector<PartialGraphNode>> TBDP::getSinglePaths()
{
	return this->singlePaths_;
}

vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> TBDP::getPathsMapping()
{
	return this->pathsMapping_;
}

