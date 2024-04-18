#include <iostream>
#include <tuple>
#include <list>
#include <string>
#include <variant>

template<typename ... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

auto value_and_type_as_pair = overloaded{
                                         [](int i) { return std::pair{std::to_string(i), "(int)"}; },
                                         [](float f) { return std::pair{std::to_string(f), "(float)"}; },
                                         [](double d) { return std::pair{std::to_string(d), "(double)"}; },
                                         [](const std::string& s) { return std::pair{s, "(string)"}; },
                                         };

struct Base {
    virtual void print() const { };
};

struct List : std::list<Base*> {
    List(auto* ... nodes) { (push_back(nodes), ...); }
    ~List() {
        for(auto ptr : *this)
            delete ptr;
    }
    void print() const {
        std::cout << "Contents of List" << std::endl;
        auto idx = 0;
        for(const auto& item : *this) {
            std::cout << ++idx << ": ";
            item->print();
        }
    }
};

template<typename ... Ts>
struct Tuple : Base {
    std::tuple<Ts...> data;

    Tuple(const Ts& ... ts) : data{std::tuple<Ts...>(ts...)} { }
    void print() const override {
        std::cout << "Tuple Node:   ";
        ((std::cout << get<Ts>(data) << value_and_type_as_pair(Ts{}).second << " "), ...);
        std::cout << std::endl;
    }
};

template<typename ... Ts>
struct Variant : Base {
    std::variant<Ts...> var;

    template<typename T>
    Variant(T&& value) : var{std::forward<T>(value)} { }
    void print() const override {
        std::cout << "Variant Node: ";
        std::cout << std::visit(value_and_type_as_pair, var).first << std::visit(value_and_type_as_pair, var).second << std::endl;
    }
};

template<typename T>
struct Value : Base {
    T value;

    Value(const T& value) : value{value} { }
    Value(T&& value) : value{std::move(value)} { }
    void print() const override {
        std::cout << "Value Node:   " << value << value_and_type_as_pair(T{}).second << std::endl;
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
// (70pts) Each correctly handled and printed Node of List will get you 10 pts (we'll test with different 7 Nodes)

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
