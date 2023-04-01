#ifndef DIST_P
#define DIST_P

#include <map>
#include "Agent.h"

using namespace std;

class Dist_Proportionally{

private:

public:
int calc_tot_pop(const map<int,int>& map);
void distVaccine(map<int,vector<Agent>>&agentvector, map<int,vector<int>>& config_list,map<int,int>& population, int available_vaccine);


	Dist_Proportionally() = default;
	~Dist_Proportionally() = default;


};



#endif
