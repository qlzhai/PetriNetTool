#pragma once
#include "ReachableGraph.h"

class PartialGraphNode {
public:
	int node_name_ = -1;// 状态节点的编号（Name）
	VectorXi marking_;// 本节点状态, Mi = {P1,P2,P3...}
	vector<std::pair<int, int>> transition_to_son_;// pair<which_transition, son_node>
	vector<int> trans;

	bool operator==(const PartialGraphNode& node) {
		if (this->node_name_ == node.node_name_) {
			return true;
		}
		return false;
	}
};
