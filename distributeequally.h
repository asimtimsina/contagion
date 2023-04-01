#ifndef EQ_H
#define EQ_H
#include <map>
#include <vector>
#include "Agent.h"
using namespace std;
class DistributeEqually
{
public:
	void distributeVaccine(map<int, vector<Agent>>& agentvector, map<int, vector<int>>& config_list, map<int, int>& population,int available_vaccine);

	static  bool check_existance(map<int, int>& population);

	DistributeEqually() = default;
	~DistributeEqually() = default;
};
#endif
