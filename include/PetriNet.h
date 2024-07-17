#pragma once

#include <iostream>
#include <vector>
#include <eigen-3.4.0/Eigen/Dense>

using namespace std;
using namespace Eigen;

class PetriNet{
public:
    int nums_place = 0;
    int nums_transition = 0;

    vector<int> M0_vector; //初始标记M0的vector形式
    vector<vector<int>> pre_incidence; //前置矩阵vector形式
    vector<vector<int>> post_incidence; //后置矩阵vector形式

    Eigen::MatrixXi pre_matrix; //前置矩阵matrix形式
    Eigen::MatrixXi post_matrix; //后置矩阵matrix形式
    Eigen::VectorXi M0_matrix; //初始标记M0的matrix形式

    static PetriNet& getInstance();
};
