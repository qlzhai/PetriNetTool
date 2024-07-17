#pragma once

#include <iostream>
#include <vector>

using namespace std;

class PetriNet{
public:
    int nums_place;
    int nums_transition;

    vector<vector<int>> pre_incidence;
    vector<vector<int>> post_incidence;

    static PetriNet& getInstance();
};
