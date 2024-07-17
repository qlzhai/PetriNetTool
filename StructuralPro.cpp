#include "StructuralPro.h"

StructuralPro& StructuralPro::getInstance() {
	// TODO: 在此处插入 return 语句
	static StructuralPro instance;
	return instance;
}

// 计算Petri网的T-不变式
vector<vector<int>> StructuralPro::computeTInvariant(const std::vector<std::vector<int>>& incidenceMatrix) {
	int numPlaces = incidenceMatrix.size();
	int numTransitions = incidenceMatrix[0].size();
	// 将变迁关系矩阵转换为Eigen矩阵
	Eigen::MatrixXd A(numPlaces, numTransitions);
	for (int i = 0; i < numPlaces; ++i) {
		for (int j = 0; j < numTransitions; ++j) {
			A(i, j) = incidenceMatrix[i][j];
		}
	}
	// 求解 T-不变式方程 AM = 0
	FullPivLU<MatrixXd> lu_decomp(A);
	MatrixXd M = lu_decomp.kernel();
	// 将结果转换为vector数组形式
	std::vector<vector<int>> tInvariant(M.cols(), vector<int>(numTransitions, 0));
	for (int i = 0; i < M.cols(); i++) {
		for (int j = 0; j < M.rows(); j++) {
			//cout << M(j,i) <<" ";
			tInvariant[i][j] = M(j, i);
		}
	}
	this->T_invariant = tInvariant;
	return tInvariant;
}

// 计算Petri网的P-不变式
vector<vector<int>> StructuralPro::computePInvariant(const std::vector<std::vector<int>>& incidenceMatrix) {
	int numPlaces = incidenceMatrix.size();
	int numTransitions = incidenceMatrix[0].size();
	// 将变迁关系矩阵转换为Eigen矩阵
	Eigen::MatrixXd A(numPlaces, numTransitions);
	for (int i = 0; i < numPlaces; ++i) {
		for (int j = 0; j < numTransitions; ++j) {
			A(i, j) = incidenceMatrix[i][j];
		}
	}
	//将关系矩阵A进行转置
	MatrixXd N = A.transpose();
	// 求解 T-不变式方程 AM = 0
	FullPivLU<MatrixXd> lu_decomp(N);
	MatrixXd M = lu_decomp.kernel();
	//cout << M << endl;
	// 将结果转换为标记向量
	std::vector<vector<int>> pInvariant(M.cols(), vector<int>(numPlaces, 0));
	for (int i = 0; i < M.cols(); i++) {
		for (int j = 0; j < M.rows(); j++) {
			//cout << M(j,i) <<" ";
			pInvariant[i][j] = M(j, i);
		}
	}
	this->P_invariant = pInvariant;
	return pInvariant;
}
vector<vector<int>> StructuralPro::get_P_invariant() {
	return this->P_invariant;
}
vector<vector<int>> StructuralPro::get_T_invariant() {
	return this->T_invariant;
}