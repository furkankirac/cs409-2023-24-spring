// concepts
// requires clause
// requires expression
// --- CastableToInt

// Function objects, operator() overloads and multiple inheritance

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors
// Array<T, sz> implementation with deduction guides

// lambda equivalents and the "struct overloaded { ... }" trick

// std::variant

#include <iostream>

template<typename T>
concept CastableToInt = requires (T t) {
    // imagine T is std::string,
    // t is maybe "Hi there"s, it's not castable to int, concept returns false
    (int)t;
};


// template<CastableToInt ... Ts>
// void print_intcasts(const Ts& ... ts) { }

// template<typename First, typename ... Rest>
// requires CastableToInt<First>
// void print_intcasts(const First& f, const Rest& ... rest) { }

// template<typename First, typename ... Rest>
// void print_intcasts(const First& f, const Rest& ... rest)
// requires CastableToInt<First>
// { }

void print_intcasts(const CastableToInt auto& ... ts) {

}

int main(int argc, char* argv[])
{
    print_intcasts(5, 5.5, 5.5f); // const char[4] ---> const char *?

    return 0;
}
