#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h> 

using namespace std; 
class Vehicle{
    public:
        int car_id;
        string location;
        double distance;
        int speed;
        double key_val; // distance / speed
        
        // Constructor for vehicles. Here, key_value is calculated for each car.
        Vehicle(int id, string loc, double dist, int sp){
            car_id = id;
            location = loc;
            distance = dist;
            speed = sp;
            key_val = distance / speed;
        };
        // Implement comparison functions for car's keys
        friend bool operator< (const Vehicle& v1, const Vehicle& v2); //ok
        // Print car information
        void print_info(){cout << "Id: " << car_id << " Location: " << location << " distance: " << distance << " speed: " << speed << " kval " << key_val<<  endl;}; //helper function
        void write_id(int x); // write id of the cars line by line
};