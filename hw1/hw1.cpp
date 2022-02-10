// İsmail Çetin
// 150180065
// Compiled with the following command
// g++ -std=c++11 .\hw1.cpp -Werror -Wall -o hw1  
#include "hw1.h"
#include "quicksort.cpp" // quicksort implementations
#include "csvops.cpp" // read and write_csv functions
bool operator < (const Tweet& tw1, const Tweet& tw2){
    // convert string to lowercase string for case insensitive comparison
    string cn1 = tw1.tw_country;
    string cn2 = tw2.tw_country;
    string an1 = tw1.artist_name; 
    string an2 = tw2.artist_name; 

    transform(cn1.begin(), cn1.end(), cn1.begin(), ::tolower);
    transform(cn2.begin(), cn2.end(), cn2.begin(), ::tolower);
    transform(an1.begin(), an1.end(), an1.begin(), ::tolower);
    transform(an2.begin(), an2.end(), an2.begin(), ::tolower);
// If the first string comes before the second string alphabetically then the first one is smaller, same is valid for strings containing only numbers. We compare them as if they are integral numbers even if they are strings.
    if(cn1 < cn2)
        return true;
    else if(cn1 == cn2){
        if(an1 < an2)
            return true;
        else if (an1 == an2){
            // Ascending order of unix_time
            if(tw1.tw_unixtime < tw2.tw_unixtime)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
    }
void swap (Tweet& a, Tweet& b){
    Tweet temp = a;
    a = b;
    b = temp;
}

int main(int argc, char** argv){
    if(argc != 5){
        cerr << "Inappropriate input is provided. Please revise your input again!";
        exit(EXIT_FAILURE);
    };
    int tw_num = stoi(argv[1]); // how many tweets are to be used
    /* Before using stoi, I used atoi however I read the cppreference  page about stoi back then and learned that stoi is safer than atoi(c-style string).  */
    
    string pv_sel = argv[2]; // pivot select algorithm
    string in_path = argv[3]; 
    string out_path = argv[4];

    vector<Tweet> tws;

    clock_t start,end;
    // Read the CSV file into vector<Tweet> in the following function
    read_csv(tws, in_path, tw_num);

    
    if(pv_sel == "randomized"){
        start = clock();
        random_qsort(tws, 0, tw_num-1);
        end = clock();
    }
    else{
        start = clock();
        det_qsort(tws, 0, tw_num-1);
        end = clock();
    }
    write_csv(out_path, tws);
    cout << "Sorted in " << double(end - start) << " miliseconds by using " << pv_sel << " pivot selection." << endl;    
    exit(EXIT_SUCCESS);
}