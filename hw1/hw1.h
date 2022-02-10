#pragma once
#include <iostream> 
#include <fstream>
#include <sstream> // to partition the string obtained from csv
#include <vector>
#include <time.h> // to use clock function
#include <string>
#include <algorithm> // used for transform() function which returns whole string as lowercase
using namespace std;
class Tweet{
    // Because this lecture is not an object oriented course, I think we do not need to use access modifiers
    public:
    int tw_id;
    string tw_unixtime; // i regard unix_time and datetime as a string because comparison is easy
    string tw_datetime;
    string track_title;
    string artist_name;
    string tw_country;
    
    // constructor function
    Tweet(int id,const string& utime,const string& dtime,const string& country,const string& artist,const string& title){
        tw_id = id;
        tw_unixtime = utime;
        tw_datetime = dtime;
        tw_country = country;
        artist_name = artist;
        track_title = title;
    }
    
    bool is_equal(Tweet tw){
        if(tw_country == tw.tw_country && tw_unixtime == tw.tw_unixtime &&  artist_name == tw.artist_name &&  track_title == tw.track_title && tw_datetime == tw.tw_datetime)
            return true;
        return false;
    }
    friend bool operator< (const Tweet& tw1, const Tweet& tw2);
};