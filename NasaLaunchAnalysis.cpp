// Author; Kelvin Lartey

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "TimeCode.cpp"

using namespace std;

// storing my strings


vector<string> split(string line, char delimiter){
    // to store my string sseprated by commas. 

    vector<string> results;
    string temp_string;
    
    for (int i = 0; i < line.length(); i ++){
        if (line[i] != delimiter){
            temp_string += line[i];
        }
        else{
            results.push_back(temp_string);
            temp_string = "";
        }

    }
    if (!temp_string.empty()) {
        results.push_back(temp_string);
    }

    return results;

}

TimeCode parse_line(string line) {

    string time;
    vector<string> separate = split (line, ',');

    // okay so a traker is needed to stop it when it reaches a time when it is not true
    bool found_time = false;

    //using the find function ; https://cplusplus.com/reference/string/string/find/
    for (int i= 0; i < separate.size(); i++){

        // Using UTC as a constant that is always there when a time is available then I can 
        // use that to extract the time infront of it.
        if (separate[i].find("UTC") != string::npos){
            vector<string> timeParts = split(separate[i], ' ');

            // To makr sure it has the time. 
            if (timeParts.size() >= 2){
                for (string colon : timeParts){
                    if (colon.find (":") != string :: npos){
                        time = colon; 
                        found_time = true;
                        break;
                    } 
                }
            }
        }
    }
    if (!found_time || time.empty()) {
        return TimeCode(0, 0, 0);  // When 000 are added it increases the size of the vector 
        // meaning the total average is lower.
    }
                
    // convert the times to timecode. 
               
    vector<string> separate_parts = split(time, ':');
    if (separate_parts.size() < 2) {
    // For cases when the time value is empty
        return TimeCode(0, 0, 0);
    }

    int hours = stoi(separate_parts[0]);
    int minutes = stoi(separate_parts[1]);

        return TimeCode(hours, minutes, 0);
}

int main() {
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    vector <TimeCode> my_time;

    ifstream inFS(file_name);
    if (!inFS.is_open()) {
        cout << "Could not open file: " << file_name << endl;
        return 1;
    }

    string line;
    while (getline(inFS, line)) {  
        TimeCode tc = parse_line(line);  
        if (!(tc.GetHours() == 0 && tc.GetMinutes() == 0 && tc.GetSeconds() == 0)) {
            my_time.push_back(tc);  
        }
    }
    

    inFS.close();  

    if (my_time.empty()) {
        cout << "No valid launch times found. Cannot compute an average." << endl;
        return 1;
    }

    // Now to average my time out
    long long unsigned int total_time = 0;
    for (int i = 0; i < my_time.size(); i++) {
        cout << my_time[i].ToString() << endl;  
        unsigned int hours = my_time[i].GetHours();
        unsigned int minutes = my_time[i].GetMinutes();
        unsigned int seconds = my_time[i].GetSeconds();

       

        total_time += my_time[i].ComponentsToSeconds(hours, minutes, seconds);
    }
    long long unsigned int average_seconds = total_time / my_time.size();
    // Convert back because timecode does not accept t seconds. 
    TimeCode average_time(0, 0, average_seconds);

    cout << "Average launch time: " << average_time.ToString() << endl;
    return 0;
}
