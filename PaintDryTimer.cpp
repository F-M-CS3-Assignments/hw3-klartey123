// Author; Kelvin Lartey

#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)


using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

// Calculating the time remainif for the drying batch
long long int get_time_remaining(DryingSnapShot dss){
	// use the system to get the current time. 
	time_t current_time  = time(0);
	time_t elpase_time = current_time - dss.startTime  ;
	// now to get how long it takes for an object to dry. 
	long long int drying_time = dss.timeToDry->GetTimeCodeAsSeconds();
	long long int remaining_time = drying_time - elpase_time;
	return remaining_time;
	
	return 0;
}

// So to get the random string description for the batch
string drying_snap_shot_to_string(DryingSnapShot dss){
	// retrun my time into hh:: mm:: ss format.
	string drying_time = dss.timeToDry -> ToString();
	// this is to store the remainig time left. 
	long long int new_seconds_left= get_time_remaining(dss);
	// convert it all to the timecode here. 
	TimeCode remainingtime (0,0, new_seconds_left);
	// now convert to  string. 
	string remainingtime_instr = remainingtime. ToString();

	// return it in the format of Batch-846930886 (takes 0:44:9 to dry) time remaining: 0:44:9
	return dss.name + " (takes " + drying_time + " to dry) time remaining: " + remainingtime_instr;
}

double get_sphere_sa(double rad){
	// computing the area of a sphere. 
	double area_sphere = (4*M_PI *pow (rad, 2));
	return area_sphere;
}


TimeCode *compute_time_code(double surfaceArea){
	// So we are converting the surface area into seconds here for it to calculate. 
	// can calculate it as 1 cm = 1 sec
	long long int cal_drytime = surfaceArea;

	TimeCode* drying_time = new TimeCode (0,0,cal_drytime);

	return drying_time;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);

	// add more tests here
	DryingSnapShot dss1;
    dss1.startTime = time(0);
    TimeCode tc1 = TimeCode(0, 0, 10); 
    dss1.timeToDry = &tc1;
    long long int ans2 = get_time_remaining(dss1); 
    assert(ans2 >= 8 && ans2 <= 10);


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here
	double sa2 = get_sphere_sa(10.0);
    assert(1256.63 < sa2 && sa2 < 1256.64);

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	//come back to this and fix it in the timecope.cpp
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;
// one that is large.
	TimeCode *tc3 = compute_time_code(500.0);
    assert(tc3->GetTimeCodeAsSeconds() == 500);
    delete tc3;
// surface area with is 0
	TimeCode *tc4 = compute_time_code(0.0);
    assert(tc4->GetTimeCodeAsSeconds() == 0);
    delete tc4;
	// add more tests here
	cout << "ALL TESTS PASSED!" << endl;

}

int main() {

	tests ();

    vector<DryingSnapShot> dryingBatches;
    char option;

    while (true) {
		// user menu.
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> option;
		// makes everything easier, no lowercase or upper case just one. 
        option = tolower(option);

        if (option == 'a') {
            double radius;
            cout << "Enter radius: ";
            cin >> radius;

            if (radius <= 0) {
                cout << "Invalid radius! Must be positive.\n";
                continue;
            }

            double surfaceArea = get_sphere_sa(radius);
            TimeCode *dryingTime = compute_time_code(surfaceArea);

			// create a new batch
            DryingSnapShot newBatch;
			string the_rand_name = to_string(rand());
            newBatch.name = "Batch-" + the_rand_name;
            newBatch.startTime = time(0);
            newBatch.timeToDry = dryingTime;

            dryingBatches.push_back(newBatch);

            cout << "Added " << newBatch.name << " (takes " << dryingTime->ToString() << " to dry)"<<endl;
        } else if (option == 'v') {
            // View all drying batches
            cout << "Current Drying Batches:\n";

            vector<DryingSnapShot> remainingBatches;

    		for (int i = 0; i < dryingBatches.size(); i++) {
        		long long int remaining = get_time_remaining(dryingBatches[i]); 

        		if (remaining <= 0) {
            	// If drying is done, print and free memory
            	cout << dryingBatches[i].name << " is done drying!" << endl;
            		delete dryingBatches[i].timeToDry;  
        		} else {
            	// If not done, keep it in the new list
            	remainingBatches.push_back(dryingBatches[i]);
            	cout << drying_snap_shot_to_string(dryingBatches[i]) << endl; 
        	}
    	}
    		// replace the old vector with the remaining batches
    		dryingBatches = remainingBatches;

    		cout << dryingBatches.size() << " batches being tracked."<< endl;
		}

        else if (option == 'q') {
            // donot forget to clean up memory before returning. 
            for (int i = 0; i < dryingBatches.size(); i++) {
                delete dryingBatches[i].timeToDry; 
            }
            dryingBatches.clear(); 
            break;
        } 
        else {
            cout << "Invalid option. Try again!" << endl;
        }
    }

    return 0; 
}