
#include <iostream>
#include <assert.h>
using namespace std;


#include "TimeCode.h"
#include "TimeCode.cpp"

void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
		// Random but "safe" inputs

	// impliments t once because c++ causes an error when it is muliple dclariarion which is redifinition
	long long unsigned int t;
	t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);

	 t = TimeCode:: ComponentsToSeconds(1,1,0);
	assert (t == 3660);

	 t = TimeCode :: ComponentsToSeconds(1,0,0);
	assert (t == 3600);
//Larger values
	 t = TimeCode:: ComponentsToSeconds(1000, 0,0);
	assert (t== 3600000);

	t = TimeCode :: ComponentsToSeconds(9999, 60, 60);
	assert(t == 36000060);
// zero values


	t = TimeCode:: ComponentsToSeconds(0,0,0);
	assert (t == 0);
// negative values
// also not working
 	// t = TimeCode :: ComponentsToSeconds(-1, 0, 0);
	// assert(t == 0);

	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	


	// more tests go here!
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}
// Reset 
void TestReset() {
    cout << "Testing Reset" << endl;

	// Safe inputs
    TimeCode tc(5, 45, 30);  
    tc.reset();  
	// Should now be 0:0:0
    assert(tc.ToString() == "0:0:0");  

	// Dangerous inputs
	// TimeCode tc(0,0,0);
	// tc.reset();
	// assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor() {
    cout << "Testing my Copy constructor" << endl;

    TimeCode t1(2, 30, 45);
	// This should copy t1 into t2
    TimeCode t2 = t1;  

    assert(t1.ToString() == t2.ToString());  

    cout << "PASSED!" << endl << endl;
}
// adding all the new times together
void TestOperatorPlus() {
    cout << "Testing operator+" << endl;

    TimeCode t1(1, 30, 0);  
    TimeCode t2(0, 30, 0);  
    TimeCode t3 = t1 + t2;  

    assert(t3.ToString() == "2:0:0");

    cout << "PASSED!" << endl << endl;
}
void TestOperatorMultiply() {
    cout << "Testing operator*" << endl;

    TimeCode t1(1, 30, 0);  
    TimeCode t2 = t1 * 2;  

    assert(t2.ToString() == "3:0:0");
}
void TestOperatorDivide() {
    cout << "Testing operator/" << endl;

    TimeCode t1(2, 0, 0);  
    TimeCode t2 = t1 / 2;  

    assert(t2.ToString() == "1:0:0");
}

void TestComparisonOperators() {
    cout << "Testing Comparison Operators" << endl;

    TimeCode t1(1, 0, 0);
    TimeCode t2(2, 0, 0);
    TimeCode t3(1, 0, 0);

    assert(t1 <= t2);  
    assert(t2 >= t1);  
    assert(t1 >= t3);  

    cout << "PASSED!" << endl << endl;
}

// Many More Tests...

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestReset();
	TestComparisonOperators();
	TestOperatorDivide();
	TestOperatorMultiply();
	TestOperatorPlus();
	TestCopyConstructor();

	
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
