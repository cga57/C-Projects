#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
// program calculates the top 3 most bought items in a supermarket


using namespace std;



int main(){

	string s = "";
	int item_count = 0; // finds out the number of different items in a file
	vector <string> unique_items; // stores all unique items into a string vector
	// bool to check to see if the string is already in unique items vector
	bool in_unique = false; 

	while(cin >> s) {
		for (int i = 0; i < unique_items.size(); i++){
			if(in_unique_items[i] == s){
				in_unique == true;
		}

		if(!(in_unique){
			item_count++;
		}

	}

	return 0;
}