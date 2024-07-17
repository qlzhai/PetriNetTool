#pragma once
#include <iostream>
#include <vector>
#include <Eigen\Dense>
#include <queue>
#include <map>
#include "PetriNet.h"
#include "Siphon.h"
#include "MarkingNode.h"

using namespace std;
using namespace Eigen;

class DeadlockPrevention
{
private:
	vector<vector<int>> DPSMSmatrix;//采用SMS死锁预防后网的关联矩阵
	vector<int> DPSMSmarking;//采用SMS死锁预防后网的初始标记

	vector<vector<int>> DPESMSmatrix;//采用ESMS死锁预防后网的关联矩阵
	vector<int> DPESMSmarking;//采用ESMS死锁预防后网的初始标记

	vector<pair<int, int>> MTSI_;
	vector<MarkingNode> FBM_;
public:
	static DeadlockPrevention& getInstance();

	vector<MarkingNode> pathNode;//路过的节点的集合
	vector<vector<MarkingNode>> allPathNode;//所有路径的集合

	int numsDeadMarking(vector<int> marking, vector<vector<int>> matrix);
	bool SMSdeadlock();
	bool ESMSdeadlock();

	vector<vector<int>> getDPSMSmatrix();
	vector<int> getDPSMSmarking();

	vector<vector<int>> getDPESMSmatrix();
	vector<int> getDPESMSmarking();

	vector<pair<int, int>> calcuMTSI(vector<MarkingNode> legalMarking, vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking);//获取状态变迁分离实例

	vector<pair<int, int>> getMTSI();
	vector<MarkingNode> getFBM();

	void pathAtoB(MarkingNode nodeA, MarkingNode nodeB, vector<MarkingNode> RGnodes);//节点A到节点B经过的节点
	void pathAtoA(MarkingNode nodeA, MarkingNode nodeB, vector<MarkingNode> RGnodes);//环路径

	vector<int> pathTransition(vector<MarkingNode> node, int numsTransition);

	void modifyTimePlaceSupervisor(vector<MarkingNode> RGnodes, vector<MarkingNode> legalMarking, vector<MarkingNode> dangerousMarking,
		vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking, int numsTransition);

	void modifyTimePlaceSupervisor2(vector<MarkingNode> RGnodes, vector<MarkingNode> legalMarking, vector<MarkingNode> dangerousMarking,
		vector<MarkingNode> badMarking, vector<MarkingNode> deadMarking, int numsTransition);
};

