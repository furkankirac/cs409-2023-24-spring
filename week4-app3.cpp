#include <iostream>
#include <vector>

// r-value binding reference
// move-ctor, move-assignment
// very big object (heap allocation): legacy version, modern version

using namespace std;


void foo(int& a) { // this only binds to l-value, why?
    a++;
    cout << "l-value is " << a << endl;
}

// void foo(int a) { // this binds to l-value and r-value
//     a++;
// }

void foo(int&& a) { // this only binds to r-value
    cout << "r-value is " << a << endl;
}

void foo(const int& a) { // this binds to both l-value and r-value with ref
    cout << "const value is " << a << endl;
}


struct Bar
{
    int k;
    Bar() : k(10) { }
    Bar(const Bar& other) : k(other.k) { } // copy ctor
    // Bar(Bar&& other) : ...  // move ctor

    void operator=(const Bar& other) { k = other.k; } // copy assignment
    // void operator=(Bar&& other) ... // move assignment
};


int main(int argc, char* argv[])
{
    auto k = 10; // k is int
    foo(k); // k is l-value
    cout << k << endl;

    foo(10);
}
