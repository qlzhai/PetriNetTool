#include "TheoryOfRegion.h"

TheoryOfRegion& TheoryOfRegion::getInstance()
{
	static TheoryOfRegion instance;
	return instance;
}

void TheoryOfRegion::calculateM0ToSingle(vector<MarkingNode>& RG, vector<bool>& visited, MarkingNode m0, MarkingNode current,
	MarkingNode target, vector<int>& path, vector<vector<int>>& paths) {
	if (current == target) {
		if (find(paths.begin(), paths.end(), path) == paths.end()) {
			for (auto value : path) {
				cout << value << " ";
			}
			cout << endl;
			paths.push_back(path);
			return;
		}
	}

	for (int i = 0; i < current.transition_to_son_.size(); i++) {
		if (visited[current.transition_to_son_[i].second] == false) {
			//当前节点的下一个节点没有访问过
			path[current.transition_to_son_[i].first]++;
			visited[current.transition_to_son_[i].second] = true;
			for (auto node : RG) {
				if (node.node_name_ == current.transition_to_son_[i].second) {
					this->calculateM0ToSingle(RG, visited, m0, node, target, path, paths);
					break;
				}
			}
			path[current.transition_to_son_[i].first]--;
			//visited[current.transition_to_son_[i].second] = false;
		}
	}
}

void TheoryOfRegion::calculateLegalPath() {
	vector<MarkingNode> RG = ReachableGraph::getInstance().GetNodes();
	MarkingNode m0 = RG[0];
	vector<vector<int>> legalPaths;

	vector<pair<int, int>> v = DeadlockPrevention::getInstance().getMTSI();

	vector<MarkingNode> deadMarkings = ReachableGraph::getInstance().getDeadMarkings();//死标记
	vector<MarkingNode> badMarkings = ReachableGraph::getInstance().getBadMarkings();//坏标记
	vector<MarkingNode> dangerousMarkings = ReachableGraph::getInstance().getDangerousMarkings();//危险标记
	vector<MarkingNode> goodMarkings = ReachableGraph::getInstance().getGoodMarkings();//好标记
	vector<MarkingNode> legalMarkings = ReachableGraph::getInstance().getLegalMarkings();// 合法标记

	//合法路径
	cout << "legalpath: " << endl;
	for (int i = 0; i < legalMarkings.size(); i++) {
		vector<bool> visited(RG.size(), false);
		visited[0] = true;
		vector<int> path(PetriNet::getInstance().num_of_trans_, 0);
		this->calculateM0ToSingle(legalMarkings, visited, m0, m0, legalMarkings[i], path, legalPaths);
	}

	this->legalPaths_ = legalPaths;

	//非法路径
	cout << "ilegalpath: " << endl;
	vector<vector<int>> iLegalPaths;
	vector<MarkingNode> fbm = DeadlockPrevention::getInstance().getFBM();
	for (int i = 0; i < fbm.size(); i++) {
		vector<bool> visited(RG.size(), false);
		visited[0] = true;
		vector<int> path(PetriNet::getInstance().num_of_trans_, 0);
		this->calculateM0ToSingle(RG, visited, m0, m0, fbm[i], path, iLegalPaths);
	}

	this->iLegalPaths_ = iLegalPaths;
}

void TheoryOfRegion::constraints() {
	vector<vector<int>> legalPaths = this->legalPaths_;
	vector<vector<int>> iLegalPaths = this->iLegalPaths_;

	//设置控制器名称 pc1 pc2 pc3......
	vector<string> controllers;
	for (int i = 0; i < iLegalPaths.size(); i++) {
		string c = "pc" + to_string(i + 1);
		controllers.push_back(c);
	}

	vector<string> T_InvariantsConditions;
	vector<vector<int>> T_Invariant = StructuralPro::getInstance().get_T_invariant();
	for (int j = 0; j < T_Invariant.size(); j++) {
		string T_InvariantCondition = "";
		vector<int> t_invariant = T_Invariant[j];
		for (int k = 0; k < t_invariant.size(); k++) {
			if (t_invariant[k] == 0) {
				continue;
			}
			else if (t_invariant[k] == 1) {
				T_InvariantCondition = T_InvariantCondition + "+t" + to_string(k);
			}
			else {
				T_InvariantCondition = T_InvariantCondition + "+" + to_string(t_invariant[k]) + "*" + "t" + to_string(k);
			}
		}
		T_InvariantCondition += "=0";
		T_InvariantCondition = T_InvariantCondition.substr(1);
		cout << "T_InvariantCondition: " << T_InvariantCondition << endl;
		T_InvariantsConditions.push_back(T_InvariantCondition);
	}
	this->T_InvariantsConditions_ = T_InvariantsConditions;

	vector<string> iLegalconditions;
	vector<vector<string>> legalConditions;
	for (int i = 0; i < iLegalPaths.size(); i++) {
		string iLegalcondition = controllers[i];
		vector<int> iLegalpath = iLegalPaths[i];
		for (int j = 0; j < iLegalpath.size(); j++) {
			if (iLegalpath[j] == 0) {
				continue;
			}
			else if (iLegalpath[j] == 1) {
				iLegalcondition = iLegalcondition + "+t" + to_string(j);
			}
			else {
				iLegalcondition = iLegalcondition + "+" + to_string(iLegalpath[j]) + "*" + "t" + to_string(j);
			}
		}
		iLegalcondition += "<=-1";
		cout << "iLegalcondition: " << iLegalcondition << endl;
		iLegalconditions.push_back(iLegalcondition);

		vector<string> legalCondition;
		for (int j = 0; j < legalPaths.size(); j++) {
			vector<int> legalPath = legalPaths[j];
			string legalcondition = controllers[i];
			for (int k = 0; k < legalPath.size(); k++) {
				if (legalPath[k] == 0) {
					continue;
				}
				else if (legalPath[k] == 1) {
					legalcondition = legalcondition + "+t" + to_string(k);
				}
				else {
					legalcondition = legalcondition + "+" + to_string(legalPath[k]) + "*" + "t" + to_string(k);
				}
			}
			legalcondition += ">=0";
			cout << "legalcondition: " << legalcondition << endl;
			legalCondition.push_back(legalcondition);
		}
		legalConditions.push_back(legalCondition);
	}
	this->iLegalConditions_ = iLegalconditions;
	this->legalConditions_ = legalConditions;
}

vector<string> TheoryOfRegion::getT_InvariantsConditions_() {
	return this->T_InvariantsConditions_;
}
vector<string> TheoryOfRegion::getiLegalConditions_() {
	return this->iLegalConditions_;
}
vector<vector<string>> TheoryOfRegion::getlegalConditions_() {
	return this->legalConditions_;
}
