#pragma once

#include "PetriNet.h"
#include <unordered_map>

#define REACHABILITY_GRAPH_SUCCESS true
#define REACHABILITY_GRAPH_FAIL false

class ReachableGraph
{
private:
    int marking_number = 0; // 用于表示当前共有多少个状态
    vector<VectorXi> v_new_; // 保存已出现但未激发的标记
    unordered_map<string, int> v_old_; // 用来记录已经生成的节点 
    vector<MarkingNode> nodes_; //可达图中所有节点信息

    bool addNode(const int& node_name,
                const VectorXi& marking,
                const vector<pair<int, int>>& transition_son);
    bool addNode(const int& node_name, const VectorXi& marking);
    string VexXiToStr(VectorXi marking); //将vectorxi转换成string
    int getNodeIndex(VectorXi marking); //查询某个标记的编号
    vector<int> freshEnabledTrans(VectorXi cur_marking); // 计算当前标记cur_marking的使能变迁的集合
    VectorXi fireOneTran(VectorXi cur_marking, int t); //从cur_marking发射一个变迁t
public:
    static ReachableGraph& getInstance();

    bool buildReachableGraph(); // 构建可达图
    vector<MarkingNode> getReachableGraphNodes(); // 外部获取可达图节点
};