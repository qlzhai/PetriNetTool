#pragma once
#include <vector>
#include <eigen/core>
#include <eigen/SparseCore>
#include <Eigen\Dense>
#include <algorithm>

#include "MarkingNode.h"
#include "ReachableGraph.h"
#include "PetriNet.h"
#include "DeadlockPrevention.h"
#include "StructuralPro.h"

using namespace std;

class TheoryOfRegion
{
private:
	vector<vector<int>> legalPaths_;
	vector<vector<int>> iLegalPaths_;

	vector<string> T_InvariantsConditions_;
	vector<string> iLegalConditions_;
	vector<vector<string>> legalConditions_;

	//计算m0到target的发射序列
	void calculateM0ToSingle(vector<MarkingNode>& RG, vector<bool>& visited, MarkingNode m0, MarkingNode current,
		MarkingNode target, vector<int>& path, vector<vector<int>>& paths);
public:
	static TheoryOfRegion& getInstance();
	void calculateLegalPath();//计算合法的路径
	void constraints();
	vector<string> getT_InvariantsConditions_();
	vector<string> getiLegalConditions_();
	vector<vector<string>> getlegalConditions_();
};

