// std::pair, std::tuple, std::map, structured binding
// std::tuple_element_t, std::get

// nth_type getter by variadic templates: nth_type<index, ...>
// nth_tuple_type getter: nth_tuple_type<index, tuple>

// static_assert(CompileTimeBooleanPredicate, error)

#include <iostream>
#include <string>
#include <map>

using namespace std;

template<typename First, typename Second>
struct Pair
{
    First first;
    Second second;

    // template<typename First, typename Second>
    // consexpr Pair(First&& first, Second&& second) : first{forward<First>(first)}, second{forward<Second>(second)}
    // { }
};

// template<typename First, typename ... Rest>
// struct Tuple
// {
//     First first;
        // ...
// };


// template<typename K, typename V>
void print(const map<auto, auto>& m) {
    // for(auto it = m.begin(); it != m.end(); it++) {
    //     const auto& item = *it;

    // }

    // for(const auto& item : m) {
    //     const auto& key = item.first;
    //     const auto& value = item.second;
    //     cout << "Key is " << key << "  Value is " << value << endl;
    // }

    for(const auto& [key, value] : m) { // structured binding
        cout << "Key is " << key << "  Value is " << value << endl;
    }
}


template<typename ... Ts>
void print(const std::tuple<Ts...>& t) {
    const auto size = sizeof...(Ts);
    cout << "tuple has " << size << " dimensions." << endl;

    ((cout << std::get<Ts>(t) << endl), ...);
    // (..., (cout << std::get<Ts>(t) << endl));
    // (cout << std::get<int>(t) << endl), (cout << std::get<float>(t) << endl), (cout << std::get<string>(t) << endl);


    // for(auto i=0; i<size; i++) {
    //     cout << std::get<i>(t) << endl;
    // }
}

int main(int argc, char* argv[])
{
    auto p = Pair{1, 1.1};

    auto m = std::map<int, string>{
        {1, "one"}, // "one" --> type? const char[4] --> const char *
        {2, "two"}
    };

    print(m);

    auto t = std::tuple<int, float, string>{5, 3.14f, "hi there"};
    print(t);


    return 0;
}
