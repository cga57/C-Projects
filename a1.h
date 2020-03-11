// a1.h

//
// Don't modify this file in any way!!
//

#include <string>

using namespace std;

struct str_array {
    string* arr;    // pointer to the underlying array
    int size;       // # of elements from user's perspective
    int capacity;   // length of underlying array
};