#pragma once

#include "PetriNet.h"
#include "Trie.h"
#include <unordered_map>
#include <functional>

#define REACHABILITY_GRAPH_SUCCESS true
#define REACHABILITY_GRAPH_FAIL false

class ReachableGraph
{
private:
    int marking_number = 0; // 用于表示当前共有多少个状态
    vector<VectorXi> v_new_; // 保存已出现但未激发的标记
    vector<TrieNode*> v_new_TrieNodes; //保存出现但是为激发的标记，在Trie_List中使用
    unordered_map<string, int> v_old_; // 用来记录已经生成的节点 
    unordered_map<size_t, int> hash_table; // hash值 序号
    vector<MarkingNode> nodes_; // 可达图中所有节点信息

    bool addNode(const int& node_name,
                const VectorXi& marking,
                const vector<pair<int, int>>& transition_son);
    bool addNode(const int& node_name, const VectorXi& marking);
    string VexXiToStr(VectorXi marking); //将vectorxi转换成string
    int getNodeIndex(VectorXi marking); //查询某个标记的编号
    vector<int> freshEnabledTrans(VectorXi cur_marking); // 计算当前标记cur_marking的使能变迁的集合
    VectorXi fireOneTran(VectorXi cur_marking, int t); //从cur_marking发射一个变迁t

    size_t hashVector(VectorXi& vec);
public:
    static ReachableGraph& getInstance();

    bool buildReachableGraph(); // 构建可达图
    bool buildReachableGraphHash(); // 构建可达图-Hash
    bool buildReachableGraphTrie(); // 构建可达图-字典树
    bool buildReachableGraphTrie_List(); // 构建可达图 -字典树 & 链表
    vector<MarkingNode> getReachableGraphNodes(); // 外部获取可达图节点
    int getMarkingNumber(); // 获取标记数量
};