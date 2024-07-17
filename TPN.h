#pragma once
#include "PetriNet.h"
class TPN
{
public:
	unsigned int num_of_place_ = 0;
	unsigned int num_of_trans_ = 0;
	Eigen::MatrixXi input_matrix_;// 前置矩阵
	Eigen::MatrixXi output_matrix_;//后置矩阵
	VectorXi m0_;
	vector<vector<string>> parametricTime;

	static TPN& getInstance();
};

