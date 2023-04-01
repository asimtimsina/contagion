#ifndef CLO_CEN_H
#define CLO_CEN_H

#include <iostream>
#include <vector>
#include <map>
#include "Agent.h"


class ClosenessCentrality{

  private:

  public:
    void Vaccinedistribution(map<int, vector<Agent>> &agentvector, map<int, vector<int>>&  config_list,map<int, int>& population,int  no_vaccines);

    float getcloseness();
    void findcloseness(map<int, vector<int>>& adjList);
    int size;
    vector<pair<double, int>> closenodes;

    ClosenessCentrality() = default;
    ~ClosenessCentrality() = default;
    
};







#endif
