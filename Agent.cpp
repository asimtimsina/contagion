
#include "Agent.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

////////////////////////////////////////////////

void Agent::setState(HealthState st, int temp){ // parameterized constructor
  state = st;
  curr_day = temp;
}

////////////////////////////////////////////
 
 HealthState Agent::getH_State(){
   return state;
 }

/////////////////////////////////////////

void Agent::operatevaccination(vector<Agent> &agentvector, int change_no){ // operatevaccination in  the state
 
if (change_no)
for(int i =0; i < agentvector.size() && change_no != 0; i++){
    if (agentvector[i].state != Vaccinated){
      
      agentvector[i].setState(Vaccinated);
      change_no--;
    } // if
} // for
} // void func

//////////////////////////////////////////

void Agent::updateH_state(int temp){ // this function changes the current state if infectious to recovery after incubation date
  if ((state == Infectious) && (temp - curr_day >= inc_time)){
		setState(Recovered);
  }
}

/////////////////////////////////////////

Agent::Agent(){ // default constructor
	state = Susceptible;
}

///////////////////////////////////////

int Agent::count_thisState(vector<Agent>& agentvector, HealthState temp){ // this function counts the no of areas with temp gealth state
    int count =0;
    for (int i =0 ; i < agentvector.size(); i++){
        if (agentvector[i].state == temp)
            count++;
    }
    return count;
}

///////////////////////////////////////////

int Agent::change_infect(vector<Agent>& agentvector, int temp , int day ){ //this function changes the Susceptible population to infectious
    int count = 0;
    for (int i = 0; i < agentvector.size() && temp!=0 ; i++){
	    if (agentvector[i].state == Susceptible){
            agentvector[i].setState(Infectious, day);
            temp--;
            count++;
	    }
    }
    return count;
}

//////////////////////////////////////

