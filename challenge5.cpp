#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Used the help of stackoverflow to find the algorithm (mathematically)
// to calculate number of ways for some numbers to add up to a sum n
// And write nCr function
// Link: https://stackoverflow.com/questions/4588429/number-of-ways-to-add-up-to-a-sum-s-with-n-numbers


// program to answer the challenge question
long long unsigned int fact(int n){
	//cout << "n value: " << n << endl;
	long long unsigned int sum = 1;
	// cout << "sum: " << sum << endl;
	for(int i = 1; i <= n; i++){

		sum*= i;
	}
	//cout << "sum after calc:" << sum <<  endl;
	return sum;


}
int main(){


	// magic sum variables
	// Note: These are the numbers we must arrange:
	// 16, 37, 1, 3, 18, 33, 35, -1, and 20

	// since by defenition of a magic sum - you can
	// make sure that all rows/columns and diognals must be the same

	// Thus 3 rows will have the value of 3M (Where the M is the value 
	// of the sum of three numbers (aka the magic number))
	// The sum of all 3 rows MUST be equal to the sum all of the numbers
	// used in the magic square

	int list[] = {16, 37, 1, 3, 18, 33, 35, -1, 20};
	const int SIZE = 9; // number of elements in the array
	int sum = 0;

	for (int i = 0; i < SIZE; i++){
		sum += list[i];

	}
	

	int magic_sum = sum/3;
	cout << "This is the magic sum: " << magic_sum << endl;
	// Now we must choose all the ways the the numbers from the 
	// list of numbers allowed can be picked


	// If you want to find the number of ways to get N as the sum of R elements. 
	// U can use this formula:
	// (N+R-1) C (R-1) - Note: Found on stackoverflow

	long long unsigned int part1 = fact(magic_sum+SIZE-1);


	long long unsigned int part2 = fact(SIZE-1) * fact(magic_sum);

	
	long long int total = (part1/part2) + 8;

	//float total = (float)(fact(magic_sum+SIZE-1))/(float)(fact(SIZE-1)*(float)fact(magic_sum));
	
	cout << "ANSWER: Number of ways is" << total << endl;




}