#pragma once

#include <iostream>
#include <vector>
#include <Eigen\Dense>

#include "PetriNet.h"
using namespace std;
using namespace Eigen;

class StructuralPro : public PetriNet
{
private:
	vector<vector<int>> P_invariant;
	vector<vector<int>> T_invariant;
public:
	static StructuralPro& getInstance();
	vector<vector<int>> computeTInvariant(const std::vector<std::vector<int>>& incidenceMatrix);// 计算Petri网的T-不变式
	vector<vector<int>> computePInvariant(const std::vector<std::vector<int>>& incidenceMatrix);// 计算Petri网的P-不变式
	vector<vector<int>> get_P_invariant();
	vector<vector<int>> get_T_invariant();
};

