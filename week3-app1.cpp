// core language definitions:
// - l-value / r-value
// - chain assignment
// - constness: east/west const, pointers and const
// using / namespaces

// OOP:
// inheritance
// dynamic polymorphism / virtual functions vs RTTI
// move-ctor, move-assignment

// functional programming:
// - overloading
//   (all the operators are implemented as functions and they also can ve overloaded)

// Generics / Templates:
// function, class, variable, type templates

#include <iostream>
#include <string>

using namespace std;

struct string_
{
    // attributes
    string_(const string&);
    string_(const char*);
    // ...
};


int foo(string const& title) // const& situation -> can bind to both l&r-values
{
    cout << title << endl;
    cout << sizeof(title) << endl;
    return 5;
}


int main(int argc, char* argv[])
{
    // l-value ---> left value
    // r-value ---> right value

    int a = 5;
    // cout << sizeof(5) << endl; // for this arch. it's 4 bytes
    // int b = foo("Hi there"); // const char[9] ---> const char*

    // int c = 55;
    // a = b = c = 10;
    // a = b = c; // now c is 10
    // a = b; // b is now assigned whatever c is (c's content is cloned)

    auto PI = 3.14; // this is a double
    auto G = 9.8; // gravity

    double* double_ptr = &PI;

    cout << "Value is " << PI << endl;
    cout << "Address of PI is " << double_ptr << endl;
    cout << "The value in the address of PI is " << *double_ptr << endl;
    double_ptr = &G;
    cout << "Address of G is " << double_ptr << endl;
    cout << "The value in the address of G is " << *double_ptr << endl;


    return 0;
}
