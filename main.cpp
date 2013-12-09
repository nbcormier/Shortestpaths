// main.cpp
// Dijkstra's algorithm for shortest paths
// Written by Nicklaus B. Cormier, December 2013

#include "dfs.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <queue>
#include <functional>
#include <map>

using namespace std;

void UpdateGraph(map <string, map <string, int> > &G, string u, string v, int w);
int GetWeight(map <string, map <string, int> > &G, string u, string v);

string source;
bool secondPass = false;
int nodes;
int edges;

//main routine
int main(int numberOfArguments, char* argumentValues[]) {
    map <string, map <string, int> > Graph;
	//only executable + 3 arguments may be passed
	int allowedNumArgs = 4;
	if(numberOfArguments != allowedNumArgs) {
		cout << "Program usage:\n";
		cout << argumentValues[0] << " <input file> <source node> <k weight>\n";
		return 1;
	}
	
	ifstream newFile;
    //attempt to open input file
    newFile.open(argumentValues[1]);
    //test to see if the file opened (i.e. does it exist?)
    if (!newFile.is_open()) {
		cout << "Error:\n";
		cout << "Input file \"" << argumentValues[1] << "\" does not exist.\n";
		//exit
		return 1;
    }
    
    map <string, vector <string> > graph;
    map <string, vector <string> > graphTrans;
    map <string, string> sets;
    vector <string> blackStack;
    
	//keep track of which line we're on
	int lineCount = 0;
	//track graph status
	bool DIRECTED = true;
	bool UNDIRECTED = false;
	//parse input file
	string line, node1, node2;
	int weight;
	while (newFile.good()) {
		newFile >> node1;
		if(node1[0] != '#') {
		    lineCount++;
			if(lineCount == 1){
			  if(node1 == "UD"){
				UNDIRECTED = true;
				DIRECTED = false;
			  }
			  continue;
			}
			newFile >> node2;
			newFile >> weight;
			cout << weight + weight << endl;
			UpdateGraph(Graph, node1, node2, weight);
			if(DIRECTED){
			  cout << "Directed graph:\n";
			  cout << "Node1: " << node1 << "\n";
			  cout << "Node2: " << node2 << "\n";
			  cout << "Weight: " << weight << "\n";
			} else {
			  cout << "Undirected graph:\n";
			  cout << "Node1: " << node1 << "\n";
			  cout << "Node2: " << node2 << "\n";
			  cout << "Weight: " << weight << "\n";
			}
			  
			if(newFile.eof())
				break;
		} else {
			string ignore;
			getline(newFile, ignore);
		}
    }
    
    int st = GetWeight(Graph, "y", "x");
    cout << "Weight from s to t: " << st << endl;
    
    std::priority_queue<int, std::vector<int>, std::greater<int> > mypq;

  mypq.push(30);
  mypq.push(100);
  mypq.push(25);
  mypq.push(40);

  std::cout << "Popping out elements...";
  while (!mypq.empty())
  {
     std::cout << ' ' << mypq.top();
     mypq.pop();
  }
  std::cout << '\n';
    
	//close input file
    newFile.close();
    return 0;
}

void UpdateGraph(map <string, map <string, int> > &G, string u, string v, int w){
  map <string, map <string, int> >::const_iterator itr;
  itr = G.find(u);
  if(itr == G.end()) {
	  map <string, int> temp;
	  temp.insert(pair<string, int> (v, w) );
	  G.insert(pair<string, map<string, int>  > (u, temp));
  } else {
	  map <string, int> temp = itr->second;
	  temp.insert(pair<string, int> (v, w) );
	  G[u] = temp;
  }
}

int GetWeight(map <string, map <string, int> > &G, string u, string v){
  map <string, map <string, int> >::const_iterator itr;
  itr = G.find(u);
  if(itr != G.end()) {
    cout << "found " << u << " in graph\n";
	map <string, int> temp = itr->second;
	map <string, int>::const_iterator itr1;
	itr1 = temp.find(v);
	if(itr1 != temp.end()){
	  return itr1->second;
	}
  }
  return 0;
}