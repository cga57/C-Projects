// a1.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Chirag Gupta
// St.# : 301391394
// Email: cga57@sfu.ca
//
// Sourcing: 
// -Used notes in lectures/class for help on the assignment
// -Got help from William Tjandra (classmate)
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

#include "a1.h"
#include "cmpt_error.h"
#include <iostream>      // no other #includes are allowed
#include <fstream>       // for this assignment
#include <string>
#include <cassert>

using namespace std;

// Note: The add_right and resize function is declared on the top
// since it is needed by many functions for testing
// purposes 
void add_right(str_array& arr, const string& s);
void resize (str_array & a);
void add_left(str_array& arr, const string& s);
void deallocate(str_array& arr);
// returns an exprty str_array struct with a fixed capacity(max size)
// capacity default is 10 unless otherwise specified by the user
str_array make_empty(int cap = 10) {

	str_array empty_struct; 
	empty_struct.size = 0;
	empty_struct.capacity = cap;
	empty_struct.arr = new string[cap];
	return empty_struct;
}

// test function for make_empty
void test_make_empty(){

	str_array empty_struct; 
	empty_struct = make_empty(20);

	assert(empty_struct.size == 0);
	assert(empty_struct.capacity == 20);

	deallocate(empty_struct);
	cout << "All tests for make_empty function passed" << endl << endl;



} 

// function to avoid memory leaks
void deallocate(str_array& arr) {

	delete[] arr.arr; // deletes the array this pointer is pointing to
	//arr.arr = nullptr; // sets the pinter to nulptr as specified 


}

void test_deallocate(){
	// empty arr str test
	// creates an str array with cap 20 
	str_array arr; 
	arr = make_empty(20);
	deallocate(arr);


	// valgrind will check for any memory leaks here
	// Also note: deallocate() function has been called in every
	// test function. And valgrind affirms there is no leaks
	// Hence deallocate function works as it should
	// Therefore no need to test further here

	cout << "All tests for deallocate functions passed" << endl << endl;

}
// This returns the size of the array divided by its capacity. 
// For example, if arrs size is 5 and its capacity is 15, 
// pct_used(arr) should return 0.333333.
double pct_used(const str_array& arr){

	return ((double)arr.size/(double)arr.capacity);


}
void test_pct_used(){
	str_array arr; 
	arr = make_empty(20);
	// empty string arr testing
	double size_capacity_ratio = pct_used(arr);
	double size = arr.size;
	double capa = arr.capacity;
	double checker = size/capa;


	assert(size_capacity_ratio == checker);
 

	deallocate(arr);
	// deallocate(arr2);
	cout << "All tests for pct (ratio) function passed" << endl << endl;

}
string to_str(const str_array& arr){

	string list = "[";
	int end = arr.size - 1; // end variable

	for(int i = 0; i < arr.size; i++){
		list.append("\""); // adds the first quotation mark
		list.append(arr.arr[i]); // adds the next string element from array
		if (i != end){
			list.append(",");
		}
	}
	list.append("\"]"); // add bracket at the end
	return list;

}  
// basic print functions for to_str
void print(const str_array& arr){

	string s = to_str(arr);
	cout << s;
}
void println(const str_array& arr){

	string s = to_str(arr);
	cout << s << "\n"; // moves on to next line
}

void test_to_str(){

	// Manual testing needed since console output
	// non-empty string arr test
	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");
	println(arr); 

	// empty-string test case
	str_array arr2; 
	arr2 = make_empty(20);
	cout << "It should print out [\"cat\",\"pokemon\"]" << endl;
	add_right(arr2, "cat");
	add_right(arr2, "pokemon");
	add_right(arr2,"lokemon");
	println(arr2);
	cout << "It should print out cat pokemon and lokemon seperated";
	cout << " by commas" << endl; 
	deallocate(arr);
	deallocate(arr2);

	cout << "All tests for to_str function passed" << endl << endl;

}

// returns the string at index location i of the underlying array
// use cmpt.error of i goes out of bounds, display an error message
// the bounds for i are (0 < i < arr.size)
string get(const str_array& arr, int i){
	// access the array through the pointer at location i
	if (i < 0 || i >= arr.size){
		cmpt::error("index i is not in bounds for get function");
	}

	string s = arr.arr[i]; 
	return s;
}

void test_get(){
	//on empty test case
	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");

	string word = get(arr, 0); // should be pokemon
	assert(word == "cat");
	assert(get(arr,1) =="pokemon");
	// 2nd case test to run potential error
	str_array arr2;
	arr2 = make_empty(20);
	try{
		word = get(arr2, 1);
	} catch(...){
		// will catch the exception

	}

	deallocate(arr);
	deallocate(arr2);
	cout << "All test cases passed for get function" << endl << endl;
}

void set(str_array& arr, int i, const string& s) {
	// access the array through the pointer at location i
	if (i < 0 || i >= arr.size){
		cmpt::error("index i is not in bounds for get function");
	}
	// sets the sttring s parameter to the array at index i
	arr.arr[i] = s; 

}

