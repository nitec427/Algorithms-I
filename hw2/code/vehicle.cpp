#include "vehicle.h"
void Vehicle::write_id(int x){
    fstream out_file;
    out_file.open("my_call_hist.txt", ios::app); // append to the file 
    out_file << this->car_id << '\n';
    out_file.close();
}
bool operator<(const Vehicle& v1, const Vehicle& v2){
    /* Compare the vehicles according to their key_vals */
    if(v1.key_val <= v2.key_val)
        return true;
    return false;
}