#ifndef DC_H
#define DC_H

#include "Agent.h"
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class degreeCentrality{

  private:

  public:
  vector<pair<int, int>> DCdegree;
	int size;

  void Vaccinedistribution(map<int, vector<Agent>>& agentvector, map<int, int>& population,map<int, vector<int>>& config_list, int available_vaccine){ 
    //PROBLEM:: linker failed while compiling
    // TODO:: try to fix this function defining in .cpp file
    cal_DCdegree(config_list);
	for (auto& temp_node : DCdegree){
		if (available_vaccine == 0){
			break;
    } 
		int  temp = min(available_vaccine, (int)agentvector[temp_node.second].size());
		
		Agent::operatevaccination(agentvector[temp_node.second], temp);


    available_vaccine -= temp; // decreasing the no of available_vaccine
	}
 }

 ////////////////////////////////


  void cal_DCdegree(map<int, vector<int>>& config_list);
	static  bool compare(pair<int, int> &tempA, pair<int, int> &tempB); 
	

    degreeCentrality() = default;
    ~degreeCentrality() = default;

};












#endif