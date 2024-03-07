// l-value, r-value bindings:
// function parameter       call site argument
//  l-value             to  l_value             - works (clones the value)
//  l-value             to  r_value             - works (clones the value)
//  l-value ref         to  l_value             - works
//  l-value ref         to  r_value             - does not work
//  const l-value ref   to  l_value             - works
//  const l-value ref   to  r_value             - works
//  const r-value ref                           - does not make sense most of the time

// TypeDisplay trick
// reference collapsing
// std::remove_reference<T>::type

// Write a Value<T> class that uses heap memory for storage! with all ctors and dtors
// initializer_list<T>
// move-ctor, move-assignment

// a Stack<T> implementation

#include <iostream>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

// template<typename T> struct RemoveRef { using type = T; };
// template<typename K> struct RemoveRef<K&> { using type = K; };
// template<typename K> struct RemoveRef<K&&> { using type = K; };

// forward declaration
template<typename T>
struct TypeDisplay;

using int_ref = int&;
using int_ref_ref = int&&;

void func(int_ref i) {

}

int main(int argc, char* argv[])
{
    auto i = 5;
    func(i);

    // auto t1 = TypeDisplay<int_ref&>{};      // &
    // auto t2 = TypeDisplay<int_ref&&>{};     // &
    // auto t3 = TypeDisplay<int_ref_ref&>{};  // &
    // auto t4 = TypeDisplay<int_ref_ref>{}; // &&

    // using K = std::remove_reference<int&&>::type;
    // auto k = TypeDisplay<K>{};

    return 0;
}
