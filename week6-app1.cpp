// perfect forwarding, about the extention done at 2011 dialect (r-value binding) &&

// Node<T> implementation with virtual functions + inheritance
// a List<T> implementation, go low-level, then implement with standard library
// move-ctor, move-assignment


#include <iostream>
#include <string>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T>
struct TypeDisplay; // forward declare, but don't give the declaration yet


// void foo(int& t) { }
// void foo(int&& t) { // what is the type of t, is it an l-value or an r-value
// }


template<typename T>
void bar(T&& k)
{
    // auto t = TypeDisplay<T>{};
}

template<typename T>
void foo(T&& whatever) { // forwarding reference or previously called universal reference (scott meyer's)
    // if T is pure (no modifiers), it's an r-value at call site
    // it T contains ref, it's an l-value at call site
    // whatever itself is an l-value
    // auto t = TypeDisplay<T>{};
    // using Tpure = std::remove_reference<T>::type;
    // bar((Tpure&&)whatever);

    bar(std::forward<T>(whatever));

    // bar(whatever);
}


int main(int argc, char* argv[])
{
    using intref = int&;
    using intrefref = int&&;

    int a = 10;

    // foo(a); // calling foo with an l-value
    foo(10); // calling foo with an l-value

    // auto t = TypeDisplay<intrefref&>{};

    // reference collapsing rules
    // & + &  --> &
    // & + && --> &
    // && + & --> &
    // && + && -> &&


    return 0;
}
