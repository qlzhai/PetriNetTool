#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <eigen/core>
#include <eigen/SparseCore>
#include <Eigen\Dense>
#include <unordered_map>
#include <utility>

#include "MyCompare.h"
#include "PartialGraphNode.h"
#include "MarkingNode.h"
#include "TPN.h"
#include "StateNode.h"
#include "MyString.h"

using namespace std;
using namespace Eigen;

class SymbolicNode
{
public:
	int node_name_ = -1;// 状态节点的编号（Name）
	Eigen::VectorXi marking_;// 本节点标记, Mi = {P1,P2,P3...}
	unordered_map<pair<int, int>, string, MyCompare> transitionDelta;

	unordered_map<pair<int, int>, string, MyCompare> transitionDelta_temp;

	unordered_map<int, int> tranSon;//发射变迁->子节点

	//函数加上const后缀作用是限定函数内部实现对类成员变量具有只读权限
	//引用的作用避免了函数在调用时对实参的一次拷贝
	bool operator==(SymbolicNode node) const {
		//判断marking是否相等
		bool flagMarking = true;
		for (int i = 0; i < this->marking_.size(); i++) {
			if (node.marking_(i) != this->marking_(i)) {
				flagMarking = false;
				return false;
			}
		}

		bool flagDelta = true;
		int thisSize = this->transitionDelta_temp.size();
		int curSize = node.transitionDelta_temp.size();

		if (thisSize != curSize) {
			flagDelta = false;
			return false;
		}

		if (thisSize <= 1) return true;

		for (auto& delta : this->transitionDelta_temp) {
			if (node.transitionDelta_temp.count(pair<int, int>(delta.first.first, delta.first.second)) == 0) {
				return false;
			}
			else {
				pair<int, int> curPair = pair<int, int>(delta.first.first, delta.first.second);
				string s = node.transitionDelta_temp[curPair];
				if (s != delta.second) {
					return false;
				}
			}
		}
		return true;
	}
};
