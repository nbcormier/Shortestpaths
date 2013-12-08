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
#include <map>

using namespace std;

string source;
bool secondPass = false;
int nodes;
int edges;

//main routine
int main(int numberOfArguments, char* argumentValues[]) {
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
    
	//close input file
    newFile.close();
    return 0;
}
