// template parameter types: unknown typename, known typename with a value, auto in templates as a parameter

// variadic templates, parameter packs, pack expansions (C++11 and later)
// - write and add function that adds all its input parameters

// fold expressions (C++17 and later)
// - write and add function that adds all its input parameters with fold expressions

// fold expressions and comma operator
// - write a print(...) function that prints all its input arguments to the console

// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>

using namespace std;

template<typename T>
void foo1(T t) { cout << "foo1" << endl; }

template<typename T>
void foo2() {
    if constexpr( is_integral_v<T> ) {
        cout << "foo2 (T is integral)" << endl;
    } else {
        cout << "foo2 (T is non-integral)" << endl;
    }
}

template<typename T, T t>
void foo3()
{
    cout << "foo3 value is " << t << endl;
}

template<auto t>
void foo4()
{
    using T = decltype(t);
    cout << "foo4 value is " << t << endl;
}

int main(int argc, char* argv[])
{
    // void foo1(int t) { cout << "foo1" << endl; }
    foo1(8);

    // void foo2<float>() { cout << "foo2 (T is non-integral)" << endl; }
    foo2<float>();

    // void foo2<int>() { cout << "foo2 (T is integral)" << endl; }
    foo2<int>();

    foo3<int, 3>();

    foo4<6>();

    return 0;
}
