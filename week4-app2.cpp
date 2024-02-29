#include <iostream>

// function objects
// function pointers

// repeat-it algorithm
// mutability
// l-value, r-value, r-value binding reference

// move-ctor, move-assignment

using namespace std;


// typedef void (*foo_ptr)(); // C notation
using dummyfunc_ptr = void (*)(); // C++ notation

void foo() { cout << "I am a dummy function" << endl; }
void bar() { cout << "I am a dummy function too" << endl; }

using one_inter_ptr = int (*)(int);
int foo(int i) { return i+1; }
int bar(int j) { return j-1; }
int xyz(int i) { return i*2; }

using two_inter_ptr = int (*)(int, int);
int foo(int a, int b) { return a + b; };


void process(int a, one_inter_ptr p)
{
    cout << p(a) << endl;
}

void process(int a, int b, two_inter_ptr p)
{
    cout << p(a, b) << endl;
}

struct FunctionObject
{
    int a; // 10
    int b; // 25
    int operator() (int c) {
        return a + b + c;
    }
};


struct FibonacciGenerator {
    int a = 0;
    int b = 1;
    int operator()() {
        auto retval = a+b;
        a = b;
        b = retval;
        return retval;
    }
};

void process(FunctionObject fo, int k)
{
    cout << fo( k ) << endl;
}

template<typename T>
void repeat_it(T fo, int num_times)
{
    for(int i=0; i<num_times; i++)
        cout << fo() << endl;
}

int main(int argc, char* argv[])
{
    // int* a = &foo;
    // cout << a << endl; // this prints 1, why?
    foo();
    bar();

    dummyfunc_ptr p = &foo;
    p();
    p = &bar;
    p();

    process(5, &foo);
    process(5, &bar);
    process(5, &xyz);

    FunctionObject fo{10, 25}; // unified/universal ctor syntax
    // process(fo, 3);
    // process(fo, 5);
    // repeat_it<FunctionObject>(fo, 10);


    // repeat_it<FibonacciGenerator>(FibonacciGenerator{}, 10);
    repeat_it(FibonacciGenerator{}, 10);

    // int a = 0;
    // int b = 1;
    // int operator()() {
    //     auto retval = a+b;
    //     a = b;
    //     b = retval;
    //     return retval;
    // }
    repeat_it([a=0, b=1]() mutable {
        auto retval = a+b;
        a = b;
        b = retval;
        return retval;
    }, 10);


}
