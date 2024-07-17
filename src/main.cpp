#include "read.h"
#include "ReachableGraph.h"
#include "StructuralPro.h"

#include <chrono>

#define INPUT_FILE_NAME "../pnt/r5.pnt"

int main()
{   
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::milliseconds duration;

    cout << "开始初始化Petri网数据..." << endl;
    ReadFileInfo::getInstance().initPetriNet(INPUT_FILE_NAME);
    cout << "初始化Petri网数据完成..." << endl;

    //计算可达图
    cout << "开始计算可达图..." << endl;
    start = std::chrono::high_resolution_clock::now();
    ReachableGraph::getInstance().buildReachableGraph();
    vector<MarkingNode> nodes = ReachableGraph::getInstance().getReachableGraphNodes();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "可达图计算完成，一共有 " << nodes.size() << " 个标记." << endl;
    cout << "所用时间 " << duration.count() << " ms." << endl;
    cout << endl;
    cout << endl;

    //计算结构特性 P-不变式 T-不变式
    cout << "开始计算结构特性..." << endl;
    start = std::chrono::high_resolution_clock::now();
    StructuralPro::getInstance().computePInvariant(PetriNet::getInstance().incidence_vector);
    StructuralPro::getInstance().computeTInvariant(PetriNet::getInstance().incidence_vector);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "结构特性计算完毕." << endl;
    cout << "所用时间 " << duration.count() << " ms." << endl;
    cout << endl;

    cout << "P-Invariants: " << endl;
    vector<vector<int>> p_Invariants = StructuralPro::getInstance().get_P_invariant();
    for(int i = 0; i < p_Invariants.size(); i++){
        for(int j = 0; j < p_Invariants[0].size(); j++){
            cout << p_Invariants[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "T-Invariants: " << endl;
    vector<vector<int>> t_Invariants = StructuralPro::getInstance().get_T_invariant();
    for(int i = 0; i < t_Invariants.size(); i++){
        for(int j = 0; j < t_Invariants[0].size(); j++){
            cout << t_Invariants[i][j] << " ";
        }
        cout << endl;
    }
    system("read -p 'Press Enter to Continue...' var");//系统调用
    return 0;
}