#include "heap.h"
#include "vehicle.h"
void MinHeap::read_file(string in_name){
    fstream in_file;
    in_file.open(in_name, ios::in);
    string id,location,distance, speed;
    string input;
    while(getline(in_file, input)){
        stringstream ss(input);
        getline(ss, id, '\t');
        getline(ss, location, '\t');
        getline(ss, distance, '\t');
        getline(ss, speed, '\t');
        if(speed == "speed")
            continue; // don't record first row
        else{
        Vehicle new_car = Vehicle(stoi(id),location,stod(distance),stoi(speed)); // create the new vehicle with the given input
        vehicles.push_back(new_car);} // push it to the end of vehicles vector, which is inside the heap data structure
        
    }
    // Update heap size
    this->heap_size = vehicles.size();
    in_file.close();
}
void MinHeap::buildMinHeap(){
    int counter = vehicles.size() / 2;
    for (int i= counter; i >= 0;i--){
        minHeapify(i); 
    }
}
// MinHeapify works as expected. I take these parts (heapsort, minHeapify and buildminheap) from the lecture slides and alter them so that they can work with 0-indexed values.
void MinHeap::minHeapify(int cur){
    int left_child = left(cur);
    int right_child = right(cur);
    int smallest = cur; 
    if(left_child < heap_size && vehicles[left_child] < vehicles[cur]){
        smallest = left_child;
    }
     if(right_child < heap_size && vehicles[right_child] < vehicles[smallest]){
         smallest = right_child;
    }
    if(smallest != cur){
        swap(vehicles[cur], vehicles[smallest]);
        minHeapify(smallest);
    }
}
// In the beginning, I was mistakenly assuming that we need to get the root after the heapsort is finished. However, one of my friend said that I was mistaken and exclude heapsort from the project. Though, I keep it here because it works. 
void MinHeap::heapsort(){
    // minheap is already built
    for(int i= heap_size-1; i>=0;i--){
        swap(vehicles[0],vehicles[i]);
        heap_size--;
        minHeapify(0); // 0 indexing
    }
    // After heapsort elements must be reversed
    for(int i=0;i<vehicles.size()/2;i++){
        swap(vehicles[vehicles.size()-1-i],vehicles[i]);
    }
    heap_size = vehicles.size(); //restore heap size
}