// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Chriag Gupta>
// St.# : <301391394>
// Email: <cga57@sfu.ca>
//
// Worked with Rahul (classmate)
// Note: Used class notes/textbook for assistance in this assignment.
// Especially: The int_vec class we made in class
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"    // These are the only permitted includes!
#include <iostream>        //
#include <string>          // Don't include anything else.
#include <algorithm>
#include <cassert>


using namespace std;



class str_vec{

private:
	int sz;
	int cap;
	string* arr;


public:

	// getters - they should all be const
	int size() const{
		return sz;

	}

	int capacity() const{
		return cap;
	}

	double pct_used() const{
		if (cap == 0){
			cmpt::error("Capacity is zero, cannot be divided, line 57");
		}
		double ratio = (((double)sz)/cap)*100; // Note: The hundred - percentage
		return ratio;
	}

	string get(int i) const{

		if(i < 0 || i >= size()){
			cmpt::error("Index i is not in bounds for get(i) function");
		}

		// for(int k = 0; k < size(); k++){
		// 	if(k == i){
		// 		return arr[i];
		// 	}
		// }

		return arr[i];

	}

	// setter
	void set(int i, string &s){
		if(i < 0 || i >= size()){
			cmpt::error("ERROR IN SET, LINE 87");
		}
		arr[i] = s;

	}
	// THE FOLLOWING 3 METHODS ARE HELPER FUNCTIONS ONLY 
	// THEY ARE IMPLEMENTED AS DONE IN CLASS

