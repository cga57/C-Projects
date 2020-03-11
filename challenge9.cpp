#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

int evaluate(int num1, char c1, int num2){
	cout << num1 <<" " << num2 << endl;
	int result = 0;
	switch(c1) {
	    case '*' : result = num1*num2;; // prints "1"
	             break;       // and exits the switch
	    case '/' : result = num1/num2;
	             break;
	    case '%' :result = num1 % num2;
	    		break;
	    case '+' : result = num1 + num2;
	    		break;
	    case '-' : result = num1 - num2;
	    		break;
	    default: cout << c1 << " RIP" << endl;
	}

	return result;


}
int main(){



	// we have to find how many 
	// numbers in the file evaluate to less than zero
	// the file is expr_1000.txt

	string s;
	istringstream str(s);
	// int count = 0;
	// int result = -1; // temp variable to store
	// the result of each expression
	while(getline(cin,s)){
		
		// for(int i = 0; i < s.size(); i+=5){
		// 	if(i == 0){ // only evaluates the first time
		// 		result = evaluate(s.substr(i,i+1),s[i+2],s.substr(i+2, i+4)); 
		// 		continue;
		// 	}
		// 	result = evaluate(result, s[i+1], s[i+2]);


		// }
		// if(result < 0){
		// 	count++;
		// }

	}





}