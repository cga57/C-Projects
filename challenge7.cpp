#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(){
	
	// remember to always pass in strings as const string &str
	// read in the file
	// int extra_cap = 100;
	int arr [1000][500];
	int first = 0;
	int second = 0;
	int x = 0;
	int count = 0;
	while(cin >> x){
		arr[first][second] = x;
		count++;
		// could this if statement be causing an error??
		if(second == 499){
			first++;
			second = 0;
			continue;
		}
		second++;
		

	}

	cout << "I have read " << count << " things from file" << endl;


	vector<int> sum(500,0); // Each column will have a sum
	// this for loop should store 
	// the sum of each column of the array
	// in the vector

	for(int k = 0; k < 500; k++){
		for(int i = 0; i < 1000; i++){
			sum[k] += arr[i][k];
		}

	}

	// determine which number is the greatest
	int greatest = 0; // greatest sum
	int greatest_column = -1; // column with the greatest sum
	for(int i = 0; i < sum.size(); i++){
		if(sum[i] >= greatest){
			greatest = sum[i];
			greatest_column = (i+1);
		}

	}

	cout << "Greatest sum is at " << greatest_column;
	cout << " column" << endl;

	cout << "And the sum is: " << greatest << endl;


	return 0;
}