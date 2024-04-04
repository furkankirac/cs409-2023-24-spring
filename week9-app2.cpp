// Array<T, sz> implementation with deduction guides


// Function objects, operator() overloads and multiple inheritance

// deduction guides:
// - used for helping the compiler deduce Class Template parameters automatically from
//   class constructors

// lambda equivalents and the "struct overloaded { ... }" trick

// std::variant

#include <iostream>
// #include <array>

using namespace std;


template<typename T, size_t sz>
struct Array
{
    T data[sz];

    Array(std::initializer_list<T> values) {
        const auto s = values.size();
        auto* ptr = values.begin();
        for(auto i=0; i<s; i++)
            data[i] = *ptr;
    }
};

template<typename T>
Array(std::initializer_list<T> values) -> Array<T, 3>;

Array(const char*) -> Array<std::string, 1>;

int main(int argc, char* argv[])
{
    int a[] = {1, 2, 3};

    // array<int, 3> A{1, 2, 3};
    // auto A = array<int, 3>{1, 2, 3};

    auto A = Array<int, 3>{1, 2, 3};
    auto A2 = Array{1, 2, 3};
    auto A3 = Array{"Hi there"};

    return 0;
}
