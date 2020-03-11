#include <iostream>
#include <string>
#include <cassert>
using namespace std;
// find the word cat in some word read from an input file
// "cat" letters DO not have to be beside each:
// Ex: Cact is considered a word with "cat"in it

//Program written by Chirag Gupta


bool cat_finder(string word) {
	int index = 0;
	string cat  = "";
	int size = word.length();
	for(int i = 0; i < size;i++){

		if(word[i] == 'c'){
			index = i; // index takes the value of i
			cat.append("c");
			break; // leave the loop immediately
		}

	}
	// no initialization needed
	for(;index < size;index++){
		if(word[index] == 'a'){
			index = index; // code only for readability purpose
			cat.append("a");
			break;
		}
	}
	for(;index < size; index++){
		if(word[index] == 't'){
			index = index;
			cat.append("t");
			break;
		}
	}
	if(cat == "cat"){
		return true;
	}
	return false;



}

void test_cat_finder(){


	assert(cat_finder("cacht"));
	assert(cat_finder("njghkcacht"));
	assert(cat_finder("ciuhjachhgkht"));

	assert(!cat_finder("tact"));
	assert(!cat_finder("cachio"));
	assert(!cat_finder("taaaaaaacccccctttt"));

	cout << "All tests passed for function cat finder " << endl;

}

void cat_counter(){
	string s;
	unsigned int counter = 0;
	while(cin >> s){
		if(cat_finder(s)){
			counter++;
		}
	}
	cout << "Number of cats that occur in the words are " << counter; 
	cout << endl;
}


int main(){

	test_cat_finder();
	cat_counter();

	return 0;

}