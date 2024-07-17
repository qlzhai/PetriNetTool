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

class PetriNet
{
public:
	unsigned int num_of_place_ = 0;
	unsigned int num_of_trans_ = 0;
	Eigen::MatrixXi input_matrix_;// 前置矩阵
	Eigen::MatrixXi output_matrix_;//后置矩阵
	VectorXi m0_;
	Eigen::MatrixXi trans_matrix_;
	vector<vector<int>> incidenceMatrix_;

	static PetriNet& getInstance();
};

