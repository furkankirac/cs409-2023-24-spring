// duck typing? type erasure: std::function

// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern


#include <iostream>
#include <memory>
#include <functional>

using namespace std;

struct Foo { void print() const { cout << "I am a duck" << endl; } };
struct Bar { void print() const { cout << "I am a duck" << endl; } };

// free functions
// function objects ---> lambdas
// methods

double freeFunc1(int) { return 0.0; }
double freeFunc2(int) { return 10.0; }

struct XYZ {
//    int a = 10;
    void print() const { cout << "XYZ::print" << endl; }
    void print2() const { cout << "XYZ::print2" << endl; }
};

//void print2(const XYZ&) { cout << "XYZ::print2" << endl; }

struct ABC {
    void print() const { cout << "ABC::print" << endl; }
};


int main()
{
//    auto foo = Foo{};
//    auto bar = Bar{};

    using FreeFuncPtr = double(*)(int); // a kind of type erasure
    FreeFuncPtr fptr = &freeFunc2;

    cout << (*fptr)(0) << endl;

    auto xyz = XYZ{};
    xyz.print();

    auto abc = ABC{};
    abc.print();

    using MemberFuncPtr = void(XYZ::*)() const;
    MemberFuncPtr mfptr = &XYZ::print2; // we only said a method under XYZ struct
    (xyz.*mfptr)();

    auto lambda = []() { cout << "I am a lambda" << endl; };
    lambda();

    std::function<double (int)> f1; // type erasure
    f1 = &freeFunc1;
    cout << f1(100) << endl;
    f1 = freeFunc2;
    cout << f1(100) << endl;

    std::function<void()> f2;
    f2 = lambda;
    f2();

    std::function<void(const XYZ&)> f3;
    f3 = &XYZ::print2;
    f3(xyz);

//    foo = bar; // strong typing does not allow this line. if duck-typed then it would be fine

}
