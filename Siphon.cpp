#include "Siphon.h"
Siphon& Siphon::getInstance() {
	static Siphon instance;
	return instance;
}
//使用递归方式生成从 n 个元素中选出 m 个元素的所有组合
void Siphon::combinations(int temp, int start, int n, int m, std::vector<int>& currentCombination, std::vector<std::vector<int>>& result) {
	if (m == 0) {
		result.push_back(currentCombination);
		return;
	}
	if (temp == 0) {
		for (int i = start; i <= n - m; i++) {
			currentCombination.push_back(i);
			combinations(0, i + 1, n, m - 1, currentCombination, result);
			currentCombination.pop_back();
		}
	}
	if (temp == 1) {
		for (int i = start; i <= n; i++) {
			currentCombination.push_back(i + 1);
			combinations(1, 0, n, m - 1, currentCombination, result);
			currentCombination.pop_back();
		}
	}
}

//判断v1是否是v2的真子集 v1中的元素是否都能在v2中找到
bool Siphon::isContainSiphons(vector<int> v1, vector<int> v2) {
	for (auto presetIt = v1.begin(); presetIt != v1.end(); presetIt++) {
		if (find(v2.begin(), v2.end(), *presetIt) == v2.end())
			return false;
	}
	return true;
}

//判断前置集是否属于后置集 也就是说，对于前置集中的每一个元素，在其后置集中是否都能找到
bool Siphon::isContain(set<int> postsetS, set<int> presetS) {
	for (auto presetIt = presetS.begin(); presetIt != presetS.end(); presetIt++) {
		if (find(postsetS.begin(), postsetS.end(), *presetIt) == postsetS.end())
			return false;
	}
	return true;
}

//求信标
vector<vector<int>> Siphon::siphons(vector<vector<int>> incidenceMatrix) {
	vector<vector<int>> siphons;
	int numsP = incidenceMatrix.size(); //库所数量
	int numsT = incidenceMatrix[0].size();//变迁数量

	//从库所集合中依次选出numsP个库所放到集合result中
	int numsS = 1; //信标中的库所数量 初始化为1
	vector<vector<int>> result;
	while (numsS <= numsP) {
		//cout << numsS << "-----------------------" << endl;
		vector<int> currentCombination;

		combinations(0, 0, numsP, numsS, currentCombination, result);

		numsS++;
	}

	//从result集合中依次选取某一个集合，求出其前置集和后置集   
	for (auto it = result.begin(); it != result.end(); it++) {
		vector<int> v = *it;
		set<int> presetS;//S的前置集
		set<int> postsetS;//S的后置集
		for (auto iit = v.begin(); iit != v.end(); iit++) {
			//求前置集
			for (int i = 0; i < incidenceMatrix[0].size(); i++) {
				if (incidenceMatrix[*iit][i] > 0) {
					presetS.insert(i);
				}
			}
			//求后置集
			for (int i = 0; i < incidenceMatrix[0].size(); i++) {
				if (incidenceMatrix[*iit][i] < 0) {
					postsetS.insert(i);
				}
			}
		}

		//判断前置集是否属于后置集 也就是说，对于前置集中的每一个元素，在其后置集中是否都能找到
		if (isContain(postsetS, presetS)) {
			//信标
			siphons.push_back(v);
		}
	}

	this->siphons_ = siphons;
	return siphons;
}

//求极小信标 称一个信标 (陷阱) 是极小的，当且仅当不存在其它信标(陷阱) 是它的真子集。
vector<vector<int>> Siphon::minSiphons(vector<vector<int>> incidenceMatrix) {
	vector<vector<int>> s = this->siphons_;//信标
	vector<vector<int>> s_copy = s;//信标
	for (auto it1 = s.begin(); it1 != s.end(); it1++) {
		vector<int> v1 = *it1;
		int temp = 0;
		for (auto it2 = s.begin(); it2 != s.end(); it2++, temp++) {
			vector<int> v2 = *it2;
			if (v1 == v2) {
				continue;
			}
			else {
				if (isContainSiphons(v1, v2)) {
					//v1是v2的真子集
					auto it3 = find(s_copy.begin(), s_copy.end(), v2);
					if (it3 != s_copy.end()) {
						s_copy.erase(it3);
					}
				}
			}
		}
	}
	this->minSiphons_ = s_copy;
	return s_copy;
}

