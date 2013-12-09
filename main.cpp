// main.cpp
// Dijkstra's algorithm for shortest paths
// Written by Nicklaus B. Cormier, December 2013

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <map>

using namespace std;

//let some large integer value represent infinity
#define INFINITY 99999999

struct CompareDistance {
    //create a way for the priority_queue to compare distances
    bool operator() (const pair<string, int> &node1, const pair<string, int> &node2) {
        return node1.second > node2.second;
    }
};

//=====================================================================
//======================== FUNCTION PROTOTYPES ========================
//=====================================================================

//* * * * * * * * * * * * * * 
//* SUB-ROUTINES
//* * * * * * * * * * * * * * 
void PrintResultsToFile(map <string, int> &Dist, string source);
//* * * * * * * * * * * * * * 
//* SETTERS
//* * * * * * * * * * * * * * 
void UpdateGraph(map <string, map <string, int> > &G, string u, string v, int w);
void UpdateDist(map <string, int> &Dist, string node, int d);
void UpdateFin(map <string, bool> &Fin, string node, bool status);
//* * * * * * * * * * * * * * 
//* GETTERS
//* * * * * * * * * * * * * * 
int GetWeight(map <string, map <string, int> > &G, string u, string v);
int GetDist(map <string, int> &Dist, string node);
int GetFin(map <string, bool> &Fin, string node);

//=====================================================================
//======================== MAIN ROUTINE ===============================
//=====================================================================

int main(int numberOfArguments, char* argumentValues[]) {
    map <string, map <string, int> > Graph; // input graph representation (adj list)
    map <string, int> Dist; // nodes: final distances
    map <string, bool> Fin; // nodes: finish status
    string source = argumentValues[2]; // pull 2nd command line argument
    int kDist = atoi(argumentValues[3]); // pull 3rd command line argument
    //a complicated priority queue
    priority_queue< pair<string, int>, vector< pair<string, int> > , CompareDistance > Q;
    int allowedNumArgs = 4; // only executable + 3 arguments may be passed
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
    
    //keep track of which line we're on
    int lineCount = 0;
    //track graph status
    bool DIRECTED = true;
    bool UNDIRECTED = false;
    //parse input file
    string line, node1, node2;
    int weight;
    while(newFile.good()) {
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
	    UpdateGraph(Graph, node1, node2, weight);
	    if(UNDIRECTED)
		UpdateGraph(Graph, node2, node1, weight);
	    UpdateDist(Dist, node1, INFINITY);
	    UpdateDist(Dist, node2, INFINITY);
	    UpdateFin(Fin, node1, false);
	    UpdateFin(Fin, node2, false);
	    if(newFile.eof())
		break;
	} else {
	      string ignore;
	      getline(newFile, ignore);
	}
    }
    UpdateDist(Dist, source, 0);
    Q.push(pair<string, int>(source, 0));
    
    //run Dijkstra
    while(!Q.empty()){
	string minNode = Q.top().first;
	Q.pop();
	if(GetFin(Fin, minNode) == true)
	  continue;
	map <string, map <string, int> >::const_iterator itr;
	itr = Graph.find(minNode);
	if(itr == Graph.end()) {
	    cout << "Error: Invalid source node. Terminating program." << endl;
	} else {
	    map <string, int> Adj = itr->second;
	    map <string, int>::const_iterator itr1;
	    for(itr1 = Adj.begin(); itr1!=Adj.end(); ++itr1){
		string v = itr1->first;
		int w = itr1->second;
		int newDist = GetDist(Dist, minNode) + w;
		int currentDist = GetDist(Dist, v);
		if(GetFin(Fin, v) == false && ( newDist < currentDist ) ){
		  UpdateDist(Dist, v, newDist);
		  Q.push(pair<string, int>(v, newDist));
		}
	    }
	    UpdateFin(Fin, minNode, true);
	}
    }
    
    PrintResultsToFile(Dist, source);
    
    //close input file
    newFile.close();
    return 0;
}

//=====================================================================
//======================== FUNCTION DEFINITIONS =======================
//=====================================================================

void PrintResultsToFile(map <string, int> &Dist, string source){
    ofstream OUT;
    OUT.open("out.txt");
    if (OUT.is_open()) {
	OUT << "Dijkstra\n";
	OUT << "Source: " << source << endl;
	map <string, int>::const_iterator itr;
	for(itr = Dist.begin(); itr != Dist.end(); ++itr)
	    OUT << "NODE " << itr->first << ": " << itr->second << endl;
	OUT << "End Dijkstra\n";
    } else {
	  cout << "Error: could not write to out.txt.\n";
    }
    OUT.close();
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

void UpdateDist(map <string, int> &Dist, string node, int d){
    map <string, int>::const_iterator itr;
    itr = Dist.find(node);
    if(itr == Dist.end()) {
	Dist.insert(pair<string, int> (node, d));
    } else {
	  Dist[node] = d;
    }
}

void UpdateFin(map <string, bool> &Fin, string node, bool status){
	map <string, bool>::const_iterator itr;
	itr = Fin.find(node);
	if(itr == Fin.end()) {
	    Fin.insert(pair<string, bool> (node, status));
	} else {
	      Fin[node] = status;
	}
}

int GetDist(map <string, int> &Dist, string node){
    map <string, int>::const_iterator itr;
    itr = Dist.find(node);
    if(itr != Dist.end())
	return itr->second;
    else
	return 0;
}

int GetFin(map <string, bool> &Fin, string node){
    map <string, bool>::const_iterator itr;
    itr = Fin.find(node);
    if(itr != Fin.end())
	return itr->second;
    else
	return 0;
}

int GetWeight(map <string, map <string, int> > &G, string u, string v){
    map <string, map <string, int> >::const_iterator itr;
    itr = G.find(u);
    if(itr != G.end()) {
	map <string, int> temp = itr->second;
	map <string, int>::const_iterator itr1;
	itr1 = temp.find(v);
	if(itr1 != temp.end()){
	    return itr1->second;
	}
    }
    return 0;
}

//=====================================================================
//======================== END MAIN.CPP ===============================
//=====================================================================