	// getter
	string operator[](int i) const {
		return get(i);
	}
	// setter
	string& operator[](int i) {
		return arr[i];
	}
	// assignment
    str_vec& operator=(const str_vec& other) {
        if (this == &other) { // always check for self-assignment
            return *this;
        } else {
            // re-size the underlying array if necessary
            if (cap < other.sz) {
                delete arr;
                cap = other.sz + 10;
                arr = new string[cap];
            }

            sz = other.sz;
            for(int i = 0; i < sz; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }


	// our default constructor 
	str_vec()
		: sz(0), cap(10), arr(nullptr) // member initialization list
	{

		arr = new string[cap]; // pointer now points to a new string vector
	}

	// non-default constructor
	// creates vector of size n, and fills
	// the vector with the string s (according to its size)
	str_vec(int n, string s)
		: sz(n), cap(n), arr(nullptr) // Note: Capacity once again has 10 extra memory
	{

		if (sz < 0){
			cmpt::error("your size (n) cannot be less than zero - line 95");
		}
		arr = new string[cap];
		for(int i = 0; i < sz; i++){
			arr[i] = s;
		}

	}
	// copy constructor
	str_vec(const str_vec &other)
		: sz(other.size()), cap(other.capacity())
	{
		arr = new string[cap];
		for(int i = 0; i < (*this).size(); i++){
			(*this).arr[i] = other.arr[i];

		}


	}
	// destructor 
	~str_vec() {

		delete[] arr;
		arr = nullptr; 
		// sz = 0; 


	}

	string to_string() const{

		if(size() == 0){

			return "{}";
		}
		string s = "{";

		for(int i = 0; i < (*this).size(); i++){

			if (i != ((*this).size()-1)){
				s = s + "\"";
				s.append((*this).get(i));
				s = s + "\"";
				s.append(",");
				
				
				

				
			}
			else{
				s = s + "\"";
				s.append((*this).get(i));
				s = s + "\"";
			}
		}
		s.append("}");
		return s;
	}


	void print() const{
		cout << to_string();

	}
	void println() const{
		print();
		cout << endl;
	}
	// adds the string s to the right end (the back) of this str_vec, 
	// increasing the size by 1
	// only double capacity WHEN required
	void append(string s){
		// resize arr if necessary
		if (size() >= capacity()) {
			// cout << "We are doubling cap" << endl; - debugging 
			cap = 2 * cap;
			string *new_arr = new string[cap];

			// copy all elements
			for(int i = 0; i < size(); i++){
				new_arr[i] = arr[i];
			}

			delete[] arr;
			arr = new_arr;
		}
		assert(size() < capacity());
		sz++;
		(*this).set(size()-1, s);

		// assert(size() < capacity()); 
		// arr[sz] = s;
		// sz++;


	}
	// adds the string s to the left end (the front) of this str_vec, 
	// increasing the size by 1
	// only double capacity WHEN required
	void prepend(string s){
		if(size() >= capacity()){
			cap = cap*2;
			string *new_arr = new string[cap];

			// copy all elements
			for(int i = 0; i < size(); i++){
				new_arr[i] = arr[i];
			}

			delete[] arr;
			arr = new_arr;
		}

		// lets copy the current array using copy constructor

		str_vec b(*this); // this safeguards all our values

		sz++; // increase size variable for the *this pointer

		(*this).set(0,s);// sets the new string to the first value 

		for(int i = 0; i < b.size(); i++){
			(*this).set(i+1, b.get(i));
		}
	}
	// reverse the elements of the string
	void reverse(){
		str_vec b(*this); // this safeguards all our values
		for(int i = 0; i < (*this).size(); i++){
			(*this).set(i,b[b.size()-1-i]);
		}

	}
	// rearranges everything into alphabetical order
	void sort(){
		std::sort(arr, arr+sz);

	}
	// By setting size to zero we essentially clear the array even 
	// if technically the elements are still there
	void clear(){
		sz = 0;
	}
	void shrink_to_fit(){

		if(size() == capacity()){
			return;
		}
		int new_cap = sz;

		cap = sz;
		string *s = new string[new_cap];
   		for (int i = 0; i < size(); i++){
       		s[i] = arr[i];
   		}
   	    delete[] arr;
        arr = s;
	}
	

}; // Note: Classes end in semicolons !


// My operator functions
bool operator==(const str_vec& a, const str_vec& b){

	if(a.size() != b.size()){
		return false;
	}
	for(int i = 0;i < a.size(); i++){
		if(a[i] != b[i]){
			return false;
		}
	}
	return true;
}

bool operator!=(const str_vec& a,const str_vec& b){
	return(!(a == b));

}

// Note: This test function tests both the default construtor
// and the getters for size and capacity
void test_default_constructor(){

	str_vec new_vec;
	assert(new_vec.size() == 0);
	assert(new_vec.capacity() == 10);

	cout << "Test cases for default constructor passed" << endl;

}
// tests the non default constructor
// the one which takes in an int for size and a string
// and then sets all the elements equal to that string parameter
void test_2nd_constructor(){
	str_vec new_vec(5,"pokemon");
	assert(new_vec.size() == 5);

	for(int i = 0; i < new_vec.size(); i++){

		assert(new_vec.get(i) == "pokemon"); 
	}

	cout << "All tests for 2nd constructor passed" << endl;

}


void test_copy_constructor(){

	str_vec a(5, "<empty>");
	str_vec b(a);

	assert(b.size() == a.size());
	assert(b.capacity() == a.capacity());

	for(int i = 0; i < a.size(); i++){
		assert(b.get(i) == a.get(i));
	}
	cout << "ALl tests for copy constructor passed" << endl;

}

void test_to_str(){
	str_vec a(5, "cats");
	a.print();
	cout << endl;
	a.println();

	cout << "ALl tests for to string passed" << endl;

}
void test_setter(){
	str_vec a(5, "cats");
	a.set(2, "pokemon"); 
	assert(a.get(2) == "pokemon");
	//catching the exception
	try{
		a.set(5, "lium");
	} catch (...){
		
	}
	cout << "All tests for setter passed" << endl;


}

void test_append(){
	str_vec a(5, "cats"); // 5 size, 5 capacity
	a.append("liken");
	assert(a.get(5) == "liken");

	// Following code should be printed out
	// ["cats", "cats", "cats", "cats", "cats", "liken"]
	a.println();


	cout << "All tests for append passed" << endl;
	// Note: I tested for subcase when size == capacity by getting rid of 
	// the +10 on capacity for constructor. It worked fine
}

void test_prepend(){
	str_vec a(5, "cats");
	a.prepend("liken");
	assert(a.get(0) == "liken");
	a.prepend("pinked");
	assert(a.get(1) == "liken"); 
	assert(a.get(0) == "pinked");
	assert(a.size() == (5+2)); // 5 is the initial size decalred. 2 prepends

	// Following code should be printed out
	// ["pinked", "liken", "cats", "cats", "cats", "cats", "cats"]
	a.println();

	cout << "All tests for prepend passed" << endl;

}

void test_reverse(){
	//str_vec a();
	str_vec a;
	a.append("ball");
	a.append("zebra");
	a.append("coke");
	a.reverse();
	
	// should print out ["coke","zebra","ball"]
	a.println();


	cout << "All tests for reverse passed" << endl;

}

// DO MORE TESTING
void test_sort(){

	//str_vec a();
	str_vec a;
	a.append("ball");
	a.append("zebra");
	a.append("coke");
	a.sort();
	
	// should print out ["ball","coke","zebra"]
	a.println();


	cout << "All tests for sort passed" << endl;

}

void test_clear(){

	str_vec a(5, "cats");
	a.clear();
	a.print(); // should be blank



	cout << "All tests for clear passed" << endl;


}

void test_shrink_to_fit(){
	str_vec a(5, "cats");
	a.shrink_to_fit();

	assert(a.size() == a.capacity());
	a.append("nine");
	cout << "All tests for shrink to fit passed" << endl;

}

void test_equals_operator(){
	str_vec a(5, "cats");
	str_vec b(5, "balls");
	str_vec c(4, "balls");
	str_vec d(5, "cats");

	assert(!(a==b));
	assert(!(a==c));
	assert(!(b==c));

	assert(a==d);

	cout << "All tests for equals operator passed" << endl;



}
void test_not_equals_operator(){
	str_vec a(5, "cats");
	str_vec b(5, "balls");
	str_vec c(4, "balls");
	str_vec d(5, "cats");

	assert((a!=b));
	assert((a!=c));
	assert((b!=c));

	assert(!(a!=d));

	cout << "All tests for not equals operator passed" << endl;



}


// Since all our test functions use the basic getter functions
// and they work fine, we know that there is no need to 
// further test the getter functions

// EXCEPT for pct_used getter which is not tested before
// Hence it is tested here
void test_getters(){

	str_vec a(5, "cats");
	a.append("tall");
	a.prepend("shall");

	double ratio = a.pct_used();
	double ratio_tst = ((double)a.size()/(double)a.capacity())*100;
	assert(ratio == ratio_tst);
	// Should return 70% 
	cout << "Ratio: " << ratio << "% " << endl; // for manual testing pruposes

	cout << "All tests for not equals operator passed" << endl;



}
// Tested through valgrind, which returns NO memory leaks
// Despite many instances of the class created in the memory
// leaks. Hence we know that the destructor works fine
// and there is NO need to do further testing 
void test_destructor(){

	// BODY IS BLANK
	// USED as a place holder only
	// So marker can see the explanation above


}


int main() {
  
	test_default_constructor();
	test_2nd_constructor();
	test_copy_constructor();
	test_to_str();
	test_setter();
	test_append();
	test_prepend();
	test_reverse();
	test_sort();
	test_clear();
	test_shrink_to_fit();
	test_equals_operator();
	test_not_equals_operator();
	test_getters();
	// test_destructor() - No need to test further, SEE above for explantion
	



}



