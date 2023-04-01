#include "distributeequally.h"
#include "Agent.h"

int make_minmap(map<int, int> & population){
  int temp = -1;
	int maxval = INT32_MAX;

	for (auto & check : population)	{
		if (check.second < maxval){
			maxval = check.second, temp = check.first;
		} // if
	} // for
	return temp;
} // func

/////////////////////////////////

bool DistributeEqually::check_existance(map<int, int>& population){
	for (auto & temp : population){
		if (temp.second)
			return 1;
	} // for
	return 0;
} // func

//////////////////////////////

void DistributeEqually::distributeVaccine(map<int, vector<Agent>>& agentvector, map<int, vector<int>>& config_list,	map<int, int>& population, int available_vaccine){
	
  map<int, int> temp_population = population; // creating a dublicate population map
	auto temp = temp_population.begin();

	while (!temp_population.empty()){
		int index = make_minmap(temp_population);
		int now = temp_population[index] * temp_population.size();
		if(available_vaccine < now)
			break;
		available_vaccine -= now;
		now = temp_population[index];
		for (auto & temp_c : temp_population){
			Agent::operatevaccination(agentvector[temp_c.first], now);
			temp_c.second -= now;
		} // for
		temp_population.erase(index);
		
	} // while
	while (available_vaccine &&  check_existance(temp_population)){
		if(temp->second){
			temp->second--;
			Agent::operatevaccination(agentvector[temp->first], 1);
				available_vaccine--;
		} // if





		temp++;
		if (temp == temp_population.end()){
			temp = temp_population.begin();
    } // if
	} // while

} //func

