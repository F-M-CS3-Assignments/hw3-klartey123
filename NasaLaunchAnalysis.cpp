#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "TimeCode.cpp"
#include "TimeCode.h"

using namespace std;

// Function to split a string based on a delimiter
vector<string> split(string line, char delimiter) {
    vector<string> results;
    string temp_string;
    
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != delimiter) {
            temp_string += line[i];
        } else {
            results.push_back(temp_string);
            temp_string = ""; // Reset temp string
        }
    }
    if (!temp_string.empty()) {
        results.push_back(temp_string); // Ensure last element gets added
    }
    return results;
}

// Function to extract time from a line
TimeCode parse_line(string line) {
    vector<string> separate = split(line, ',');
    string time = "";
    
    // Loop through the columns to find the one containing time
    for (int i = 0; i < separate.size(); i++) {
        if (separate[i].find("UTC") != string::npos) { // Checking if 'UTC' is in the string
            vector<string> timeParts = split(separate[i], ' '); // Splitting by space
            
            for (int j = 0; j < timeParts.size(); j++) {
                if (timeParts[j].find(":") != string::npos) { // Finding the actual time
                    time = timeParts[j];
                    break;
                }
            }
            break; // Exit loop after finding time
        }
    }
    
    if (time.empty()) { // If no time was found, return default TimeCode
        return TimeCode(0, 0, 0);
    }
    
    // Ensure time string is trimmed of spaces
    time.erase(remove(time.begin(), time.end(), ' '), time.end());
    
    // Split the time string into hours and minutes (only HH:MM format is expected)
    vector<string> time_parts = split(time, ':');
    if (time_parts.size() != 2) { // Ensure we only get HH:MM format
        return TimeCode(0, 0, 0);
    }
    
    int hours = stoi(time_parts[0]); // Convert string to integer
    int minutes = stoi(time_parts[1]);
    int seconds = 0; // Since dataset does not contain HH:MM:SS, default seconds to 0
    
    return TimeCode(hours, minutes, seconds); // Return extracted time
}

int main() {
    string file_name;
    cout << "Enter file name: ";
    cin >> file_name;
    vector<TimeCode> my_time; // Vector to store extracted time values

    ifstream inFS(file_name);
    if (!inFS.is_open()) {
        cout << "Could not open file: " << file_name << endl;
        return 1;
    }

    string line;
    int skipped_zeroes = 0; // Counter for invalid entries
    int valid_data_points = 0; // Counter for valid data points
    getline(inFS, line); // Skip the header line
    
    while (getline(inFS, line)) {
        TimeCode tc = parse_line(line);
        if (tc.GetHours() == 0 && tc.GetMinutes() == 0) {
            skipped_zeroes++; // Count invalid entries
        } else {
            my_time.push_back(tc);
            valid_data_points++; // Count valid entries
        }
    }
    
    inFS.close(); // Close the file when done

    if (my_time.empty()) {
        cout << "No valid launch times found. Cannot compute an average." << endl;
        return 1;
    }

    // Compute the average launch time
    long long unsigned int total_time = 0;
    for (int i = 0; i < my_time.size(); i++) {
        total_time += my_time[i].ComponentsToSeconds(my_time[i].GetHours(), my_time[i].GetMinutes(), 0); // Always set seconds to 0
    }

    long long unsigned int average_seconds = total_time / my_time.size(); // Compute average
    TimeCode average_time(0, 0, average_seconds); // Convert back to TimeCode format

    cout << valid_data_points << " data points." << endl;
    cout << "Average: " << average_time.ToString() << endl; // Print average launch time
    return 0;
}