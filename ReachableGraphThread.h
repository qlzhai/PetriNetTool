#pragma once

#include <iostream>
#include <vector>
#include <eigen/core>
#include <eigen/SparseCore>
#include <Eigen\Dense>
#include <unordered_map>
#include <utility>
#include <queue>
#include <unordered_set>

#include "PetriNet.h"
#include "MarkingNode.h"

#define REACHABILITY_GRAPH_SUCCESS true
#define REACHABILITY_GRAPH_FAIL false

using namespace std;
using namespace Eigen;

class ReachableGraph
{
private:
	//用来记录SRG是否是无限的
	bool SRGinfinite = false;

	// 用于标识当前共有多少个状态
	int marking_number_ = 0;
	// 维护v_new_，保存已出现但未激发的状态，因为v_new_需遍历/增删首尾元素，用vector较合理
	std::vector<Eigen::VectorXi> v_new_;
	// 维护v_old_，反向检索某状态是否已出现过，因v_old_只需添加/检索无需遍历，用unordered_map/set更快
	std::unordered_map<std::string, std::pair<bool, int>> v_old_;

	// 维护nodes_结构体数组表示可达图
	std::vector<MarkingNode> nodes_;

	unordered_map<int, vector<int>> partialGraph_;

	vector<MarkingNode> deadMarkings_;//死标记
	vector<MarkingNode> badMarkings_;//坏标记
	vector<MarkingNode> dangerousMarkings_;//危险标记
	vector<MarkingNode> goodMarkings_;//好标记
	vector<MarkingNode> legalMarkings_;//合法标记

	bool AddNode(const int& node_name,
		const Eigen::VectorXi& marking,
		const std::vector<std::pair<int, int>>& transition_to_son);
	bool AddNode(const int& node_name,
		const Eigen::VectorXi& marking);
	//TODO: 因为不想自己写hash函数，所以多绕一步将vector转化为string
	static std::string Vector2String(Eigen::VectorXi Eigen_vector_int);
	int GetNodeNumberInVOld(const Eigen::VectorXi& mark) const;
	bool GetNodeStatusInVOld(const Eigen::VectorXi& mark) const;
	bool SetNodeFiredInVOld(const Eigen::VectorXi& mark);

	// 激发一个transition，并改变petri net的marking
	VectorXi FiringATransition(VectorXi cur_marking, int t);

	void dfs(vector<MarkingNode> nodes, MarkingNode start, MarkingNode current, vector<bool>& visited, vector<MarkingNode>& path, vector<vector<MarkingNode>>& cycles);

	bool isExistContinuousTran(MarkingNode left, MarkingNode right);

	bool isSafeCirPath(vector<MarkingNode> nodes);

	bool isLegalMarking(VectorXi saveM0);

	bool isDangerousMarking(MarkingNode node);
public:
	static ReachableGraph& getInstance();
	bool isContinuousEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran);
	bool isNewEnabledTransition(VectorXi marking_cur, VectorXi marking_next, int fireTran, int curFireTran);
	vector<int> FreshFirableTransition(VectorXi marking_);
	bool BuildReachabilityGraph();
	const std::vector<MarkingNode>& GetNodes() const;

	vector<vector<MarkingNode>> CalculateCircularPath(vector<MarkingNode> nodes);
	bool isSRGinfinite(vector<vector<MarkingNode>> circularPaths);

	bool isSRGinfinite();

	void markingClassification();

	//外部获取死标记、危险标记、坏标记、好标记、合法标记
	vector<MarkingNode> getDeadMarkings();
	vector<MarkingNode> getDangerousMarkings();
	vector<MarkingNode> getBadMarkings();
	vector<MarkingNode> getGoodMarkings();
	vector<MarkingNode> getLegalMarkings();
};

