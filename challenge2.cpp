#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;


bool threeNines(int num){

	int count = 0;

	// a non recursive solution
	
	while (true){
		if (num < 10) {
			if (num == 9) {
				count++;
			}

		return (count == 3); // checks if count == 3, returns bool
		}

		if(num % 10 == 9){
			count++;
			
		}

		num = num/10;

	}

}
// adds up all integers from 1 to a million with exactly three nines
//(test function)
void testThreeNines(){

	assert(threeNines(999));
	assert(threeNines(929429));
	assert(threeNines(999000));
	assert(threeNines(1999));
	assert(threeNines(100999));
	

	assert(!threeNines(190999));
	assert(!threeNines(939991));


	cout << "All tests for function Three Nines passed" << endl;


}

// Note: Unsinged long long in allows the big value 
// to be returned
unsigned long long int sumThreeNines(){



	unsigned long long int sum = 0;
	// note including 1 and a million
	for (int i = 1; i <= 1000000; i++) {

		if (threeNines(i) == true) {
			sum += i; 
		}


	}

	return sum;



}

int main(){

	// check to see if the sums are passed
	testThreeNines(); // test funtion
	unsigned long long int summed = sumThreeNines();
	cout << "The sum is: " << summed << endl;






}
