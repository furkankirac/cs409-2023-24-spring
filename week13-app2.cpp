// tuple implementation

#include <iostream>
#include <variant>

using namespace std;

template<typename First, typename ... Rest>
struct Tuple {
    First value;
    Tuple<Rest...> rest;

    template<size_t target_idx, size_t current_idx = 0>
    auto get() const {
        if constexpr(target_idx == current_idx) {
            return value;
        } else {
            return rest.template get<target_idx, current_idx+1>();
        }
    }

    template<typename target_type>
    auto get() const {
        if constexpr(std::is_same_v<target_type, First>) {
            return value;
        } else {
            return rest.template get<target_type>();
        }
    }
};

template<typename T>
struct Tuple<T> {
    T value;

    template<size_t target_idx, size_t current_idx>
    auto get() const {
        static_assert(target_idx == current_idx, "Index Error");
        return value;
    }

    template<typename target_type>
    auto get() const {
        static_assert(std::is_same_v<target_type, T>, "Type Error");
        return value;
    }
};


template<size_t target_idx, typename ... Ts>
auto get(const Tuple<Ts...>& t) {
    return t.template get<target_idx>();
}

template<typename target_type, typename ... Ts>
auto get(const Tuple<Ts...>& t) {
    return t.template get<target_type>();
}


int main()
{
    auto t = Tuple<int, float, double>{2, 1.1f, 3.14};

    // cout << t.get<3>() << endl;
    cout << get<0>(t) << endl;
    cout << get<double>(t) << endl;
    // cout << t.get<double>() << endl;

    return 0;
}


// struct X {
//     int i; // assigned 2
//     float f; // assigned 1.1f
//     double d; // assigned 1, became 1.0

//     template<size_t idx>
//     auto get() const {
//         if constexpr(idx == 0) {
//             return i;
//         } else if constexpr(idx == 1) {
//             return f;
//         } else if constexpr(idx == 2) {
//             return d;
//         }
//     }

//     // auto get(size_t index) const -> std::variant<int, float, double> {
//     //     switch(index) {
//     //     case 0: return i;
//     //     case 1: return f;
//     //     case 2: return d;
//     //     default: return 0;
//     //     }
//     // }
// };
