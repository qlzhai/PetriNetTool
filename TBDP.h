#pragma once
#include "ReachableGraph.h"
#include "PartialGraphNode.h"
#include "SymbolicGraph.h"
#include <set>
#include <map>
#include "MyPathString.h"

using namespace std;

class TBDP
{
private:
	vector<vector<PartialGraphNode>> allPartialGraph_;
	vector<int> startNode_;
	vector<vector<int>> startNodes_;
	vector<vector<PartialGraphNode>> noCyclePaths_;
	vector<vector<PartialGraphNode>> cyclePaths_;
	vector<vector<PartialGraphNode>> mergePaths_;
	vector<vector<PartialGraphNode>> singlePaths_;
	vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> pathsMapping_;

	vector<vector<string>> mapDelta_;

	void init();
	//获取影响node标记下使能变迁发射时间域的部分可达图
	void calculatePartialGraph(MarkingNode node);
public:
	static TBDP& getInstance();
	//计算所有危险标记的部分可达图
	void calculateAllPartialGraph();
	void dfs(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode target, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths);
	void dfs2(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode target, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths);

	void dfsCircle(vector<PartialGraphNode> partialGraph, PartialGraphNode start, PartialGraphNode current, vector<bool>& visited, vector<PartialGraphNode>& path, vector<vector<PartialGraphNode>>& paths);
	//计算单个部分可达图的路径
	void findSingleGraphPath(vector<PartialGraphNode> partialGraph, vector<int> startNode);
	void mergePath();

	void calculateSignalPathSRG(vector<vector<PartialGraphNode>> singlePaths);

	void calculateCirclePathSRG(vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> pathsMapping);
	vector<vector<string>> getMapDelta_();
	void calculateAllSRG();

	vector<vector<PartialGraphNode>> getAllPartialGraphs();
	vector<vector<int>> getStartNodes();
	vector<vector<PartialGraphNode>> getNoCyclePaths();
	vector<vector<PartialGraphNode>> getCyclePaths();
	vector<vector<PartialGraphNode>> getMergePaths();
	vector<vector<PartialGraphNode>> getSinglePaths();
	vector<pair<vector<PartialGraphNode>, vector<PartialGraphNode>>> getPathsMapping();
};

