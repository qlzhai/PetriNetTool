#pragma once

#include <iostream>
#include <vector>
#include <eigen/core>
#include <eigen/SparseCore>
#include <Eigen\Dense>
#include <unordered_map>
#include <utility>

using namespace std;
using namespace Eigen;

class MarkingNode
{
public:
	int node_name_ = -1;// 状态节点的编号（Name）
	Eigen::VectorXi marking_;// 本节点状态, Mi = {P1,P2,P3...}
	std::vector<std::pair<int, int>> transition_to_son_;// pair<which_transition, son_node>

	MarkingNode(int node_name, Eigen::VectorXi marking);
	MarkingNode() = default;

	//函数加上const后缀作用是限定函数内部实现对类成员变量具有只读权限
	//引用的作用避免了函数在调用时对实参的一次拷贝
	bool operator==(const MarkingNode& node) {
		if (this->node_name_ == node.node_name_) {
			return true;
		}
		return false;
	}

	bool operator<(const MarkingNode& node) const {
		if (this->node_name_ > node.node_name_) {
			return false;
		}
		return true;
	}

	/*bool operator()(const MarkingNode& node) const {
		return this->node_name_ < node.node_name_;
	}*/
};

