#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <Eigen\Dense>
#include "PetriNet.h"
#include "StructuralPro.h"

class Siphon :public PetriNet
{
private:
	vector<vector<int>> siphons_;//信标
	vector<vector<int>> minSiphons_;//极小信标
	vector<vector<int>> strictMinSiphons_;//严格极小信标
	vector<vector<int>> EMS_;//基本信标
	MatrixXd SMS_T_vector; //严格极小信标对应的特征T向量
	MatrixXd ESMS_T_vector; //基本信标对应的特征T向量
public:
	static Siphon& getInstance();
	//使用递归方式生成从 n 个元素中选出 m 个元素的所有组合
	void combinations(int temp, int start, int n, int m, std::vector<int>& currentCombination, std::vector<std::vector<int>>& result);

	//判断v1是否是v2的真子集 v1中的元素是否都能在v2中找到
	bool isContainSiphons(vector<int> v1, vector<int> v2);

	//判断前置集是否属于后置集 也就是说，对于前置集中的每一个元素，在其后置集中是否都能找到
	bool isContain(set<int> postsetS, set<int> presetS);

	//求信标
	vector<vector<int>> siphons(vector<vector<int>> incidenceMatrix);

	//求极小信标
	vector<vector<int>> minSiphons(vector<vector<int>> incidenceMatrix);

	//求严格极小信标
	vector<vector<int>> strictMinSiphons(vector<vector<int>> incidenceMatrix);

	//基本信标
	vector<vector<int>> elemSiphons(vector<vector<int>> incidenceMatrix);

	vector<vector<int>> getSiphons();
	vector<vector<int>> getMinSiphons();
	vector<vector<int>> getSMS();
	vector<vector<int>> getESMS();
	MatrixXd getSMS_T_vector();
	MatrixXd getESMS_T_vector();
};

