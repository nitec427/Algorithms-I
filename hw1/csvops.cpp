void read_csv(vector<Tweet>& tweets,const string& f_name, int tw_num){
    fstream f_in;
    f_in.open(f_name, ios::in); // Open the file for input 

    string dtime, utime, artist, t_title, country, id;
    /* For reading CSV file line by line */
    string row, blank;

    int index = 0;
    // CSV file is a little bit complicated
    while(f_in >> id){ // first field is input
        getline(f_in,row);
        stringstream ss(row);

        getline(ss, blank, '\t'); // I had to use blank here because the structure of the CSV file.
        getline(ss, dtime, '\t');
        getline(ss, utime, '\t');
        getline(ss, artist, '\t');
        getline(ss, t_title, '\t');
        getline(ss, country, '\t');

        if (country == "country") // to ignore the first line
            continue;
        else{
            Tweet tw(stoi(id), utime, dtime, country, artist, t_title);
            tweets.push_back(tw);
            index++;
        }
        if(index == tw_num)
            break;
    }
    f_in.close();
}

void write_csv(const string& f_name, vector<Tweet> & tweets){
    fstream f_out;
    
    f_out.open(f_name, ios::out); // Open the file for output 

    f_out<<"tweet_id	tweet_datetime	tweet_unixtime	artist_name	track_title	country\n";

    for(size_t i=0;i<tweets.size();i++){
        f_out << tweets[i].tw_id << '\t';
        f_out << tweets[i].tw_datetime << '\t';
        f_out << tweets[i].tw_unixtime << '\t';
        f_out << tweets[i].artist_name << '\t';
        f_out << tweets[i].track_title << '\t';
        f_out << tweets[i].tw_country << '\n';
    }
    
    f_out.close(); // Close the file
}