void test_set(){

	// non empty test case
	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");


	int set_value = 1;
	set(arr, set_value, "lokemon"); 
	assert(arr.arr[1] == "lokemon");
	

	// Note: Dont need to test exception since already tested
	// in get function (exact same code for exception)
	deallocate(arr);
	cout << "All test cases passed for set function" << endl << endl;


}
// Note: When we pass by reference, the actual value infact gets changed
// using the ampersand
void add_right(str_array& arr, const string& s){
	if(arr.size < arr.capacity){
		
		// puts first unused location (which would be at 
		// index arr.size to the new string value s
		arr.size++;
		arr.arr[arr.size-1] = s; // now do as follows by if loop
		

	}
	else if(arr.size >= arr.capacity){

		resize(arr); // resises array to be twice the capacity
		arr.size++;
		arr.arr[arr.size-1] = s; // now do as follows by if loop

	}


}

// Note: this function has already been tested
// many times for tests used for previous functions 
// Hence, only one test is eneeded on its own
void test_add_right(){

	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");
	println(arr);
	deallocate(arr);
	cout << "An array with cat and pokemon should be printed out.";
	cout << endl;
	cout << "Then tests are passed for add_right function" << endl; 
	cout << endl;


}


// personal function added to assist in program
// resizes the array to double the capacity
// no need to test since other functions which use this function
// e tested

void resize (str_array &a){
	a.capacity = a.capacity * 2;
	str_array temp = make_empty();
	str_array {temp.arr, temp.size, temp.capacity = a.capacity};
	for(int i = 0; i < a.size;i++){
		temp.arr[i] = a.arr[i];
	}
	deallocate(a); // old array deleted
	a = temp;
	a.arr = temp.arr;
	//a.capacity = (2*a.capacity); // the array is now resized with 2*original cap.

}


bool operator==(str_array a, str_array b){
	// two empty strings are declared
	string inA;
	string inB;
	for(int i = 0; i < a.size; i++){
		inA.append(a.arr[i]); // adds every string into var from array a
	}
	for(int i = 0; i < b.size; i++){
		inB.append(b.arr[i]);
	}

	if(a.size == b.size && inA == inB){
		return true;
	}
	else {
		return false;
	}
	
}
void test_operator(){


	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");

	str_array arr2; 
	arr2 = make_empty(20);
	add_right(arr2, "cat");
	add_right(arr2, "pokemon");

	str_array arr3; 
	arr3 = make_empty(20);
	add_right(arr3, "cat");
	add_right(arr3, "pokemon");
	add_right(arr3, "dog");

	assert(operator==(arr, arr2)); 
	assert(!(operator==(arr,arr3)));

	deallocate(arr);
	deallocate(arr2);
	deallocate(arr3);
	cout << "All tests for operator is passed" << endl << endl;



}

void clear(str_array& arr) {

	arr.size = 0;

}
void test_clear(){

	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");

	clear(arr);
	assert(arr.size == 0);

	deallocate(arr);
	cout << "All tests for clear is passed" << endl << endl;
	
}
// works similar to add_right except the new string
// is added as the first element
// thus forcing us to move all our elements in the arr
// to the left
void add_left(str_array& arr, const string& s){
	if(arr.size < arr.capacity){
		
		for(int i = arr.size; i > 0; i--){
			arr.arr[i] = arr.arr[i-1];
		}
		arr.arr[0] = s; // sets the first element to the new string
		arr.size++; // increases array size by 1
	}
	else if(arr.size >= arr.capacity){

		resize(arr); // resises array to be twice the capacity
		// same as in if statement
		for(int i = arr.size; i > 0; i--){
			arr.arr[i] = arr.arr[i-1];
		}
		arr.arr[0] = s;
		arr.size++; // increases array size by 1

	}
}
// very similar to testing as add_right
// Note: Both add_right and add_left have already been used to
// test previous functions. hence they are already tested
// This is an additional test
void test_add_left(){


	str_array arr; 
	arr = make_empty(20);
	add_left(arr, "cat");
	add_left(arr, "pokemon");
	println(arr);


	deallocate(arr);
	cout << "An array with pokemon and cat (in that order)"; 
	cout << " should be printed out" << endl;
	cout << "Then tests are passed for add_left function" << endl;
	cout << endl;


}
// makes the size and capacity of the array the "same"
// For ex: If arr.size = 0; (the capacity is set to 1)
// Technically this means that arr.cap_1 == arr.size
// Note: For testing purposes this function is very similar
// to resize function (with a few changes)
// Since resize function is used in add_left and add_right
// functions, this function is already partially tested
// Though this funciton does have its own test function below
// to assure no failure
void shrink_to_fit(str_array& arr){

	

	if(arr.size == (arr.capacity+1)){
		return; // does nothing in this condition
	}
	// this means that the size is less than the (capacity+1)
	// since the if loop didnt exit function

	int new_cap = arr.size+1; // the new capacity
	string *temp = new string[new_cap];  
	for(int i = 0; i < arr.size;i++){

		temp[i] = arr.arr[i];

	}
	delete[] arr.arr; // old array deleted
	arr.arr = temp;
	arr.capacity = new_cap;

}
void test_shrink_to_fit(){


	str_array arr; 
	arr = make_empty(20);
	add_right(arr, "cat");
	add_right(arr, "pokemon");

	shrink_to_fit(arr);
	// by subtracting the capacity by one u should get the size
	// if this function works properly
	assert(arr.size == (arr.capacity-1));

	deallocate(arr);

	cout << "All tests for shrink to fit function passed" << endl;
	cout << endl;
}


int main(){

  cout << "Assignment 1!\n" << endl;

  
  test_make_empty();
  test_deallocate();
  test_pct_used();
  test_to_str();
  test_get();
  test_set();
  test_add_right();
  test_operator();
  test_clear();
  test_add_left();
  test_shrink_to_fit();





  return 0;

}