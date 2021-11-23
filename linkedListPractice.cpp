/*
Jake Gorski
2001406428
Assignment #12
   This program deals with linked lists. Given an input of values,
   the program will first output the inital lists. Then it will split them.
   The program then outputs the first and second halfs of the lists. 
*/
#include<iostream>
#include<cstddef>
using namespace std;

// Varible and struct declaration 
typedef int ItemType;
struct NodeType;
typedef NodeType *NodePtr;

// Nodetype Struct 
struct NodeType{
    ItemType component;
    NodePtr link;
};


// Class List
class List {
public:
   List();
   void Insert(ItemType item);
   void Delete(ItemType item);
   void ResetList();
   ItemType GetNextItem();
   int GetLength() const;
   bool IsEmpty() const;
   bool IsFull() const;
   bool IsThere(ItemType item) const;
   bool HasNext() const;

// First Linked List 
   List split_ver1(ItemType item){
    
      NodePtr currPtr = dataPtr;
      NodePtr prevPtr = NULL;
      while(currPtr != NULL && currPtr->component != item) {
         prevPtr = currPtr;
         currPtr = currPtr->link;
      }

// currPtr points to beginning of new list
// prevPtr points to last element of current list
// Set lastPtr = prevPtr and prevPtr->link = NULL

      if(prevPtr == NULL){
         dataPtr = NULL;
      }
      else{
         prevPtr->link = NULL;
      }
      lastPtr = prevPtr;
      List newList;

// Loop from currPtr to end of list
// Insert each item into new list 

   while(currPtr != NULL){
      newList.Insert(currPtr->component);
      // delete current element 
      NodePtr tempPtr = currPtr->link;
      delete currPtr;
      length--;
      currPtr = tempPtr;
   }
   
// Return new list 
   return newList;

   }

// Linked List 2
   List split_ver2(ItemType item){

      int counter = 0;
      NodePtr currPtr = dataPtr;
      NodePtr prevPtr = NULL;
      while(currPtr != NULL && currPtr->component != item) {
         prevPtr = currPtr;
         currPtr = currPtr->link;
         counter++;
      }
      List newList;
      newList.dataPtr = currPtr;
      newList.lastPtr = lastPtr;
      newList.length = length - counter;

      if(prevPtr == NULL){
         dataPtr = NULL;
      }
      else{
         prevPtr->link = NULL;
      }
      lastPtr = prevPtr;
      return newList;
   }
// PrintForward prints the current node 
   void PrintForward() const{
      NodePtr currPtr = dataPtr;
      while (currPtr != NULL) {     
         cout << currPtr->component << ","; 
         currPtr = currPtr->link;
      }
      cout << endl;
   }
// Private Data
private:
   NodeType *dataPtr;
   int length;
   NodeType *currentPos;
   NodeType *lastPtr;
};
// Constructor 
List::List(){
   dataPtr = NULL;
   currentPos = dataPtr;
   length = 0;
   lastPtr = NULL;
}
// Insert Funcion inserts into our linked list at a given node
void List::Insert(ItemType item){
   NodePtr currPtr, prevPtr, newNodePtr;
   newNodePtr = new NodeType;
   newNodePtr->link = NULL;
   newNodePtr->component = item;
   if (dataPtr == NULL){  // Empty list?
      dataPtr = newNodePtr;
      lastPtr = newNodePtr;
   }
   else{ //Find previous insertion point
      currPtr = dataPtr;
      prevPtr = NULL;
      while (currPtr != NULL && currPtr->component < item) {
         prevPtr = currPtr;
         currPtr = currPtr->link;
      }
      // Insert new node
      newNodePtr->link = currPtr;
      if (prevPtr == NULL)  // Insert as first?
         dataPtr = newNodePtr;
      else  prevPtr->link = newNodePtr;
      if (currPtr == NULL) // Insert as last?
         lastPtr = newNodePtr;
   }
   length++;
}
// Delete will delete the previous node in our linked list
void List::Delete(ItemType item){
   NodePtr prevPtr = NULL;
   NodePtr currPtr = dataPtr;
   while(currPtr != NULL && currPtr->component != item){
      prevPtr = currPtr;
      currPtr = currPtr->link;
   }
   if (currPtr != NULL){
      if (currPtr == dataPtr) dataPtr = currPtr->link;
      else prevPtr->link = currPtr->link;
      if (currPtr == lastPtr) lastPtr = prevPtr;
      delete currPtr;
      length--;
   }
}
// Reset list 
void List::ResetList(){
   currentPos = dataPtr;
}
// GetNextItem returns the next varible "item" in the list
ItemType List::GetNextItem(){
   ItemType item;
   item = currentPos->component;
   currentPos = currentPos->link;
   return item;
}
// Get length
int List::GetLength() const{
   return length;
}
// Checks if list is empty
bool List::IsEmpty() const{
   return (dataPtr == NULL);
}
// Checks next node
bool List::HasNext() const{
   return (currentPos != NULL);
}
// Checks if full
bool List::IsFull() const{
   return false;
}
// Checks if node is there
bool List::IsThere(ItemType item) const{
   NodePtr currPtr = dataPtr;
   while (currPtr != NULL && currPtr->component != item)
      currPtr = currPtr->link;
   if (currPtr != NULL) return true;
   else return false;
}
int main(){
   List L1,L2, L3, L4;
   int n, x;
   cin >> n;
   //read first list
   for (int i=0; i<n; i++){
      cin >> x;
      L1.Insert(x);
   }
   //read second list
   for (int i=0; i<n; i++){
      cin >> x;
      L2.Insert(x);
   }
   cout << "Given List L1: " << endl;
   L1.PrintForward();
   cout << endl;
   cout << "Given List L2: " << endl;
   L2.PrintForward();
   cout << endl;

   cin >> x; // Read item to split the first list
   cout << "Split Data: " << x << endl;
   L3 = L1.split_ver1(x);
   cout << "After splitting L1, first part is: " << endl;
   L1.PrintForward();
   cout << "After splitting L1, second part is: " << endl;
   L3.PrintForward();
   cin >> x; // Read item to split the second list
   cout << "Split Data: " << x << endl;
   L4 = L2.split_ver2(x);
   cout << "After splitting L2, first part is: " << endl;
   L2.PrintForward();
   cout << "After splitting L2, second part is: " << endl;
   L4.PrintForward();

   return 0;
}