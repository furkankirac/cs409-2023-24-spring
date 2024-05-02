// tuple and its implementation #2

#include <iostream>
#include <tuple>

using namespace std;

template<typename First, typename ... Rest>
struct Tuple : Tuple<Rest...> {
    static constexpr auto n_elements = sizeof...(Rest) + 1;

    First value;

    template<size_t wanted_index, size_t current_index = n_elements-1>
    auto get() const
    {
        if constexpr(current_index == wanted_index)
            return value;
        else
            return Tuple<Rest...>::template get<wanted_index, current_index-1>();
    }
};


template<typename Single>
struct Tuple<Single> {
    static constexpr auto n_elements = 1;

    Single value;

    template<size_t wanted_index, size_t current_index = n_elements-1>
    auto get() const
    {
        return value;
    }
};


template<size_t index, typename ... Ts>
auto get(const Tuple<Ts...>& t)
{
    return t.template get<index>();
}


struct Foo {
    int a1;
    int a2;
    string a3;
    float a4;
    int a5;

    Foo(int a1, int a2, string a3, float a4, int a5) : a1{a1}, a2{a2}, a3{a3}, a4{a4}, a5{a5} { }
};

int main()
{
    auto t = Tuple<int, float, double>{2.2, 1.1f, 1};

    cout << t.get<0>() << endl;
    cout << get<0>(t) << endl;

    return 0;
}
