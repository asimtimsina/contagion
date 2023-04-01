#ifndef SIM_H
#define SIM_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <map>

#include "Agent.h"
#include "closenesscentrality.h"
#include "degreecentrality.h"
#include "distributerandomly.h"
#include "distributeequally.h"
#include "distributeproportionally.h"
using namespace std;

class Simulation{

private:

public:

void path();
int infectedarea ;
int infected_period ;
int contact_rate ;
int no_vaccines;
map<int,int> population;
void readfile();
void readpopulation(std::string popfilename);
void readregion(string regionfilename);
void init_simulation();
void printfinal();


	Simulation() = default;
	~Simulation() = default;

vector<string> splitstr(string str, char delimiter);
vector<vector<int>> config_matrix;
map<int, vector<int> > config_list;
void printlist();
void coverttolist();
int recover(vector<Agent>& agentvector);
int infect_neighbors(vector<int>& temp);
vector<int> tot_ind_infections;
vector<pair<int, pair<int,int>>> peak ; 
int is_area_infected(int neighbor);

map<int, vector<Agent>> agentvector;
degreeCentrality d_centrality;
DistrubuteRandomly distribute_randomly;
ClosenessCentrality c_centrality;
DistributeEqually distribute_equally;
Dist_Proportionally dist_prop;
map<int, vector<int>> adjList;
void simulate();
int current_day;
void printagentsdata();
int	peakdate_F;
int	peakdate_L;
int	peak_number;


};

#endif

