/*
Jake Gorski
CS 302 - 1002
Assignment 2
This program uses a mulitude of boolean functions to solve
a given soduku puzzle. Including a main recursive function
used to solve the puzzles.
*/
#include<iostream>
#include<fstream>
using namespace std;
int board[9][9];

//Checks Rows and Collums for repeating #
bool rowColl(int row, int col, int number){ 
   for(int row = 0; row < 9; row++){
      if(board[row][col] == number){
      return true;
      }
   }
   for(int col = 0; col < 9; col++){
      if(board[row][col] == number){
      return true;
      }
   }
   return false;
}

//Find's '0's
bool findZero(int &row, int &col){ 
   for(row = 0; row < 9; row++){
      for(col = 0; col < 9; col++){
         if(board[row][col] == 0){ 
            return true;
         }
      }
   }
   return false;
}

//Check whether # is present in 3x3
bool inThree(int startCol, int startRow, int number){
   for(int row = 0; row < 3; row++){
      for(int col = 0; col < 3; col++){
         if(board[row + startCol][col + startRow] == number){
            return true;
         }
      }
   }
   return false;
}

//Checks 3x3 space on board
bool valid(int row, int col, int number){
   return !rowColl(row, col, number) &&
   !inThree(row - row % 3 ,col - col % 3, number);
}

/*
Hydra Soduku (Name inspired from hydra password crack!)
Main function for recursivly solving the board,
implements previous boolean functions to determine if
place and numberber is valid.
Uses recurrsion to check other boxes.
*/
bool hydraSoduku(){
   int row; 
   int col;
   if(!findZero(row, col)){ //Base Case all spots filled, return true
      return true;
   }
   for(int number = 1; number <= 9; number++){ //Loops through each number 1-9
      if(valid(row, col, number)){             //Checks validity and places number
         board[row][col] = number;
         if(hydraSoduku()){ 
         return true;
         }
         board[row][col] = 0;
      }
   }
   return false;
}

int main() {

//Reads input file and reprompts if file not opened
ifstream fin;
string fileName;
cout << "Enter the file name: ";
cin >> fileName;
fin.open(fileName.c_str());
while(fin.fail()){
    fin.clear();
    cout << "Incorrect filename, please enter again." << endl;
    cout << "Enter the file name: ";
    cin >> fileName;
    fin.open(fileName.c_str());
}

//Intial board output
cout << endl;
cout << "Intial board read in: " << endl;
cout << endl;
//9x9 Array output 
for(int row = 0; row < 9; row++){
   for(int col = 0; col < 9; col++){
      fin >> board[row][col];

      if(col == 3 || col == 6)
      cout << " ";
      cout << board[row][col] << " ";
   }
      if(row == 2 || row == 5){
      cout << endl;
      for(int i = 0; i < 9; i++)
      cout << " ";
   }
      cout << endl;
}
cout << endl;


//Solved board output
if(hydraSoduku() == true){
cout << "Puzzle Sovled!" << endl;
cout << endl;
for(int row = 0; row < 9; row++){
   for(int col = 0; col < 9; col++){
      if(col == 3 || col == 6)
      cout << " ";
      cout << board[row][col] << " ";
   }
      if(row == 2 || row == 5){
      cout << endl;
         for(int i = 0; i < 9; i++)
            cout << " ";
   }
      cout << endl;
   }
}
   cout << endl;
}
