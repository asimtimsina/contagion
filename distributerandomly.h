#ifndef RAND_H
#define RAND_H
#include "Agent.h"
#include <map>
#include <algorithm>
//#include <utility>
using namespace std;
class DistrubuteRandomly{
public:

	void distributeVaccine(map<int, vector<Agent>>& agentvector, map<int, vector<int>>& config_list, map<int, int>& population,		int available_vaccine);

	DistrubuteRandomly()= default;
	~DistrubuteRandomly() = default;
	
};

#endif
