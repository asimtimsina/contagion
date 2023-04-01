#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum HealthState { Susceptible,Infectious,Recovered, Vaccinated  };


class Agent{


public:
HealthState state;
int curr_day =0;
int inc_time;

	~Agent() = default;
Agent();
void setState(HealthState st, int temp = 0);
void updateH_state(int curr_day);
HealthState getH_State();



static int count_thisState(vector<Agent>& agentvector, HealthState temp);
static void operatevaccination(vector<Agent> &agentvector, int change_no);
static int change_infect(vector<Agent>& agentvector, int temp , int day );


 friend  bool operator==(const Agent& lhs, const Agent& rhs){
		return   lhs.state == rhs.state; // friend to compare 
	  }

};


#endif
