// Author; Kelvin Lartey

#include <iostream>
#include "TimeCode.h"

using namespace std;


TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {

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

// my copy functiuon;
TimeCode::TimeCode(const TimeCode& tc) {
    this->t = tc.t;  
}

// This function will be converting the hr, min and secs. 
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = (t % 60);
}

// Now we are setting the hours
void TimeCode::SetHours(unsigned int hours) {
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec); 
    hr = hours; 
    t = ComponentsToSeconds(hr, min, sec); 
}

void TimeCode:: SetMinutes(unsigned int minutes){
    unsigned int hr, min, sec;
    GetComponents(hr, min, sec);

    // throw an exception for minutes that is higher than 59 minutes

    if (minutes >= 60){
        throw invalid_argument("Minutes are less than 60.");
    }
    min = minutes;
    t = ComponentsToSeconds(hr,min, sec);
}
void TimeCode:: SetSeconds(unsigned int seconds){
    unsigned int hr, min, sec;
    // throw an exception for seconds that is higher than 59 minutes
    GetComponents(hr, min, sec);
    if (seconds >= 60){
        throw invalid_argument("Seconds are less than 60.");
    }
    sec = seconds;
    t = ComponentsToSeconds(hr,min, sec);
}
unsigned int TimeCode:: GetHours() const{
    unsigned hr, min, sec;
    GetComponents (hr, min, sec);
    return hr;
}
unsigned int TimeCode ::GetMinutes()const{
    unsigned hr, min, sec;
    GetComponents (hr, min, sec);
    return min;
}
unsigned int TimeCode:: GetSeconds()const{
    unsigned hr, min, sec;
    GetComponents (hr, min, sec);
    return sec;
}

// forgot to add this function, now i am adding it to help my painter file
long long unsigned int TimeCode::GetTimeCodeAsSeconds() const {
    return t;
}


// my rest function, turns everything back to zero

void TimeCode::reset() {
    t = 0;  
}

 long long unsigned int TimeCode ::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
        // // convert hours, minutes, and seconds to t seconds. 

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
    return TimeCode(0, 0, new_time);

   }

   TimeCode TimeCode :: operator-(const TimeCode& other) const{
    // first have to deal with negative value/ negative time
    if (t < other.t ){
        throw invalid_argument("This will result in a negative time");
    }
    long long unsigned int new_time;

    new_time = t - other.t;
    return TimeCode(0,0, new_time);

   }

   TimeCode TimeCode::operator* (double a) const{
    // Another exception would be if there is a negative number. Well it works for normal 
    // math numbers, but for time, we can't even have -time so lets take care of that

    if (a < 0 ){
        throw invalid_argument("This will result in a negative time");
    }
    long long unsigned int muliple_time;
         muliple_time = t * a;

          return TimeCode (0,0, muliple_time);
   }
   TimeCode TimeCode :: operator/ (double a)const{

    // for one you can divide by a negative

    if (a<=0 ){
        throw invalid_argument("You can't divide by a negaive number");

    }
    long long unsigned int divided_number;
    divided_number = t/a;

        return TimeCode (0,0,divided_number);
   }

   // My bool functions and their implementations
   // This function is for when the times are the same

   bool TimeCode :: operator == (const TimeCode& other) const{
    if (this->t == other.t) {
        return true;
    }
    return false;
    
   }
// Different times 
    bool TimeCode :: operator != (const TimeCode& other) const{
        
        if (this->t != other.t) {
            return true;
        }
        return false;
    }
// one time is less than the other time
    bool TimeCode :: operator < (const TimeCode& other) const{
        if (this -> t < other.t ){
            return true;
        }
        return false;
    }

    // Is the time less than or equal too
    bool TimeCode :: operator <= (const TimeCode& other) const{
        if (this -> t <= other.t ){
            return true;
        }
        return false;
    }

    // is the time the greater than the other time
    bool TimeCode :: operator >(const TimeCode& other) const{
        if (this -> t > other.t ){
            return true;
        }
        return false;
    }
    // is the time greater than or equal to
    bool TimeCode :: operator >= (const TimeCode& other) const{
        if (this -> t >= other.t ){
            return true;
        }
        return false;
    }
        
        
