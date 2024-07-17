#include "read.h"
#include "ReachableGraph.h"

#define INPUT_FILE_NAME "../pnt/r5.pnt"

int main()
{   
    ReadFileInfo::getInstance().initPetriNet(INPUT_FILE_NAME);
    ReachableGraph::getInstance().buildReachableGraph();
    vector<MarkingNode> nodes = ReachableGraph::getInstance().getReachableGraphNodes();
    cout << "there are total " << nodes.size() << " markings." << endl;
    return 0;
}