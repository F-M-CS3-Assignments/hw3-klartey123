// Author; Kelvin Lartey

#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)
#include "TimeCode.cpp"

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


string drying_snap_shot_to_string(DryingSnapShot dss){
	// retrun my time into hh:: mm:: ss format.
	string drying_time = dss.timeToDry -> ToString();
	// this is to store the remainig time left. 
	long long int new_seconds_left= get_time_remaining(dss);
	// convert it all to the timecode here. 
	TimeCode remainingtime (0,0, new_seconds_left);
	// now compute the string. 
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


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;

	//come back to this and fix it in the timecope.cpp
	//assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	//tests());
	return 0;
}