// godbolt.org website
// factorial: consexpr function, meta programming version, meta programming with integral constant

#include <type_traits>

constexpr int factorial(int n) {
    if (std::is_constant_evaluated())
        return -1;

    if(n==0) return 1;
    return n * factorial(n-1);
}

template<int N>
struct Factorial : std::integral_constant<int, N * Factorial<N-1>::value> {
    // static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};


int main()
{
    constexpr int a = factorial(5);
    return a;
    // return Factorial<5>::value;
}
