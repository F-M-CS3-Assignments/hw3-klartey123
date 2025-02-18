// Author; Kelvin Lartey


#include <iostream>
#include "TimeCode.h"

using namespace std;

TimeCode:: TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0){
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

 long long unsigned int TimeCode ::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
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
    return TimeCode(0, 0, new_time);

   }

   TimeCode TimeCode :: operator-(const TimeCode& other) const{
    // first have to deal with negative value/ negative times
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

    if (t < 0 || a < 0 ){
        throw invalid_argument("This will result in a negative time");
    }
         double muliple_time;
         muliple_time = t * a;

          return TimeCode (0,0, muliple_time);
   }
   TimeCode TimeCode :: operator/ (double a)const{

    // for one you can divide by a negative

    if (a<=0 ){
        throw invalid_argument("You can't divide by a negaive number");

    }
    double divided_number;
    divided_number = t/a;

        return TimeCode (0,0,divided_number);
   }

   // My bool functions and their implementations

   







//    int main() {
//     TimeCode t1(1, 70, 90);  
//     // Output should be (2:11:30)
//     cout << "t1: " << t1.ToString() << endl;

//     TimeCode t2(0, 61, 0);  
//     // Output should be (1:1:0)
//     cout << "t2: " << t2.ToString() << endl;

//     return 0;
// }
