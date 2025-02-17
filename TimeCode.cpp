// Author; Kelvin Lartey


#include <iostream>
#include "TimeCode.h"

using namespace std;

TimeCode:: TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0){
   
    if (hr< 0 || min < 0 || sec < 0){
        // wasn't sure if to use a try and catch but this wesite helped
        //https://stackoverflow.com/questions/8480640/how-to-throw-a-c-exception
        throw std::invalid_argument ("Your time cannot be negative");
    }
    // Thinking about roll overs and how to convert things
    // if sec >=60 change it to mins. If mins >=60 cohnage it to hrs.
    if (sec >= 60){
        min += sec / 60;   
        // now for the remainder has to be kept in secs
        sec = sec %60;
    }
    if (min >= 60){
        hr +=min/60;
        min = min%60;
    }
        t = ComponentsToSeconds(hr, min, sec);   
        
}
   
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = (t % 60);
}

   static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
        // converting to sec

     return (hr * 3600) + (min * 60) + sec;

   }
   string TimeCode::ToString() const{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;
    GetComponents(hr, min, sec);

    string new_output = to_string(hr)+ ":" + to_string(min)+ ":"+ to_string(sec);

    return new_output;

   }
// Adding the times together to make a new time. 
   TimeCode TimeCode::operator+(const TimeCode& other) const {
    long long unsigned int new_time;

    new_time = t + other.t;
    return new_time;

   }

   TimeCode TimeCode :: operator-(const TimeCode& other) const{
    long long unsigned int new_time;

    new_time = t - other.t;
    return new_time;

   }

