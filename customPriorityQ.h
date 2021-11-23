#include <iostream>
using namespace std;

template<class Type>
class priorityQ {

public:
    priorityQ(int = 10);
    priorityQ(const priorityQ<Type>&);
    ~priorityQ();
    const priorityQ<Type>& operator=(const priorityQ<Type>&);
    void insert(const Type&);
    void deleteHighestPriority();
    Type getHighestPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;
private:
    int capacity;  // Length of heap array
    int items;   // Amount of items stored in priority heap
    Type * heapArray;  // Contains elements for priority queue
};

// Constructor
template<class Type>
priorityQ<Type>::priorityQ(int capacity){

    this->capacity = capacity;
    if(capacity > 0){
        this->heapArray = new Type[capacity];
    }
    else{
        this->heapArray = nullptr;
    }
    
    this->items = 0;
    
}

// Copy Constructor
template<class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy){
    // Copied from constructor

    this->capacity = copy.capacity;
    if(capacity > 0){
        this->heapArray = new Type[capacity];
    }
    else{
        this->heapArray = nullptr;
    }
    
    this->items = copy.items;
    
    for(int i = 0; i < capacity; i++){
        this->heapArray[i] = copy.heapArray[i];
    }
}

// Destructor
template<class Type>
priorityQ<Type>::~priorityQ(){

    delete[] this->heapArray;
}

// Operator Function
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs){

    if(*this == rhs){
        return rhs;
    }

    delete[] this->heapArray;

    this->capacity = rhs.capacity;
    if(capacity > 0){
        this->heapArray = new Type[capacity];
    }
    else{
        this->heapArray = nullptr;
    }
    
    this->items = rhs.items;
    
    for(int i = 0; i < capacity; i++){
        this->heapArray[i] = rhs.heapArray[i];
    }

    return *this;
}

// Insert Function
template <class Type>
void priorityQ<Type>::insert(const Type& element){

    if(items >= capacity - 1){
        // Doubles heap
        Type * ptr = new Type[2 * capacity];

        for(int i = 0; i < capacity; i++){
            ptr[i] = heapArray[i];
        }

        capacity = 2 * capacity;
        delete[] heapArray;
        heapArray = ptr;
    }

    items++;
    heapArray[items] = element;
    bubbleUp(items);
}


template <class Type>
void priorityQ<Type>::deleteHighestPriority(){

    if(heapArray == nullptr){
        return;
    }

    heapArray[1] = heapArray[items];
    items--;
    bubbleDown(1);
}


template <class Type>
Type priorityQ<Type>::getHighestPriority() const{

    return heapArray[1];
}

template <class Type>
bool priorityQ<Type>::isEmpty() const {

    if(items == 0 || heapArray == nullptr){
        return true;
    }

    return false;
}

template <class Type>
void priorityQ<Type>::bubbleUp(int index){

    int parent = index / 2;
    while(parent > 0){
        if(heapArray[index] < heapArray[parent]){
            Type temp = heapArray[index];
            heapArray[index] = heapArray[parent];
            heapArray[parent] = temp;

            index = parent;
        }
        parent = parent / 2;
    }
}

template <class Type>
void priorityQ<Type>::bubbleDown(int index) {

    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;

    while(2 * index <= items){
        if(heapArray[index] < heapArray[leftChild]){
            Type temp = heapArray[index];
            heapArray[index] = heapArray[leftChild];
            heapArray[leftChild] = temp;

            index = leftChild;
        }
        else if(heapArray[index] < heapArray[leftChild]){
            Type temp = heapArray[index];
            heapArray[index] = heapArray[rightChild];
            heapArray[rightChild] = temp;

            index = rightChild;
        }
        else{
            break;
        }

        leftChild = 2 * index;
        rightChild = 2 * index +1;

    }
}

template <class Type>
int priorityQ<Type>::getSize() const {
    return items;
}