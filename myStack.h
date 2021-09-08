#pragma once
#include<iostream>
using namespace std;

template <class Type>
class myStack
{
public:
	myStack();
	myStack(const myStack<Type>&);
	const myStack<Type>& operator=(const myStack<Type>&);
	~myStack();

	void push(const Type&);
	void pop();
	Type top() const;
	bool isEmpty() const;
	int size() const;
	void traverse(void (*func)(Type)) const;

private:
	struct node
	{
		Type item;
		node * next;
	};

	node * topOfmyStack;
};

//Constructor
template <class Type>
myStack<Type>::myStack()
{
	topOfmyStack = nullptr;
}

//Copy constructor that performs a deep copy of the copy object
template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
	myStack<Type>::node * tc; //Top copy
	myStack<Type>::node * cc; //Current copy
	myStack<Type>::node * pc; //Previous copy 
	myStack<Type>::node * copyIndex; 
	tc = nullptr; 
	pc = nullptr;
	copyIndex = copy.topOfmyStack; //Start copying copy's data, if any

	while(copyIndex != nullptr){

		cc = new myStack<Type>::node();
		cc -> item = copyIndex -> item;
		cc -> next = nullptr;
		if(tc == nullptr){	//If top copy is null, set it equal to current copy
			tc = cc;
		}
		if(pc != nullptr){	//If previous copy isn't null, set pc next to current
			pc -> next = cc;
		}
		pc = cc;
		copyIndex = copyIndex -> next;
	}

	topOfmyStack = tc;

}

template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
	myStack<Type>::node * tc; //Top copy
	myStack<Type>::node * cc; //Current copy
	myStack<Type>::node * pc; //Previous copy 
	myStack<Type>::node * copyIndex; 

	if(*this == rhs){
		return *this;
	}
	while(!isEmpty()){
		this->pop();
	}
	
	tc = nullptr; 
	pc = nullptr;
	copyIndex = rhs.topOfmyStack; //Start copying copy's data, if any

	while(copyIndex != nullptr){

		cc = new myStack<Type>::node();
		cc -> item = copyIndex -> item;
		cc -> next = nullptr;
		if(tc == nullptr){	//If top copy is null, set it equal to current copy
			tc = cc;
		}
		if(pc != nullptr){	//If previous copy isn't null, set pc next to current
			pc -> next = cc;
		}
		pc = cc;
		copyIndex = copyIndex -> next;
	}

	topOfmyStack = tc;

}

//Destructor
template<class Type>
myStack<Type>::~myStack()
{
	myStack<Type>::node * temp = topOfmyStack;
	while(temp != nullptr){
		topOfmyStack = topOfmyStack->next;
		delete temp;
		temp = topOfmyStack;
	}

}

//Pushes a new node to the top of the stack (aka a head insert) 
//and assigns insert into this new node’s item field
template <class Type>
void myStack<Type>::push(const Type& insert)
{
	myStack<Type>::node * newTop = new myStack<Type>::node();
	newTop->item = insert;
	newTop->next = topOfmyStack;
	topOfmyStack = newTop;
}


//Removes the top element (head removal) if the stack is not empty,
//otherwise nothing happens
template <class Type>
void myStack<Type>::pop()
{
	if(topOfmyStack == nullptr){ 
		return;
	}
   else{
    	node *temp = topOfmyStack;	
		topOfmyStack = topOfmyStack->next;
		delete temp;
   }
}

//Returns the item of the top node in the stack
template <class Type>
Type myStack<Type>::top() const
{
	if(topOfmyStack == nullptr){
		cerr << "Error: Top of stack is NULL" << endl;
	}
	return topOfmyStack->item;
}


//Returns true if the stack is empty and false if the stack is not empty
template <class Type>
bool myStack<Type>::isEmpty() const
{
	if(topOfmyStack == nullptr){
		return true;
	}
	else{
		return false;
	}
}


template <class Type>
int myStack<Type>::size() const{

	int counter = 0;
	node *current = topOfmyStack;
	while(current != nullptr){
		counter++;
		current = current->next;
	}

	return counter;
}

template <class Type>
void myStack<Type>::traverse(void (*func)(Type)) const{

	node *current = topOfmyStack;
	while(current != nullptr){
		func(current->item);
		current = current->next; 
	}
}