// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>

using namespace std;

template<bool B, typename T = void> struct enableIf { };
template<typename T>                struct enableIf<true, T> { using type = T; };

template<typename T>
concept IsIntegral = is_integral_v<T>;


//template<typename Integral, typename T = enableIf< is_integral_v<Integral> >::type >
//void printIntegralValues(Integral integral)
//{
//    cout << integral << endl;
//}

//template<typename Integral>
//enableIf< is_integral_v<Integral> >::type printIntegralValues(Integral integral)
//{
//    cout << integral << endl;
//}

template<typename Integral>
void printIntegralValues(Integral integral,
                         typename enableIf<is_integral_v<Integral>>::type* /*whatever*/ = nullptr)
// when Integral typename is really integral:
//  enableIf line turns into "void* whatever = nullptr" which is correct syntax
//  else ::type is not available, hence, skipped by the substitution failure is not an error rule of compiler
{
    cout << integral << endl;
}


void foo(int* whatever = nullptr) // you can ignore writing whatever variable name if you don't use it
{
}

int main()
{
    // SFINAE -> Substitution Failure Is Not An Error
    // invented trick to earn the concept like behavior with old compilers
    // have concepts before they are introduced in C++20

   // printIntegralValues("Hi there"); // invalid
    printIntegralValues(3); // valid
    foo();

}
