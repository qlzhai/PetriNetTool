#pragma once

/*
* @Description: 用来处理输入文件的函数
* @Author: Qianlong Zhai
* @Date: 2024-07-16
* @LastEditTime: 2024-07-16
*/

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "PetriNet.h"

using namespace std;

class ReadFileInfo{
public:
    static ReadFileInfo& getInstance();

    // 从输入文件中获取库所数和变迁数
    void Getsize(int *rows, int *cols, string fileName);

    // 从输入文件中获取pre矩阵、post矩阵、关联矩阵、初始标记
    void LY_pnt2NW(string fileName, vector<vector<int>> &pre, vector<vector<int>> &post, vector<int> &M);
};