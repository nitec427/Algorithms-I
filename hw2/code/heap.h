#pragma once
#include "vehicle.h"
class MinHeap{
    // Heap is an array object whose attributes are given as length and heap_size in the slide. However, I just used the heap size
    public:
    vector<Vehicle> vehicles; // vector is used for ease and extensive methods.
    int heap_size;
    // MinHeap constructor
    MinHeap(){
        heap_size = 0;
    }
    // Heap Operations
    void minHeapify(int i); // min heap heapify method
    void buildMinHeap(); // building min heap
    void heapsort(); // At the beginning, I thought that we first sort the array in increasing order so I used this function. However, then I learned that we just need to use buildMinHeap and ignore heapsort function. However, since I implemented this function it is better not to delete.
    
    
    // Inline Functions
    // Left, right and parent is calculated according to 0-index.
    int left(int i) { return (i*2 + 1);};
    int right(int i) {return (2*i + 2);}
    int parent(int i) {return (i-1)/2;}; //Integer division truncates the number
    void read_file(string); // read vehicles into heap
    
};