#pragma once
#include "SymbolicNode.h"

class SymbolicGraph
{
public:
	int state_number = 0;//用于标识当前共有多少个状态
	vector<int> enabled_trans;//当前标记下的使能变迁集合

	vector<StateNode> nodes;
	static SymbolicGraph& getInstance();
	vector<SymbolicNode> calculatePath(vector<PartialGraphNode> path);

	void FreshFirableTransition(VectorXi marking_);//计算标记marking的使能变迁集合

	VectorXi fireAtransition(VectorXi marking, int tran);//发射一个变迁

	StateNode* buildGraph();

	void printTransitionDelta(unordered_map<pair<int, int>, string, MyCompare> cur_transitionDelta);

	void printStateNode(const StateNode& node);

	vector<StateNode> getSRG();
private:
	static std::string Vector2String(Eigen::VectorXi Eigen_vector_int);
	int GetNodeNumberInVOld(const Eigen::VectorXi& mark) const;

	// 维护v_old_，反向检索某状态是否已出现过，因v_old_只需添加/检索无需遍历，用unordered_map/set更快
	std::unordered_map<std::string, std::pair<bool, int>> v_old_;

	void transPair(vector<int> firable_trans, vector<bool>& visited, vector<int>& path, vector<vector<int>>& result);//将使能变迁两两排列
	bool isNewEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran);//判断curFireTran是否是新使能变迁

	bool isContinuousEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran);//判断curFireTran是否是持续使能变迁

	map<int, bool> transProperty(VectorXi marking_cur, VectorXi marking_next, vector<int> firable_trans, int fireTran);//从marking_cur发射tran到达marking_next，marking_next下使能变迁的特性
};

