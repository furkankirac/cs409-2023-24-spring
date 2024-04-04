// Function objects, operator() overloads and multiple inheritance
// lambda equivalents and the "struct overloaded { ... }" trick
// std::variant

#include <iostream>

using namespace std;


template<typename T>
struct Value
{
    T value;
    operator T() { return value; }
};

struct FuncObjInt
{
    // void print() const { }
    void operator() (int a) const { cout << "This value is an integer " << a << endl; }
};

struct FuncObjFloat
{
    void operator() (float a) const { cout << "This value is a float " << a << endl; }
};

// struct FuncObjIntFloat
// {
//     void operator() (int a) const { cout << "This value is an integer " << a << endl; }
//     void operator() (float a) const { cout << "This value is a float " << a << endl; }
// };

struct FuncObjIntFloat : FuncObjInt, FuncObjFloat
{
    using FuncObjInt::operator(), FuncObjFloat::operator();
};

template<typename ... FuncObjs> // FuncObjInt|FuncObjFloat
struct FuncObjGeneric : FuncObjs... { // FuncObjInt|FuncObjFloat ---> FuncObjInt, FuncObjFloat
    using FuncObjs::operator()...;
    // using FuncObjInt::operator(), FuncObjFloat::operator();
};


template<typename ... Ts> struct Overloaded : Ts... { using Ts::operator()...; };


using Double = Value<double>;
using Float = Value<float>;

#include <variant>

int main(int argc, char* argv[])
{
    // {
    //     auto fo_int = FuncObjInt{};
    //     auto fo_float = FuncObjFloat{};
    //     // fo_int.operator()(5);
    //     fo_int(5);
    //     fo_float(3.14);

    //     auto fo_intfloat = FuncObjIntFloat{};
    //     fo_intfloat(5);
    //     fo_intfloat(3.14f);

    //     auto fo_generic = FuncObjGeneric<FuncObjInt, FuncObjFloat>{};
    //     fo_generic(5);
    //     fo_generic(3.14f);
    // }

    auto lambda_int = [](int a) { cout << "This value is a int " << a << endl; };
    auto lambda_float = [](float a) { cout << "This value is a float " << a << endl; };
    // auto lambda_intfloat = []<typename T>(T a) {
    //     if constexpr(is_same_v<T, int>)
    //         cout << "This value is a int " << a << endl;
    //     else
    //         cout << "This value is a float " << a << endl;
    // };
    // lambda_int(5);
    // lambda_float(3.14f);
    // template<typename ... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
    auto x = Overloaded{lambda_int, lambda_float};

    auto var = variant<int, float>{};
    var = 5;
    // var = 3.14f;

    std::visit(x, var);


    // int k = 5;
    // switch(k) {
    // case 0: break;
    // case 1: break;
    // default: break;
    // }




    // cout << std::get<int>(var) << endl;


    // var = "hi";

    // x(5);
    // x(3.14f);



    return 0;
}
