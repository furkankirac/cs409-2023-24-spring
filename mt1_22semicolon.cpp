#include <iostream>
#include <tuple>
#include <list>
#include <string>
#include <variant>

template<typename ... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

auto value_type_pair = overloaded{
                                  [](int i) { return std::pair{std::to_string(i), std::string("(int)")}; },
                                  [](float f) { return std::pair{std::to_string(f), std::string("(float)")}; },
                                  [](double d) { return std::pair{std::to_string(d), std::string("(double)")}; },
                                  [](const std::string& s) { return std::pair{s, std::string("(string)")}; },
                                  };

struct Base {
    virtual std::string as_string() const { };
};

struct List : std::list<Base*> {
    List(auto* ... nodes) : std::list<Base*>{nodes...} { }
    ~List() {
        for(auto ptr : *this)
            delete ptr;
    }
    void print() const {
        auto idx = 0;
        for(const auto& item : *this) {
            std::cout << (idx == 0 ? "Contents of List\n" : "") << ++idx << ": " << item->as_string();
        }
    }
};

template<typename ... Ts>
struct Tuple : Base {
    std::tuple<Ts...> data;

    Tuple(const Ts& ... ts) : data{std::tuple<Ts...>(ts...)} { }
    std::string as_string() const override {
        return std::string("Tuple Node:   ")
               + ((value_type_pair(get<Ts>(data)).first + value_type_pair(Ts{}).second + " ") + ...)
               + "\n";
    }
};

template<typename ... Ts>
struct Variant : Base {
    std::variant<Ts...> var;

    template<typename T>
    Variant(T&& value) : var{std::forward<T>(value)} { }
    std::string as_string() const override {
        return std::string("Variant Node: ")
               + std::visit(value_type_pair, var).first
               + std::visit(value_type_pair, var).second
               + "\n";
    }
};

template<typename T>
struct Value : Base {
    T value;
    Value(const T& value) : value{value} { }
    Value(T&& value) : value{std::move(value)} { }
    std::string as_string() const override {
        return std::string("Value Node:   ") + std::to_string(value) + value_type_pair(T{}).second + "\n";
    }
};

// You are to design a generic List class that can either store
// a generic Tuple Node, a generic Variant Node, or a generic Value Node
// generic types that needs to be supported by Tuple/Variant/Value are int, float, double, and std::string
// you can assume that each type will be used only once within a single Tuple Node
// Note that order of the types does matter for a Tuple node. Tuple<int, float> is different than Tuple<float, int>
// For Variant node, the order is irrelevant

// hint: std::to_string(x) converts most x values of different types to string, you might need it
// hint: you can and must use the standard library as you wish without any limitations.
// hint: consider copy/move construction carefully (perfect forwarding might be needed depending on your implementation)

// (5pts) consider not leaking memory when List gets destroyed.
// (5pts) const correctness of values and methods
// (5pts) careful handling of l-values/r-values during construction of Variant Nodes
// (5pts) careful handling of l-values/r-values during construction of Value Nodes
// (10pts) solve the exam without using "if constexpr" (not even one)
// (70pts) Each correctly handled and printed Node of List will get you 10 pts (we'll test with different 7 Nodes of the same type)

// your total points will get multiplied with a coefficient depending on the number of semicolons that you have used
// EXCLUDING the main() function's semicolons (we won't count the semicolons in the main() function)
// [ 0..30] semicolons: multiplier = 1.3
// [31..35] semicolons: multiplier = 1.2
// [36..40] semicolons: multiplier = 1.1
// [41..45] semicolons: multiplier = 1.0
// [46..50] semicolons: multiplier = 0.9
// [51..55] semicolons: multiplier = 0.8
// [56..XX] semicolons: multiplier = 0.7

int main()
{
    auto whatsup = std::string("Whats up");
    auto L = List{
                  new Tuple<int, float, double>{1, 3.14f, 5.5},
                  new Tuple{1, 3.14f, 5.5, std::string("Hello")},
                  new Variant<int, std::string>{whatsup},
                  new Variant<float, double>{11.11},
                  };
    L.push_back(new Tuple{3.14f});
    L.push_back(new Variant<std::string, double>{std::string("Hi")});
    L.push_back(new Value{11.11f});
    L.print();
}
