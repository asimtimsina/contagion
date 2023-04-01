
#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Simulation:: path(){
  readfile();

//*
  cout << endl <<"CLOSENESS DISTRIBUTION"<< endl;
  init_simulation();
	c_centrality.Vaccinedistribution(agentvector, config_list, population, no_vaccines);
	simulate();
//*/
///*
  cout << endl << "DEGREE DISTRIBUTION" << endl;
  init_simulation();
  d_centrality.Vaccinedistribution(agentvector,population,  config_list,  no_vaccines);
  simulate();
//*/
///*
  init_simulation();
	 cout << endl <<"RANDOM DISTRIBUTION"<< endl;
	distribute_randomly.distributeVaccine(agentvector, config_list, population, no_vaccines);
	simulate();
  //*/
  //
  init_simulation();
	 cout << endl <<"EQUAL DISTRIBUTION"<< endl;
	distribute_equally.distributeVaccine(agentvector, config_list, population, no_vaccines);
	simulate();

   init_simulation();
	 cout << endl <<"WEIGHTED DISTRIBUTION"<< endl;
	dist_prop.distVaccine(agentvector, config_list, population, no_vaccines);
	simulate();
  

  printfinal();
}

///////////////////////////
void Simulation::printfinal(){
  cout << "Using the closeness centrality distribution method, the peak number of infected was "<< peak[0].first<<" on day "<< peak[0].second.first<<". The outbreak ended on day "<< peak[0].second.second<<" and the total number of infected individuals was " <<tot_ind_infections[0]<<"." << endl << endl;

   cout << "Using the degree centrality distribution method, the peak number of infected was "<< peak[1].first<<" on day "<< peak[1].second.first<<". The outbreak ended on day "<< peak[1].second.second<<" and the total number of infected individuals was " <<tot_ind_infections[1]<<"."  << endl << endl;

    cout << "Using the random distribution method, the peak number of infected was "<< peak[2].first<<" on day "<< peak[2].second.first<<". The outbreak ended on day "<< peak[2].second.second<<" and the total number of infected individuals was " <<tot_ind_infections[2]<<"."  << endl<< endl;

    cout << "Using the equal distribution method, the peak number of infected was "<< peak[3].first<<" on day "<< peak[3].second.first<<". The outbreak ended on day "<< peak[3].second.second<<" and the total number of infected individuals was " <<tot_ind_infections[3]<<"."  << endl<< endl;

     cout << "Using the weighted distribution method, the peak number of infected was "<< peak[4].first<<" on day "<< peak[4].second.first<<". The outbreak ended on day "<< peak[4].second.second<<" and the total number of infected individuals was " <<tot_ind_infections[4]<<"."  << endl<< endl;
	
}


///////////////////////////////////////
void Simulation::init_simulation(){
	for (auto& pop : population){
		agentvector[pop.first] = vector<Agent>(pop.second);
	}
	
}
///////////////////////////

void Simulation::simulate(){
  current_day = 0;
	cout << "DAY: " << current_day << endl;

	printagentsdata();
	peakdate_F = -1;
	peakdate_L = -1;
	peak_number = -1;
	int tot_infectant = 0;
  int tempa =  Agent::change_infect(agentvector[infectedarea], 1, current_day);
	tot_infectant +=tempa;
	int isChanged = 1;
	while (isChanged){
		int new_inf_cnt = 0;
		int recoverd = 0;
		vector<int> infectedNeighbors;
		int todays_total_infected = 0;
		for (auto& region : agentvector) {

			int newInf = 0;

			int infected = Agent::count_thisState(region.second, Infectious);
			todays_total_infected += infected;
			if (infected > population[region.first] / 2){
				infectedNeighbors.push_back(region.first);
			} 

			newInf = infected * contact_rate;
			int tmp = Agent::change_infect(region.second, newInf, current_day + 1);
			tot_infectant += tmp; 
			new_inf_cnt = new_inf_cnt ? 1 : tmp;
	
			tmp = recover(region.second);
			recoverd = recoverd ? 1 : tmp;
	
		} 
		if (todays_total_infected > peak_number){
			peak_number = todays_total_infected;
			peakdate_F = current_day;
		} 

	
		tot_infectant += infect_neighbors(infectedNeighbors);

		if (new_inf_cnt == 0 && recoverd == 0){
			peakdate_L = current_day;

			break;
		} // if
		current_day++;

		cout << "DAY: " << current_day << endl;

		printagentsdata();
	}  //while
	tot_ind_infections.push_back(tot_infectant);
	peak.push_back({peak_number, {peakdate_F, peakdate_L}});
} // func

/////////////////////////////////////////////////

void Simulation::printagentsdata(){
	for (auto& temp : agentvector){
		cout << temp.first << " POP: " << setw(7) << population[temp.first] << setw(10);
		cout << "S: " << setw(5) << Agent::count_thisState(temp.second, Susceptible) << setw(10);
		cout << "I: " << setw(5) << Agent::count_thisState(temp.second, Infectious) << setw(10);
		cout << "R: " << setw(5) << Agent::count_thisState(temp.second, Recovered) << setw(10);
		cout << "V: " << setw(5) << Agent::count_thisState(temp.second, Vaccinated) << endl;
	} // for
  cout << endl;
} // func

