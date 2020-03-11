#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int main(){

	// this initializes a vector with all the words in it
	string s;
	vector<string> list;
	while(cin >> s){

		list.push_back(s);
	}

	// sorts the vector alphabetically
	sort(list.begin(),list.end());


	string repeated_word;
	// checks to see what the repeated word is
	// note: starts from i = 1(instead of zero)
	// Since we are checking based on list[i] and
	// list[i-1] (This avoids an out of bounds index)
	// error
	for(int i = 1; i < list.size(); i++){
		if(list[i] == list[i-1]){
			repeated_word = list[i];
			break;
		}

	}
	int count = 0;
	for(int i = 0; i < list.size(); i++){
		if(repeated_word == list[i]){
			count++;
		}

	}

	cout << "The repeated word is: " << repeated_word << endl;
	cout << "It occurs " << count << " times" << endl; 





}