// Priority queue from assignment 8

#include <iostream>
#include <vector>

struct trainPath {
    std::string indicator;
    int pathWeight;

    bool operator<(const trainPath& rhs) {
        if (pathWeight < rhs.pathWeight) {
            return true;
        }

        return false;
    }
};

template <class Type>
class priorityQ {
    public:
        priorityQ(int = 10);
        priorityQ(std::vector<Type>);
        priorityQ(const priorityQ<Type>&);
        ~priorityQ();

        const priorityQ<Type>& operator=(const priorityQ<Type>&);
        void insert(Type);
        void deletePriority();
        Type getPriority() const;
        bool isEmpty() const;
        void bubbleUp(int);
        void bubbleDown(int);
        int getSize() const;

    private:
        int capacity;
        int size;
        Type * heapArray;
};

template <class Type>
priorityQ<Type>::priorityQ(int cap) {
    capacity = cap;
    size = 0;
    heapArray = new Type[capacity];
}

template <class Type>
priorityQ<Type>::priorityQ(std::vector<Type> v) {

    capacity = v.size() + 1;
    size = capacity;

    heapArray = new Type[capacity];

    for (int i = 1; i < v.size; i++) {
        heapArray[i] = v[i - 1];
    }
}

template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy) {
    capacity = copy.capacity;
    size = copy.size;

    heapArray = new Type[capacity];

    for (int i = 1; i <= size; i++) {
        heapArray[i] = copy.heapArray[i];
    }
}

template <class Type>
priorityQ<Type>::~priorityQ() {
    delete[] heapArray;
}

template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs) {
    capacity = rhs.capacity;
    size = rhs.size;

    for (int i = 1; i <= size; i++) {
        heapArray[i] = rhs.heapArray[i];
    }
    
    return this;
}

template <class Type>
void priorityQ<Type>::insert(Type item) {

    size++;

    // Doubles heapArray if heapArray is full
    if (size == capacity) {
        capacity = capacity * 2;

        Type * copy = new Type[capacity];

        for (int i = 1; i < size; i++) {
            copy[i] = heapArray[i];
        }

        delete[] heapArray;
        heapArray = copy;
    }

    // Then insert element
    heapArray[size] = item;
    
    // Bubble up
    bubbleUp(size);

    return;
}

template <class Type>
void priorityQ<Type>::deletePriority() {
    heapArray[1] = heapArray[size];
    size -= 1;

    // Bubble down
    if (size != 0) {
        bubbleDown(1);
    }

    return;
}

template <class Type>
Type priorityQ<Type>::getPriority() const {
    return heapArray[1];
}

template <class Type>
bool priorityQ<Type>::isEmpty() const {
    if (size == 0) { 
        return true; 
    }
    return false;
}

template <class Type>
void priorityQ<Type>::bubbleUp(int index) {
    // Recursive Function
    
    // Checks if only one element in the array
    if (index == 1) { return; }

    int parent = index / 2;

    // Swaps elements
    if (heapArray[index] < heapArray[parent]) {
        Type copy = heapArray[parent];
        heapArray[parent] = heapArray[index];
        heapArray[index] = copy;
    }

    bubbleUp(parent);

    return;
}

template <class Type>
void priorityQ<Type>::bubbleDown(int index) {
    // Recursive Function
    // Index is the parent

    int left, right;

    // Checks if only one element in the array
    if (size <= 1) { return; }

    // Checks if there is a left child
    left = index * 2;
    if (left > size) { return; }

    // Checks left child
    if (heapArray[left] < heapArray[index]) { 
        Type copy = heapArray[left];

        heapArray[left] = heapArray[index];
        heapArray[index] = copy;
        
        bubbleDown(left);
    }

    // Checks if there is a right child
    right = left + 1;
    if (right > size) { return; }

    // Checks right child
    if (heapArray[right] < heapArray[index]) {
        Type copy = heapArray[right];
        
        heapArray[right] = heapArray[index];
        heapArray[index] = copy;
        
        bubbleDown(right);
    }

    return;
}

template <class Type>
int priorityQ<Type>::getSize() const {
    return size;
}
