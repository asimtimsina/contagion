#include "distributeproportionally.h"
#include "Agent.h"

#include <algorithm>

#include "distributeequally.h"



void Dist_Proportionally::distVaccine(map<int,vector<Agent>>&agentvector, map<int,vector<int>>& config_list,map<int,int>& population, int available_vaccine){

  int total = available_vaccine;
	map<int, int> temp_population = population;
	int agents = calc_tot_pop(population);
	
	for (auto & temp : agentvector){
		int now_av_vac = temp.second.size() * 1.0 / agents * total;
		// checking area
    // now_av_vac = max(now_av_vac , (int)temp.second.size());
		now_av_vac = min(now_av_vac , (int)temp.second.size());
		available_vaccine -= now_av_vac; // deducitng the vaccine count



		temp_population[temp.first] -= now_av_vac; // deducitng the no of agents
	  if(temp_population[temp.first] == 0){ // check and remove the vaccinated area
			temp_population.erase(temp.first);
		} // if
		Agent::operatevaccination(temp.second, now_av_vac); // operatevaccination
	} // for

	auto seg = temp_population.begin();

	while (available_vaccine && DistributeEqually::check_existance(temp_population)){
		if (seg->second)	{
			seg->second--;
			Agent::operatevaccination(agentvector[seg->first], 1); // operatevaccination
			available_vaccine--; // decrease the no of available_vaccine
		} // if
		seg++;
	
		if (seg == temp_population.end()){
			seg = temp_population.begin();
    } // if
	} // while 
	
} // func


int Dist_Proportionally::calc_tot_pop(const map<int, int>& population){
	int pop = 0;
	for (auto& temp : population)
	{
		pop += temp.second; // add population
	}
	return pop;
} // func
