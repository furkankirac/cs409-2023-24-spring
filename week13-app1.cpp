// decltype(auto)

// get_int_byval(), get_int_byref()
// function object that calls the callable when called :)

// Tuple struct implementations

// lambdas capturing local variables: this includes local parameter packs as well
// storing parameter packs: an elegant storage container; get_first, get_size, get_tail impl.

// std::function<...> // type erasure


#include <iostream>

using namespace std;

auto get_int_byval() -> int  { int i = 5; return i; }
auto get_int_byref() -> int& { static int i = 5; return i; }

template<typename Callable>
struct FuncObj {
    void operator() (Callable callable) {
        callable();
    }
};

template<typename...>
struct Debug;

int main() {

    auto value1 = get_int_byval(); // value1 -> int
    auto value2 = get_int_byref(); // value2 -> int

    decltype(auto) value3 = get_int_byval();
    decltype(auto) value4 = get_int_byref();

    // auto func1 = FuncObj< ... >{};
    // decltype(auto) retval = func1();



    // auto t = Debug<decltype(value4)>{};


    return 0;
}
