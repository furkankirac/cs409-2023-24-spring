// variadic templates, parameter packs, pack expansions (C++11 and later) "modern C++"
// - write an add function that adds all its input parameters

// fold expressions (C++17 and later) "more modern C++" ---> "modern C++"
// - write an add function that adds all its input parameters with fold expressions

// fold expressions and comma operator
// - write a print(...) function that prints all its input arguments to the console

// std::pair, std::tuple, std::map
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>

using namespace std;


template<typename T1, typename T2>
auto add_v1(T1 a, T2 b) { return a + b; }

template<auto a, auto b>
auto add_v2() { return a + b; }

// Ts is called a compile-time parameter-pack
auto add_v3() { return 0; }

template<typename First, typename ... Rest>
auto add_v3(First first, Rest ... rest) {
    return first + add_v3(rest...); // pack expansion
}

template<typename First, typename ... Rest>
inline auto add_v4(First first, Rest ... rest) {
    if constexpr(sizeof...(rest) == 0) {
        return first;
    } else {
        return first + add_v4(rest...); // pack expansion
    }
}

template<typename ... Ts>
inline auto add_v5(Ts ... ts) {
    return (ts + ...);
}



int main(int argc, char* argv[])
{
    cout << add_v1(3, 5.3); // add_v1<int, double>
    cout << endl;
    cout << add_v2<3, 5.3>(); // add_v1<int, double>
    cout << endl;
    cout << add_v3(1, 1.1, 2.2f, 10);
    cout << endl;
    cout << add_v4(1, 1.1, 2.2f, 10);
    cout << endl;
    cout << add_v5(1, 1.1, 2.2f, 10);

    // for(int i=0, j=10; i<10 && j>=0; i++, j--);
    // cout << (10, 20, 30) << endl;


    return 0;
}
