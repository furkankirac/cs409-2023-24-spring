// lambdas capturing local variables: this includes local parameter packs as well
// storing parameter packs: an elegant storage container; get_first, get_size, get_tail impl.

#include <iostream>
#include <vector>

using namespace std;


auto list(const auto& ... items) {
    return [&items...](auto accessor) {
        return accessor(items...);
    };
};

auto get_first() {
    return [](const auto& first, auto ...) {
        return first;
    };
}

auto get_rest() {
    return [](const auto&, const auto& ... rest) {
        return list(rest...);
    };
}

auto get_last() {
    return [](const auto& ... all) { // all is a parameter pack 100|1|'a'|"abc"|3.14
        return (all, ...);
    };
}

auto foo() {
    auto a = 100;
    auto b = 1;
    auto c = 'a';
    auto d = "abc";
    auto e = 3.14;
    auto l = list(a, b, c, d, e);
    return l;
}


int main() {
    auto v = vector{1, 2, 3, 4};

    auto z = 'z';
    auto l = list(100, 1, 'a', "abc", 3.14);

    // l is a list instance returned by foo using references to objects that got destructed
    // this will cause issues without any warning
    // auto l = foo();

    auto a = l(get_first());
    cout << a << endl;

    auto l_rest = l(get_rest());
    auto b = l_rest(get_first());
    cout << b << endl;

    auto c = l(get_last());
    cout << c << endl;

    // int k = 10;
    // auto lambda = [&k](int increment) { k += increment; };
    // lambda(100);
    // cout << k << endl;

    return 0;
}