////////////////////////////////////////////////
int Simulation::recover(vector<Agent>& agentvector){
	int count = 0;
	for (int i =0 ; i < agentvector.size(); i++){
		if ((agentvector[i].state == Infectious) && (current_day + 1 == infected_period + agentvector[i].curr_day))	{
				agentvector[i].setState(Recovered,0);
				count++;
		} // if
	} // for
	return count;
} // func

/////////////////////////////////////////////////

int Simulation::infect_neighbors(vector<int>& temp){
int count = 0;
	for (int tem : temp){
		for (auto& neighbor : config_list[tem]){
			// infect the non-infected area only
			if (is_area_infected(neighbor) == 0){
				count+= Agent::change_infect(agentvector[neighbor], 1, current_day + 1);
      } // if
		} // for 
	} // for 
	return count;
} // func

////////////////////////////////////////////////////

int Simulation::is_area_infected(int neighbor){
	return Agent::count_thisState(agentvector[neighbor], Infectious) > 0;
} /// func

////////////////////////////////////////////////

void Simulation::readfile(){
  string filename;
  cout << "Please enter the name of the configuration file: ";
  cin >> filename;
  //filename = "config1.txt";

  ifstream infile(filename);
if(infile.fail()){
  cout << "Unable to open config file !!" <<endl;
  exit(1);
}
  string readline;

  getline(infile,readline,':'); // first line char befrore :
 getline(infile,readline);// first line char after :
 string popfilename = readline;

   getline(infile,readline,':'); //second line char befrore :
getline(infile,readline);
 string regionfilename = readline;

   getline(infile,readline); // reads empty line

 getline(infile,readline,':'); //read infected area line char befrore :
getline(infile,readline);//read infected area line char after :
 infectedarea = stoi(readline);

 getline(infile,readline,':'); //read infectious period line char befrore :
getline(infile,readline);//read infectious period line char after :
 infected_period = stoi(readline);

 getline(infile,readline,':'); //read contact rate line char befrore :
getline(infile,readline);//read contact rate line char after :
 contact_rate = stoi(readline);

 getline(infile,readline,':'); //read noof vaccines line char befrore :
getline(infile,readline);//read noof vaccines line char after :
 no_vaccines = stoi(readline);

/*
// testing :: Remove before submit
cout << popfilename << endl;
cout << regionfilename << endl;
cout << infectedarea << endl;
cout << infected_period << endl;
cout << contact_rate << endl;
cout << no_vaccines << endl;
*/


readpopulation(popfilename);
readregion(regionfilename);
infile.close();

}





////////////////////////////////////////

void Simulation::readpopulation(string popfilename){
 
ifstream infile(popfilename);

if(infile.fail()){ // if unable to open file
  cout << "Unable to open population file !!" <<endl;
  exit(1);
}
	string readline; 
  string pop;
	while ( getline(infile,readline))	{ // reading from the file
  vector <string> parts = splitstr(readline, ':');
  population[stoi(parts[0])] = stoi(parts[1]);
	}

  // printing the regional population
	cout << "Regional Population" << endl;
	for (auto& popn : population)
			cout << popn.first << " " << popn.second << endl;
	
	cout << endl;
}
////////////////////////////////

void Simulation::readregion(string regionfilename){

ifstream infile(regionfilename);

if(infile.fail()){ // if unable to open file
  cout << "Unable to open region file !!" <<endl;
  exit(1);
}
string readline;
getline(infile,readline); // skip the first line because the region layout stores the region as an adjacency matrix with a header on the top row 

while(getline(infile,readline)){

  vector <string> parts = splitstr(readline, ',');
  vector <int> tempstore ;
  for(int i =1; i <parts.size(); i++){

   
      tempstore.push_back(stoi(parts[i]));
  }
 
  config_matrix.push_back(tempstore);
  tempstore.clear();
}

coverttolist();
printlist();
}

////////////////////////////////

void Simulation::coverttolist(){
  for(int i =0; i <config_matrix.size(); i++){
    for(int j=0; j < config_matrix[i].size(); j++){
      if(config_matrix[i][j]==1){
        config_list[i+1].push_back(j+1);
      }
    }
  }
}
//////////////////////////////////
void Simulation::printlist(){
  cout <<"Adjacency List" << endl;
  for(auto& part :config_list ){
    cout << part.first;
    cout << " : " ;
    for (int i =0 ; i < part.second.size(); i++){
      cout << part.second[i] <<" ";
    }
    cout << endl;
  }
}

////////////////////////////////


vector<string> Simulation::splitstr(string str, char delimiter){
	string temp;
	vector<string> splits;
	for (char i : str)	{
		if (i == delimiter)		{
			splits.push_back(temp), temp.clear();
			continue;
		}
		temp += i;
	}
	splits.push_back(temp);
	return splits;
}

/////////////////////////


