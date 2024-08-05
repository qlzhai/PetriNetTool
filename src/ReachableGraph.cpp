#include "ReachableGraph.h"

ReachableGraph& ReachableGraph::getInstance(){
    static ReachableGraph instance;
    return instance;
}

bool ReachableGraph::addNode(const int& node_name,
                const VectorXi& marking,
                const vector<pair<int, int>>& transition_son){
    MarkingNode node;
    node.node_name_ = node_name;
    node.marking_ = marking;
    node.transition_to_son_ = transition_son;
    this->nodes_.emplace_back(node);
    return REACHABILITY_GRAPH_SUCCESS;
}

bool ReachableGraph::addNode(const int& node_name, const VectorXi& marking){
    MarkingNode node(node_name, marking);
    this->nodes_.emplace_back(node);
    return REACHABILITY_GRAPH_SUCCESS;
}

string ReachableGraph::VexXiToStr(VectorXi marking){
    string str = "";
    for(int i = 0; i < marking.rows(); i++){
        str = str + to_string(marking(i)) + " ";
    }
    str = str.substr(0, str.size() - 1);
    return str;
}

int ReachableGraph::getNodeIndex(VectorXi marking){
    string marking_str = this->VexXiToStr(marking);
    auto it = this->v_old_.find(marking_str);
    if(it == this->v_old_.end()){
        return -1;
    }
    return it->second;
}

vector<int> ReachableGraph::freshEnabledTrans(VectorXi cur_marking){
    VectorXi temp_marking(PetriNet::getInstance().nums_place);
    vector<int> enabled_trans;
    for(int i = 0; i < PetriNet::getInstance().nums_transition; i++){
        temp_marking = cur_marking - PetriNet::getInstance().pre_matrix.col(i);
        bool flag = true;
        for(auto& j : temp_marking){
            flag = (j >= 0) & flag;
        }
        if(flag) enabled_trans.emplace_back(i);
    }
    return enabled_trans;
}

VectorXi ReachableGraph::fireOneTran(VectorXi cur_marking, int t){
    VectorXi next_marking = cur_marking 
                            + PetriNet::getInstance().post_matrix.col(t) 
                            - PetriNet::getInstance().pre_matrix.col(t);
    return next_marking;
}

