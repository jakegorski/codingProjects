// Jake Gorski - 302-1002
// Assignment 6
// This program will practice the use of file
// input and using a hash map.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


int main(){

// Prompt for a names file and store all the students names into a vector of string objects
    ifstream fin;
	string fileName;
	cout << "Enter Names File: ";
	cin >> fileName;
	fin.open(fileName.c_str());
	while(fin.fail()){
		fin.clear();
		cout << "Enter Students File: ";
		cin >> fileName;
		fin.open(fileName.c_str());
	}
// Creates a vector of strings to store names into
    vector<string> students;
    string s;
    while(fin >> s){
        students.push_back(s);
    }

    fin.close();
    fin.clear();

// Prompt for assignments file
    cout << "Enter Assignments File: ";
	cin >> fileName;
	fin.open(fileName.c_str());
	while(fin.fail()){
		fin.clear();
		cout << "Enter Assignments File: ";
		cin >> fileName;
		fin.open(fileName.c_str());
	}

// Creates a vector of strings to store assignments into
    vector<string> assignments;
    string a;
    while(fin >> a){
        assignments.push_back(a);
    }

// Vector to store names with no duplicates
    vector<string> condensed;
// Hash Map that stores strings and checks bool
    unordered_map<string, bool> dupeCheck;
    for(int i = 0; i < assignments.size(); i++){  
        if(!dupeCheck[assignments[i]]){             //Duplicate["Ora_A4"]
            condensed.push_back(assignments[i]);  //Pushes Ora_A4 into  new vector 
            dupeCheck[assignments[i]] = true;    //Changes Ora_A4 to true so will only be inserted once
        }
    }
// Pop off number of each assignment # in order to count
    for(int i = 0; i < condensed.size(); i++)
    {
        if(!condensed[i].empty()){ 
            condensed[i].pop_back(); 
            condensed[i].pop_back();
            condensed[i].pop_back();
        }
    }
// Condensed now holds names with no assignments attatched     
// New unordered map to load no duplicated list into
    unordered_map<string, int> countAssigments;
	for(int i = 0; i < condensed.size(); i++){
        countAssigments[condensed[i]]++;
	}

//Output final result abs - 9 for difference in missing assignments with subumitted
    cout << endl;
    cout << "Students" << "\t" "\t" << "Missing Assignments" << endl;
    for(int i = 0; i < students.size(); i++){
        cout << students[i] << "\t" "\t" "\t" << abs(countAssigments[students[i]] - 9) << endl;
    }
     
    return 0;
}
