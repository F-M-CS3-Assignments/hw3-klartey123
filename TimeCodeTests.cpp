
#include <iostream>
#include <assert.h>
using namespace std;


#include "TimeCode.h"
#include "TimeCode.cpp"
// Components to seconds. It converts hours, minutes and seconds all to seonds in the format such as
// 3600
void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	// Random but "safe" inputs
	// impliments t once because c++ causes an error when it is muliple 
	//declariarion which is redefinition

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

	cout << "PASSED!" << endl << endl;
}

// Make sure that if a time is empty it would be 0:0:0
void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}

// Make sure that the initizalization is right and all rollovers are handled. 
void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");


	TimeCode tc4 = TimeCode(1, 60, 60);
	assert(tc4.ToString()== "2:1:0");

	TimeCode tc5 = TimeCode(0, 59, 0);
	assert(tc5.ToString() == "0:59:0");
	cout << "PASSED!" << endl << endl;
}

// Extracting each components such as hours, minutes and seconds
void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	

	TimeCode tc2 = TimeCode(0, 0, 18);
	tc2.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 18);

	TimeCode tc3 = TimeCode(0, 0, 18);
	tc3.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 18);

	TimeCode tc4 = TimeCode(0, 0, 0);
	tc4.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);
	
	cout << "PASSED!" << endl << endl;
}
// My time testing

// Minutes testing. 
void TestSetMinutes(){
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");
// What is minutes is more than 59
	try
	{
		tc.SetMinutes(80);  
		assert(false);
	}
	catch (const invalid_argument &e)
	{}

	cout << "PASSED!" << endl << endl;
}
// Tesing my hours, will be hours change when it is a new hour is added. 
void TestSetHours(){
	cout << "Testing SetHours"<< endl;
	TimeCode tc = TimeCode(8,5,9);
	tc.SetHours(9);
	assert(tc.ToString()== "9:5:9");
}

// Tetsting seconds

void TestSetSeconds() {
    cout << "Testing SetSeconds" << endl;

    TimeCode tc(1, 15, 30);
    tc.SetSeconds(45);
    assert(tc.ToString() == "1:15:45");  

    try {
        tc.SetSeconds(60);  
        assert(false);
    } catch (const invalid_argument& e) {}

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

	//Dangerous inputs
	TimeCode tc1(0,0,0);
	tc1.reset();
	assert(tc1.ToString() == "0:0:0");

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

// My operator functions 
// adding all the new times together
void TestOperatorPlus() {
    cout << "Testing operator+" << endl;

    TimeCode t1(1, 30, 0);  
    TimeCode t2(0, 30, 0);  
    TimeCode t3 = t1 + t2;  

    assert(t3.ToString() == "2:0:0");

    cout << "PASSED!" << endl << endl;
}

//Lets subtract the times and see how it changes. 
void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	// Now lets try neagtive numbers again 
	// t4 will be 4545 which when t1 is subtraced from will be a - number. 
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

void TestOperatorMultiply() {
    cout << "Testing operator*" << endl;

    TimeCode t1(1, 30, 0);  
    TimeCode t2 = t1 * 2;  

    assert(t2.ToString() == "3:0:0");

	// testing for negative values;

	try {
        TimeCode t = t * -1;  
        assert(false);
    } catch (const invalid_argument& e) {}

    cout << "PASSED!" << endl << endl;
}

void TestOperatorDivide() {
    cout << "Testing operator/" << endl;

    TimeCode t1(2, 0, 0);  
    TimeCode t2 = t1 / 2;  

    assert(t2.ToString() == "1:0:0");

	// Negative numbers division should throw an exception. 

	try {
        TimeCode t = t/ -1;  
        assert(false);
    } catch (const invalid_argument& e) {}


	// dividing by 0 should throw an exception. 
    try {
        TimeCode t = t / 0;  
        assert(false);
    } catch (const invalid_argument& e) {}
}

void TestComparisonOperators() {

	//  tesing all the comparison operators. 
    cout << "Testing Comparison Operators" << endl;

    TimeCode t1(1, 0, 0);
    TimeCode t2(2, 0, 0);
    TimeCode t3(1, 0, 0);
	


    assert(t1 <= t2);  
    assert(t2 >= t1);  
    assert(t1 >= t3);  
	assert(t1 !=t2);
	assert(t1< t2);
	assert(t3== t1);
	assert(t2> t1);

    cout << "PASSED!" << endl << endl;
}

	
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
	TestSetSeconds();

	
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
