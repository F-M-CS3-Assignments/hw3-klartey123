#ifndef TimeCode_H
#define TimeCode_H

#include <iostream>

using namespace std;

class TimeCode{
    public:

        TimeCode(unsigned int hr = 0, unsigned int min = 0, long long unsigned int sec = 0);
        TimeCode(const TimeCode& tc);
        ~TimeCode(){};
        void SetHours(unsigned int hours);
        void SetMinutes (unsigned int mintutes);
        void SetSeconds (unsigned int seconds);

        void reset();

        unsigned int GetHours() const;
        unsigned int GetMinutes() const;
        unsigned int GetSeconds()const;
// changes the name from GetTImeCodeAsSeconds() to GetTimeCodeAsSeconds() the 'i' was
// capitalized, it made it difficult not to make a mistake. 
        long long unsigned int GetTimeCodeAsSeconds() const; 
        void GetComponents (unsigned int& hr, unsigned int& min, unsigned int& sec) const;
        static long long unsigned int ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec);

        string ToString () const;

        TimeCode operator+ (const TimeCode& other) const; 
        TimeCode operator- (const TimeCode& other) const;
        TimeCode operator* (double a) const;
        TimeCode operator/ (double a)const;

        bool operator == (const TimeCode& other) const;
        bool operator != (const TimeCode& other) const;

        bool operator < (const TimeCode& other) const;
        bool operator <= (const TimeCode& other) const;

        bool operator >   (const TimeCode& other) const;
        bool operator>= (const TimeCode& other) const;

private:
    long long unsigned int t = 0;
};
#endif