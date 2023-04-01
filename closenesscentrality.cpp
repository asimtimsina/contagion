#include <iostream>
#include "closenesscentrality.h"
#include "Agent.h"
#include <algorithm>
#include <queue>
using namespace std;




long long dis[10000];
void find_mindist(int temp, map<int, vector<int>>& config_list){
//long distance[10000];
for(int i =0;i < 10000;i++){
  dis[i] = INT32_MAX;
}

	dis[temp] = 0;
	queue<int> que;
	que.push(temp);
	while (que.size()){
		temp = que.front();
		que.pop();
		for (int tempa : config_list[temp]){
			if (dis[tempa] == INT32_MAX){
				dis[tempa] = dis[temp] + 1;
				que.push(tempa);
			} // if
		} // for
	} // while
} // func

////////////////////////////////////

void ClosenessCentrality::Vaccinedistribution(map<int, vector<Agent>> &agentvector, map<int, vector<int>>&  config_list,map<int, int>& population,int  no_vaccines){ // function to distribute vaccine using closenesscentrality
 
	size = config_list.size();
	findcloseness(config_list);
 
	for (auto & temp_node : closenodes){
  
		if(no_vaccines == 0){
			break;
    }
		int  min_num = min(no_vaccines, (int)agentvector[temp_node.second].size());
		no_vaccines -= min_num;
    
		Agent::operatevaccination(agentvector[temp_node.second], min_num);
	} // for
} // fuinc

/////////////////////////////////////////////////////

float ClosenessCentrality::getcloseness(){ //func to find closeness
	 long long temp = 0;
	for (int i = 0; i < 1000; i++){
		if (dis[i] != INT32_MAX)
			temp += dis[i];
	} // for
	return (static_cast<float>(temp)) / (size - 1);
} // func

////////////////////////////////////////////////////////

void ClosenessCentrality::findcloseness(map<int, vector<int>>& config_list){
	for (auto& temp_node : config_list){
		find_mindist(temp_node.first, config_list);  // finding distance between the current node and other
		closenodes.push_back({ getcloseness() ,temp_node.first });
	} // for
	sort(closenodes.begin(), closenodes.end());  // sorting using algorithm
	
} // func

///////////////////////////////////////////////////////////

