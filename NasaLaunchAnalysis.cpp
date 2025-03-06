// Author; Kelvin Lartey


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "TimeCode.h"


using namespace std;


// function to split a string based on a delimiter
vector<string> split(string line, char delimiter) {
   vector<string> results;
   string temp_string;
  
   for (int i = 0; i < line.length(); i++) {
       if (line[i] != delimiter) {
           temp_string += line[i];
       } else {
           results.push_back(temp_string);
           temp_string = ""; 
       }
   }
   if (!temp_string.empty()) {
       results.push_back(temp_string); // make sure the last element is added
   }
   return results;
}


// Function to extract time from a line
TimeCode parse_line(string line) {
   vector<string> separate = split(line, ',');
   string time = "";
  
   // only valid time formats HH:MM (with or without UTC) the mistake i was first making
   for (int i = 0; i < separate.size(); i++) {
       if (separate[i].find(":") != string::npos) { // Find a column containing HH:MM format
           vector<string> time_parts = split(separate[i], ' '); 
          
           for (int j = 0; j < time_parts.size(); j++) {
               if (time_parts[j].find(":") != string::npos) { // Extract only the HH:MM part
                   time = time_parts[j];
                   break;
               }
           }
           break;
       }
   }
  
   if (time.empty()) { // If no time was found, return default TimeCode
       return TimeCode(0, 0, 0);
   }
   // Trim spaces from extracted time
   time.erase(remove(time.begin(), time.end(), ' '), time.end());
  
   // split the time string into hours and minutes 
   vector<string> time_parts = split(time, ':');
   if (time_parts.size() != 2) { 
       return TimeCode(0, 0, 0);
   }
  
   // Debugging 
   //cout << "Extracted time: [" << time_parts[0] << ":" << time_parts[1] << "]" << endl;
  
   int hours = stoi(time_parts[0]); 
   int minutes = stoi(time_parts[1]);
   int seconds = 0; 
   // default for seconds is 0
  
   return TimeCode(hours, minutes, seconds); 
}


int main() {
   string file_name;
   cout << "Enter file name: ";
   cin >> file_name;
   vector<TimeCode> my_time; 


   ifstream inFS(file_name);
   if (!inFS.is_open()) {
       cout << "Could not open file: " << file_name << endl;
       return 1;
   }

   string line;
   int skipped_zeroes = 0; // invalid entries
   int valid_data_points = 0; // valid data points
   getline(inFS, line);
  
   while (getline(inFS, line)) {
       TimeCode tc = parse_line(line);
       if (tc.GetHours() == 0 && tc.GetMinutes() == 0 && line.find("00:00 UTC") == string::npos) {
           skipped_zeroes++; 
           //cout << "Skipped Line: " << line << endl; 
       } else {
           my_time.push_back(tc);
           valid_data_points++; 
       }
   }
  
   inFS.close(); 


   if (my_time.empty()) {
       cout << "No valid launch times found. Cannot compute an average." << endl;
       return 1;
   }


   // Calculating the total time in seconds
   long long unsigned int total_time = 0;
   for (int i = 0; i < my_time.size(); i++) {
       total_time += my_time[i].GetTimeCodeAsSeconds();
   }
   // Calculating the correct average time in seconds
   long long unsigned int average_seconds = (total_time + (my_time.size() / 2)) / my_time.size();
   int avg_hours = average_seconds / 3600;
   int avg_minutes = (average_seconds % 3600) / 60;
   int avg_seconds = (average_seconds % 60);
   TimeCode average_time(avg_hours, avg_minutes, avg_seconds);


   cout << valid_data_points << " data points." << endl;
   cout << "Average: " << average_time.ToString() << endl; 
   return 0;
}

