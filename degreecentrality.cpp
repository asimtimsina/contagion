#include "degreecentrality.h"
#include "Agent.h"
#include <iostream>
#include <algorithm>
using namespace std;


 /////////////////////////

void degreeCentrality::cal_DCdegree(map<int, vector<int>>& config_list){ 
  	for (auto & temp_node : config_list){
		DCdegree.push_back({ temp_node.second.size(), temp_node.first });
	}
	sort(DCdegree.begin(), DCdegree.end(), compare); // sorting using algorithm
}

////////////////////////////////////

bool degreeCentrality::compare(pair<int, int> &tempA, pair<int, int> &tempB){
	if(tempA.first != tempB.first)
		return  tempA.first > tempB.first; // if first degree is larger
	else
	return tempA.second < tempB.second; // if second degree is larger
}


//////////////////////////////