size_t ReachableGraph::hashVector(VectorXi& vec) {
    std::hash<int> hasher;
    size_t hash = 0;
    for (const int& elem : vec) {
        hash ^= hasher(elem) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
}

bool ReachableGraph::buildReachableGraph(){
    this->v_new_.clear();
    this->v_old_.clear();
    this->nodes_.clear();

    this->marking_number = 0;

    // 将初始标记添加到可达图中
    this->v_new_.emplace_back(PetriNet::getInstance().M0_matrix);
    this->v_old_.emplace(this->VexXiToStr(PetriNet::getInstance().M0_matrix), marking_number);
    this->addNode(marking_number, PetriNet::getInstance().M0_matrix);
    
    cout << "original: " << endl;
    while(!this->v_new_.empty()){
        VectorXi cur_marking = this->v_new_.back();
        this->v_new_.pop_back();
        int cur_index = this->getNodeIndex(cur_marking);
        vector<int> enabled_trans = ReachableGraph::freshEnabledTrans(cur_marking);

        for(auto& t : enabled_trans){
            VectorXi next_marking = ReachableGraph::fireOneTran(cur_marking, t);

            //将向量转换成字符串判重
            int next_index = this->getNodeIndex(next_marking);
            if(next_index == -1){
                this->marking_number++;
                //cout << "marking_number: " << marking_number << endl;
                v_new_.emplace_back(next_marking);
                v_old_.emplace(this->VexXiToStr(next_marking), this->marking_number);
                this->addNode(marking_number, next_marking);
            }
            nodes_[cur_index].transition_to_son_.emplace_back(make_pair(t, marking_number));
        }
    }

    return REACHABILITY_GRAPH_SUCCESS;
}

bool ReachableGraph::buildReachableGraphHash(){
    this->v_new_.clear();
    this->v_old_.clear();
    this->nodes_.clear();

    this->marking_number = 0;

    // 将初始标记添加到可达图中
    this->v_new_.emplace_back(PetriNet::getInstance().M0_matrix);
    this->v_old_.emplace(this->VexXiToStr(PetriNet::getInstance().M0_matrix), marking_number);
    this->addNode(marking_number, PetriNet::getInstance().M0_matrix);

    size_t hash_value = this->hashVector(PetriNet::getInstance().M0_matrix);
    this->hash_table[hash_value] = PetriNet::getInstance().M0_matrix;
    
    cout << "by hashvalue: " << endl;
    while(!this->v_new_.empty()){
        VectorXi cur_marking = this->v_new_.back();
        this->v_new_.pop_back();
        int cur_index = this->getNodeIndex(cur_marking);
        vector<int> enabled_trans = ReachableGraph::freshEnabledTrans(cur_marking);

        for(auto& t : enabled_trans){
            VectorXi next_marking = ReachableGraph::fireOneTran(cur_marking, t);
            
            //计算hash值 判重
            hash_value = this->hashVector(next_marking);
            if(hash_table.find(hash_value) == hash_table.end()){
                this->marking_number++;
                //cout << "marking_number: " << marking_number << endl;
                v_new_.emplace_back(next_marking);
                v_old_.emplace(this->VexXiToStr(next_marking), this->marking_number);
                this->addNode(marking_number, next_marking);
                hash_table[hash_value] = next_marking; 
            }
            nodes_[cur_index].transition_to_son_.emplace_back(make_pair(t, marking_number));
        }
    }

    return REACHABILITY_GRAPH_SUCCESS;
}

bool ReachableGraph::buildReachableGraphTrie(){
    this->v_new_.clear();
    this->v_old_.clear();
    this->nodes_.clear();

    this->marking_number = 0;

    // 将初始标记添加到可达图中
    this->v_new_.emplace_back(PetriNet::getInstance().M0_matrix);
    this->v_old_.emplace(this->VexXiToStr(PetriNet::getInstance().M0_matrix), marking_number);
    this->addNode(marking_number, PetriNet::getInstance().M0_matrix);
    
    Trie tree;
    tree.search(PetriNet::getInstance().M0_matrix);

    cout << "by Trie: " << endl;
    while(!this->v_new_.empty()){
        VectorXi cur_marking = this->v_new_.back();
        this->v_new_.pop_back();
        int cur_index = this->getNodeIndex(cur_marking);
        vector<int> enabled_trans = ReachableGraph::freshEnabledTrans(cur_marking);

        for(auto& t : enabled_trans){
            VectorXi next_marking = ReachableGraph::fireOneTran(cur_marking, t);

            tree.insert(next_marking);
            if(tree.isexist == false){
                //不存在
                this->marking_number++;
                //cout << "marking_number: " << marking_number << endl;
                v_new_.emplace_back(next_marking);
                v_old_.emplace(this->VexXiToStr(next_marking), this->marking_number);
                this->addNode(marking_number, next_marking);
            }
            nodes_[cur_index].transition_to_son_.emplace_back(make_pair(t, marking_number));
            tree.isexist = true;

            /*bool flag = tree.search(next_marking);
            if(flag == false){
                //不存在
                this->marking_number++;
                //cout << "marking_number: " << marking_number << endl;
                v_new_.emplace_back(next_marking);
                v_old_.emplace(this->VexXiToStr(next_marking), this->marking_number);
                this->addNode(marking_number, next_marking);
                tree.insert(next_marking);
            }
            nodes_[cur_index].transition_to_son_.emplace_back(make_pair(t, marking_number));*/
        }
    }

    return REACHABILITY_GRAPH_SUCCESS;
}

vector<MarkingNode> ReachableGraph::getReachableGraphNodes(){
    return this->nodes_;
}
