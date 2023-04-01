#include "distributerandomly.h"

void DistrubuteRandomly::distributeVaccine(map<int, vector<Agent>>& agentvector, map<int, vector<int>>& config_list, map<int, int>& population,int available_vaccine){
	
  for (auto& temp : config_list){
    
		if (available_vaccine == 0){
			break;
    } // if
		int  temp_num = min(available_vaccine, population[temp.first]);

		Agent::operatevaccination(agentvector[temp.first], temp_num);
//TODO:: decrease the vaccine
    		available_vaccine -= temp_num; // decrease the available_vaccine
	} // for
} // func