//求严格极小信标
vector<vector<int>> Siphon::strictMinSiphons(vector<vector<int>> incidenceMatrix) {
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

	// 求解 P-不变式方程 AM = 0
	FullPivLU<MatrixXd> lu_decomp(N);
	MatrixXd I = lu_decomp.kernel();
	/*cout << "P-不变式" << endl;
	cout << I << endl;*/

	vector<vector<int>> SMS;

	vector<vector<int>> MS1 = this->minSiphons_;//求出极小信标
	//将极小信标转换成 0 1的形式
	vector<vector<int>> MS(MS1.size(), vector<int>(incidenceMatrix.size(), 0));
	for (int i = 0; i < MS1.size(); i++) {
		//cout << MS1[i].size() << endl;
		for (int j = 0; j < MS1[i].size(); j++) {
			int temp = MS1[i][j];
			MS[i][temp] = 1;
		}
	}

	//将极小信标出入到矩阵中
	Eigen::MatrixXd MSmatrix(MS.size(), incidenceMatrix.size());
	for (int i = 0; i < MS.size(); ++i) {
		for (int j = 0; j < incidenceMatrix.size(); ++j) {
			MSmatrix(i, j) = MS[i][j];
		}
	}

	//将极小信标矩阵进行转置
	MatrixXd MSmatrixT = MSmatrix.transpose();
	/*cout << "极小信标------------" << endl;
	cout << MSmatrixT << endl;*/

	//判断一个极小信标是否可以由P不变式线性表示
	int rankI = min(I.rows(), I.cols());
	for (int i = 0; i < MSmatrixT.cols(); i++) {
		MatrixXd temp = MSmatrixT.col(i);
		MatrixXd combinedMatrix(I.rows(), I.cols() + 1);
		combinedMatrix << I, temp;
		FullPivLU<Eigen::MatrixXd> lu_decomposition(combinedMatrix);
		int rank = lu_decomposition.rank();
		if (rank > rankI) {
			//cout << "无解" << endl;
			SMS.push_back(MS[i]);
		}
		else {
			//有解
			continue;
		}
	}

	//将严格极小信标转换为特征P-向量矩阵
	MatrixXd chaP_vector(SMS.size(), SMS[0].size());
	for (int i = 0; i < SMS.size(); ++i) {
		for (int j = 0; j < SMS[0].size(); ++j) {
			chaP_vector(i, j) = SMS[i][j];
		}
	}

	//求特征T-向量矩阵
	MatrixXd chaT_vector = chaP_vector * A;
	this->SMS_T_vector = chaT_vector;

	//不包含任何P-不变式的支撑的信标为严格信标
	this->strictMinSiphons_ = SMS;
	return SMS;
}

//基本信标
vector<vector<int>> Siphon::elemSiphons(vector<vector<int>> incidenceMatrix) {
	vector<vector<int>> ESMS;//elementary siphon 

	vector<vector<int>> SMS = this->strictMinSiphons_;//严格极小信标

	//将严格极小信标转换为特征P-向量矩阵
	MatrixXd chaP_vector(SMS.size(), SMS[0].size());
	for (int i = 0; i < SMS.size(); ++i) {
		for (int j = 0; j < SMS[0].size(); ++j) {
			chaP_vector(i, j) = SMS[i][j];
		}
	}
	/*cout << "chaP_vector:" << endl;
	cout << chaP_vector << endl;*/

	//求特征T-向量矩阵
	int numPlaces = incidenceMatrix.size();
	int numTransitions = incidenceMatrix[0].size();
	Eigen::MatrixXd A(numPlaces, numTransitions);
	for (int i = 0; i < numPlaces; ++i) {
		for (int j = 0; j < numTransitions; ++j) {
			A(i, j) = incidenceMatrix[i][j];
		}
	}
	MatrixXd chaT_vector = chaP_vector * A;

	this->SMS_T_vector = chaT_vector;
	/*cout << "chaT_vector:" << endl;
	cout << chaT_vector << endl;*/
	FullPivLU<Eigen::MatrixXd> lu_decomposition(chaT_vector);
	int rank = lu_decomposition.rank();
	//cout << "rank = " << rank << endl;

	//从SMS.size()个SMS中任意选择rank个信标
	vector<int> elements;
	for (int i = 0; i < SMS.size(); i++) {
		elements.push_back(i);
	}
	vector<vector<int>> result;
	vector<int> combination;
	combinations(0, 0, SMS.size(), rank, combination, result);

	for (int i = 0; i < result.size(); i++) {
		MatrixXd tempT_vector(rank, chaT_vector.cols());
		tempT_vector.setZero();
		for (int j = 0; j < result[0].size(); j++) {
			//cout << result[i][j] << " ";
			tempT_vector.row(j) = chaT_vector.row(result[i][j]);
		}
		//cout << endl;
		//cout << tempT_vector << endl;
		this->ESMS_T_vector = tempT_vector;
		FullPivLU<MatrixXd> lu_tempT_vector(tempT_vector);
		int ranktemp = lu_tempT_vector.rank();
		if (rank == ranktemp) {
			for (int z = 0; z < result[0].size(); z++) {
				ESMS.push_back(SMS[result[i][z]]);
			}
			break;
		}
		cout << std::endl;
	}

	this->EMS_ = ESMS;
	return ESMS;
}

vector<vector<int>> Siphon::getSiphons() {
	return this->siphons_;
}
vector<vector<int>> Siphon::getMinSiphons() {
	return this->minSiphons_;
}
vector<vector<int>> Siphon::getSMS() {
	return this->strictMinSiphons_;
}
vector<vector<int>> Siphon::getESMS() {
	return this->EMS_;
}
MatrixXd Siphon::getSMS_T_vector() {
	return this->SMS_T_vector;
}
MatrixXd Siphon::getESMS_T_vector() {
	return this->ESMS_T_vector;
}
