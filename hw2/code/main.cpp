#include "vehicle.h"
#include "heap.h"
/*  
İsmail Çetin
150180065
BLG 335E - Homework2
# compiled with ->  g++ .\main.cpp .\heap.cpp .\vehicle.cpp -Werror  
*/
class minPriorityQueue : public MinHeap{
    // Inherit from the minimum heap
    public:
    Vehicle extract_min();
    void decrease_key(int pos, double key);
    void insertCar(Vehicle car);
};
Vehicle minPriorityQueue::extract_min(){
        if(heap_size < 1){ // if there is no car in the heap do not execute this operation
            cerr << "Heap underflow. Aborted...";
            exit(-1);
        }
        Vehicle min = vehicles[0]; // get the root
        vehicles[0] = vehicles[vehicles.size()-1]; // put the last into first place
        vehicles.pop_back(); // delete element
        heap_size = vehicles.size(); // update size
        minHeapify(0);
        return min; // return root, which is the quickest 
}
void minPriorityQueue::decrease_key(int pos, double key = -1){// Key is default arg and I assign -1, because the division is always > 0 logically
    pos--; // 0 index
    if(pos>vehicles.size()) // check whether the given position is in range
        cerr << "Pos value is out of range" << endl; // if not warn 
    if (key > vehicles[pos].key_val) // check whether the given key is smaller than the value of vehicles[pos] 
        cerr << "New key cannot be bigger than current key";
    else
        vehicles[pos].key_val = key;
    // check whether you reach the root, otherwise compare the parent_key with current_key and swap if the parent is larger
    while(pos>0 && vehicles[parent(pos)].key_val > vehicles[pos].key_val){
        // Traverse the tree from bottom up. This will take O(logn) times for which n is equal to n is the number of nodes. Which is same as car number
        swap(vehicles[pos], vehicles[parent(pos)]);
        pos = parent(pos);
    }
}
void minPriorityQueue::insertCar(Vehicle car){
    vehicles.push_back(car); // push the car to vector
    heap_size = vehicles.size(); //update heap_size
    decrease_key(heap_size, car.key_val); //use decrease key (as it is given in slides)
}
void swap(Vehicle& v1, Vehicle& v2){
    Vehicle temp = v1;
    v1 = v2;
    v2 = temp;
}
void read_execute_requests(minPriorityQueue min_q, const string& f_name, int n){
    fstream in_file;
    in_file.open(f_name, ios::in);
    string location,distance,lucky_num;
    string input; // read the line into input string
    int op_count = 0; // counter
    while(getline(in_file, input)){
        stringstream ss(input); // create stringstream from input
        // I read all values in string form and transform them necessary types
        getline(ss, location, '\t');
        getline(ss, distance, '\t');
        getline(ss, lucky_num, '\n');
        if(location == "location")
            continue; // don't process first row
        else{
            // otherwise if lucky_num is 0 call the vehicle in the first position
            int num = stoi(lucky_num); // convert lucky_num (string) to int
            if(!num){
                // Call the first car in the queue, then update its location and distance and put it again
                Vehicle car = min_q.extract_min();
                car.distance = stod(distance);
                car.location = location;
                car.key_val = stod(distance) / car.speed; // new key_val
                min_q.insertCar(car);
                op_count+=2;
                if(op_count <= n) // when you exceed break the loop and stop execution
                    car.write_id(car.car_id);
                else
                    break;
            }
            else{
                min_q.decrease_key(num+1);// 0 based indexing
                // Extract the car from the top of heap
                Vehicle car = min_q.extract_min();
                // Update distance and location and k_val
                car.distance = stod(distance);
                car.location = location;
                car.key_val = stod(distance) / car.speed;
                min_q.insertCar(car); // insert the car for which lucky num was given
                op_count+=3;
                if(op_count <= n) // when you exceed break the loop and stop execution
                    car.write_id(car.car_id);
                else
                    break;
            }
        }
    }
    in_file.close();
}

int main(int argc, char** argv){
    minPriorityQueue minQueue; // assigned 0 to heap_size in constructor
    int n = stoi(argv[1]); // take the argument
    minQueue.read_file("vehicles.txt"); // read all the vehicles
    minQueue.buildMinHeap(); // as its name suggests
    clock_t time = clock(); // start timer
    read_execute_requests(minQueue,"requests.txt",n);
    time = clock() - time; // calculate the time
    cout << "It took " << (float) time / CLOCKS_PER_SEC << " seconds to execute requests" << endl; 
}