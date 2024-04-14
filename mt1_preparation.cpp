#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <map>
#include <variant>

using namespace std;

template<typename ...> struct TD;

template<typename T>
struct Mat
{
    using type = T;
    size_t rows, cols;
    vector<T> data;

    Mat(size_t rows = 0, size_t cols = 0, T init = T{}) : rows{rows}, cols{cols}, data(rows*cols, init) { }

    const T* operator[](size_t r) const { return &data[r*cols]; }
    T* operator[](size_t r) { return &data[r*cols]; }
};

template<typename T>
void print(const Mat<T>& m)
{
    for(size_t i=0; i<m.rows; ++i)
    {
        auto ptr = m[i];
        for(size_t j=0; j<m.cols; ++j)
        {
            if constexpr(is_same_v<string, T>)
                cout << "\"" << ptr[j] << "\" ";
            else
                cout << ptr[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template<typename T>
concept IsMatX =
    is_same_v<
        Mat<typename remove_reference_t<T>::type>,
        remove_reference_t<T>
        >;

template<IsMatX T>
auto transform(T&& mat_src, auto func)
{
    using M = remove_reference_t<T>; // Mat<U> with reference filtered out
    using U = typename M::type; // underlying type stored in Mat
    using V = remove_cvref_t<decltype(func(U{}))>; // underlying type after the transformation
    if constexpr(is_reference_v<T>)
        cout << "Transforming l-value parameter" << endl;
    else
        cout << "Transforming r-value parameter" << endl;
    auto mat_dest = Mat<V>{mat_src.rows, mat_src.cols};
    for(size_t i=0; i<mat_src.rows; ++i)
    {
        auto src_ptr = mat_src[i];
        auto dest_ptr = mat_dest[i];
        for(size_t j=0; j<mat_src.cols; ++j)
            dest_ptr[j] = func(src_ptr[j]);
    }
    return mat_dest;
}

template<typename T>
requires(IsMatX<T>)
auto inc(T&& input)
{
    if constexpr(is_reference_v<T>)
        cout << "Incrementing l-value matrix" << endl;
    else
        cout << "Incrementing r-value matrix" << endl;
    return transform(input, [](auto&& value) { return value+1; });
}

template<typename ...>                      struct concat;
template<typename T>                        struct concat<T, void>                    { using type = T; };
template<typename ... Ts, typename ... Us>  struct concat<tuple<Ts...>, tuple<Us...>> { using type = tuple<Ts..., Us...>; };

template<typename ... Ts>
using concat_t = typename concat<Ts...>::type;

template<typename ...>  struct IsIntegral           : false_type { };
template<>              struct IsIntegral<char>     : true_type { };
template<>              struct IsIntegral<short>    : true_type { };
template<>              struct IsIntegral<int>      : true_type { };
template<>              struct IsIntegral<long>     : true_type { };

template<typename ...>
struct filter_types;

template<typename ... Ts>
using filter_types_t = typename filter_types<Ts...>::type;

template<template<typename...> typename FUNC, typename ... FuncTs>
struct filter_types<FUNC<FuncTs...>, tuple<>>
{
    using type = void;
};

template<template<typename...> typename FUNC, typename ... FuncTs, typename First, typename ... Rest>
struct filter_types<FUNC<FuncTs...>, tuple<First, Rest...>>
{
    using type =
        concat_t<
            conditional_t<FUNC<First>::value, tuple<First>, tuple<>>,
            filter_types_t<FUNC<FuncTs...>, tuple<Rest...>>
            >;
};

struct String : string { using string::string; };

template<typename ...>  struct Transformer;
template<typename T>    struct Transformer<T>       { using type = T; };
template<>              struct Transformer<char>    { using type = int; };
template<>              struct Transformer<short>   { using type = int; };
template<>              struct Transformer<long>    { using type = int; };
template<>              struct Transformer<double>  { using type = float; };
template<>              struct Transformer<string>  { using type = String; };

template<typename ...>
struct transform_types;

template<typename ... Ts>
using transform_types_t = typename transform_types<Ts...>::type;

template<template<typename...> typename FUNC>
struct transform_types<FUNC<>, tuple<>>
{
    using type = void;
};

template<template<typename...> typename FUNC, typename First, typename ... Rest>
struct transform_types<FUNC<>, tuple<First, Rest...>>
{
    using type = concat_t< tuple<typename FUNC<First>::type>, transform_types_t<FUNC<>, tuple<Rest...>> >;
};


template<template<typename...> typename FUNC, typename ... Ts>
constexpr size_t count_types(const tuple<Ts...>&)
{
    return ((int)FUNC<Ts>::value + ...);
}


int main()
{
    auto m1 = Mat(2, 3, 9.9); // 2 row, 3 column matrix with double values is initialized to 9.9 for each cell
    print(m1);

    for(size_t i=0; i<m1.rows; ++i)
        m1[i][i] = 1.1;
    print(m1);

    auto m2 = transform(
        Mat{2, 2,
            map<string, variant<string, double, int>>{
                {"pi", 3.14},
                {"CS", "409/509"},
                {"year", 2021}
            }
        }, []<typename T>(T&& map_) {
            auto s = string{};
            for(const auto& [key, value] : map_)
            {
                auto value_str = string{};
                if(holds_alternative<string>(value))
                    value_str = get<string>(value);
                else if(holds_alternative<double>(value))
                    value_str = to_string(get<double>(value));
                else if(holds_alternative<int>(value))
                    value_str = to_string(get<int>(value));
                s += key + ": " + value_str + " ";
            }
            return s;
        });
    print(m1);
    print(m2);

    print(inc(m1)); // prints l-value
    print(inc(Mat(1, 4, 1))); // prints r-value


    using TUPLE = tuple<int, float, string, char, short, double, string, double, float>;

    using TUPLE_INTEGRAL = filter_types_t<IsIntegral<>, TUPLE>;

    using TUPLE_FLOATING = filter_types_t<is_floating_point<void>, TUPLE>;

    using TUPLE_TRANSFORMED = transform_types_t<Transformer<>, TUPLE>;

    cout << "Number of integral types in TUPLE is " << count_types<IsIntegral>(TUPLE{}) << endl;
    cout << "Number of integral types in TUPLE is " << count_types<is_integral>(TUPLE{}) << endl;
    cout << "Number of floating types in TUPLE is " << count_types<is_floating_point>(TUPLE{}) << endl;

    return 0;
}
