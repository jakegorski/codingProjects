// Jake Gorski
// CS 302 - 1002
// Assignment 9
// This assignment practices the use of adjacency lists
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "myStack.h"
#include "adjacencyList.h"
using namespace std;


bool getPaths(string current, string finalDestination, unordered_map<string, vertex<string>> adjList, 
                unordered_map<string, bool>& nodesInPath, myStack<string>& recStack, int& numPaths);

bool reverse(string finalDestination, string source, unordered_map<string, vertex<string>> adjList, 
                unordered_map<string, bool>& nodesInPath, myStack<string>& recStack);

int main(){

    // Variables
    unordered_map<string, vertex<string>> adjList;
    unordered_map<string, bool> nodesInPath;
    myStack<string> recStack;
    string first;
    string last;
    string source;
    string finalDestination;
    int numPaths;


    // Prompt for file
    ifstream fin;
	string fileName;
	cout << "Enter Streets File: ";
	cin >> fileName;
	fin.open(fileName.c_str());
	while(fin.fail()){
		fin.clear();
		cout << "Enter Streets File: ";
		cin >> fileName;
		fin.open(fileName.c_str());
	}

    //Fin Source and Dest
    fin >> source; 
    fin >> finalDestination;
    nodesInPath[source] = false;
    nodesInPath[finalDestination] = false;

    while(!fin.eof()){

        fin >> first;
        if(first.empty()){
            continue;
        }

        fin >> last;
        if(last.empty()){
            cout << "Error" << endl;
            break;
        }
    // Populate Adjlist
        adjList[first].addEdge(last);
    }

    fin.close();
    getPaths(source, finalDestination, adjList, nodesInPath, recStack, numPaths);
   
   return 0;
}

bool getPaths(string source, string finalDestination, unordered_map<string, vertex<string>> adjList, 
unordered_map<string, bool>& nodesInPath, myStack<string>& recStack, int& numPaths){

    myStack<string> s;
    unordered_map<string, bool> visited;
    unordered_map<string, string> predecessor;
    vertex<string> w;
    vertex<string> adj = adjList[source];


    // Push true visited indices onto stack
    for(vertex<string>::edgeIterator g = adj.begin(); g != adj.end(); g++){
        visited = nodesInPath;
        visited[source] = true;
        s.push(*g);
        predecessor.clear();
        predecessor[*g] = "0";

    // Update stack
        while(!s.isEmpty()){
            string u = s.top();
            s.pop();
            if(!visited[u]){
                visited[u] = true;
                w = adjList[u];

                for(vertex<string>::edgeIterator e = w.begin(); e != w.end(); e++){
                    if(!visited[*e]){
                        predecessor[*e] = u;
                    }
                    s.push(*e);
                }
            }
        }

        if(!predecessor[finalDestination].empty() && reverse(source, finalDestination, adjList, nodesInPath, recStack)){
            numPaths++;
            cout << "Path: " << numPaths << " ";
            string cn = finalDestination;
            while(cn != "0"){
                s.push(cn);
                cn = predecessor[cn];
            }   
            s.push(source);

            while(!s.isEmpty()){
                cout << s.top();
                s.pop();
                if(!s.isEmpty()){
                    cout << " <=> ";
                }
            }
            cout << endl;
        }
    }
    if(numPaths == 0){
        return false;
    }
    return true;
}


// Same function but switches source and finalDestination
bool reverse(string finalDestination, string source, unordered_map<string, vertex<string>> adjList, 
unordered_map<string, bool>& nodesInPath, myStack<string>& recStack){

    myStack<string> s;
    unordered_map<string, bool> visited;
    unordered_map<string, string> predecessor;
    vertex<string> w;
    vertex<string> adj = adjList[source];
    int paths = 0;

    for(vertex<string>::edgeIterator g = adj.begin(); g != adj.end(); g++){
        visited = nodesInPath;
        visited[source] = true;
        s.push(*g);
        predecessor.clear();
        predecessor[*g] = "0";

    while(!s.isEmpty()){
        string u = s.top();
        s.pop();
        if(!visited[u]){
            visited[u] = true;
            w = adjList[u];

            for(vertex<string>::edgeIterator e = w.begin(); e != w.end(); e++){
                
                if(!visited[*e]){
                    predecessor[*e] = u;
                }
                s.push(*e);
            }
        }
    }
        if(!predecessor[finalDestination].empty()){
            paths++;
            string cn = finalDestination;
            while(cn != "0"){
                s.push(cn);
                cn = predecessor[cn];
            }   
            s.push(source);
            while(!s.isEmpty()){
                  s.pop();
            }

        }
    }
    if(paths == 0){
        return false;
    }
    return true;
}



