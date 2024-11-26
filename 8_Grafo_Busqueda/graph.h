/*
* Mateo Minghi
* A01711231
* Prof. Benjamin
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>

#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
		int lista_conexiones;
		int matriz_adj;
		
        int nodes;
    	vector<int> *adjList;
		int *adjMatrix;
        //vector<Type> *vect = new vector<Type>

public:
    Graph(int);
    Graph();
    void addEdgeAdjMatrix(int, int);
    void addEdgeAdjList(int, int);
    string DFS(int, int);
    string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int> >&);
    string BFS(int, int);
    string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int> >&);
    string print_visited(list<int>);
    string print_path(vector<vector<int> >&,int ,int);
    string printAdjList();
    string printAdjMat();
    bool contains(list<int>, int);
    void sortAdjList();
    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);
};

Graph::Graph() {
    lista_conexiones = matriz_adj = 0;
}

Graph::Graph(int n) {
    nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	lista_conexiones = matriz_adj = 0;
}


void Graph::loadGraphMat(string data, int node_tam, int edge_tam){
    int u, v, i = 0;
    adjMatrix = new int [node_tam * edge_tam];	
	nodes = node_tam;
	
    for (int i = 0; i < node_tam * edge_tam; i++)
		adjMatrix[i] = 0;	
	
	
	
	while (i < data.size()) {
		u = (int)data[i+1] - 48;			
		v = (int)data[i+3] - 48;		
		i = i + 6;
		addEdgeAdjMatrix(u,v);
	}
}

void Graph :: loadGraphList(string data, int node_tam){
	adjList = new vector<int>[node_tam];
	nodes = node_tam;

	int u, v, i = 0;
	
	while (i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
	}
	sortAdjList();
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	matriz_adj++;
}

void Graph :: addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	
	lista_conexiones++;
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int> > &paths){
	
	if (current == goal){
		return print_visited(visited);
	}
	
	else if (st.empty()){
		return " node not found";
	}
	
	else {
		
		current = st.top();
		
		st.pop();
		
		visited.push_back(current);
		
		for (int i = 0; i < adjList[current].size(); i++){

			if (!contains(visited, adjList[current][i])){
				st.push(adjList[current][i]);
				paths[adjList[current][i]][0] = current;
			}
		}
		return depthHelper(current, goal, st, visited, paths);
	}
}

string Graph :: DFS(int start, int goal){
	
	stack <int> st;
	list <int> visited;
	
	vector <vector<int> > paths(nodes, vector <int> (1, -1));
	st.push(start);
	
	string ans = depthHelper(start, goal, st, visited, paths);
	 
	ans = ans + print_path(paths, start, goal);
	
	return ans;
}


string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int> > &paths){
	if (current == goal){
		return print_visited(visited);
	}
	else if (qu.empty()){
		return " node not found";
	}
	else {
		current = qu.front();
		qu.pop();
		visited.push_back(current);
		for (int i = 0; i < adjList[current].size(); i++){
			if (!contains(visited, adjList[current][i])){
				qu.push(adjList[current][i]);
			
				if (paths[adjList[current][i]][0] == -1){
					paths[adjList[current][i]][0] = current;
				}
			}
		}
		
		return breadthHelper(current, goal, qu, visited, paths);
	}
}


string Graph :: BFS(int start, int goal){
	queue <int> qu;
	list <int> visited;
	vector <vector<int> > paths(nodes, vector <int> (1, -1));
	qu.push(start);
	string ans = breadthHelper(start, goal, qu, visited, paths);
	ans = ans + print_path(paths, start, goal);
	return ans;
}


string Graph::print_visited(list<int> q){
	
	stringstream aux;
	aux << "visited: ";
	
	while (!q.empty()){
		aux << q.front() << " ";
		q.pop_front();
  	}
	return aux.str();
}
 
string Graph::print_path(vector<vector <int> > &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    	node = path[node][0];
 	}
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
 	}
	return aux.str();
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}


bool Graph::contains(list<int> ls, int node){
	
	list<int>::iterator it;

	it = find(ls.begin(), ls.end(), node);
	if(it != ls.end())
		return true;
	else
		return false;
}

void Graph::sortAdjList(){ 
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(), adjList[i].end());
}


#endif 