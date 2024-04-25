// std::integral_constant, std::true_type, std::false_type, tag dispatching

// constexpr functions
// std::is_constant_evaluated()

// godbolt.org
// factorial function that runs at compile time
// - with integral_constant
// - with constexpr

// decltype(auto)

#include <iostream>
// #include <string>

using namespace std;

struct LoggingMode { };
struct ReleaseMode { };

// tag dispatching
void log(auto smt, LoggingMode) { cout << "Logging: " << smt << endl; }
void log(auto smt, ReleaseMode) { cout << "Release: " << smt << endl; }

struct int_10 {
    using type = int;
    static constexpr int value = 10;
};

struct float_3_14f {
    using type = float;
    static constexpr int value = 3.14f;
};

template<auto v>
struct Constant {
    using type = decltype(v);
    static constexpr decltype(v) value = v;
};


constexpr auto foo() -> int
{
    return 10;
}

constexpr int i = 20;


int main() {

    auto v = int_10::value;
    auto v2 = Constant<10>::value;
    auto v3 = std::integral_constant<int, 10>::value;

    log("Whatever", LoggingMode{});
    log("Hi there", ReleaseMode{});

    int* p = (int*)&i;

    cout << foo() << endl;
    using T = decltype(foo());

    return 0;
}
