#include "MarkingNode.h"

MarkingNode::MarkingNode(int node_name, Eigen::VectorXi marking) : 
                node_name_(node_name), marking_(std::move(marking)) {}