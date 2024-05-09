// std::declval
// [[nodiscard]], std::unique_ptr, std::shared_ptr
// duck typing? type erasure: std::function
// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>

using namespace std;

//struct Foo
//{
//    Foo() = delete;

//    Foo(int) { }

//    void print() const {
//        cout << "Hi" << endl;
//    }
//};

//template<typename T>
//auto callPrintOfType() -> decltype(std::declval<T>().print())
//{
////    T{}.print();
//}


#include <utility>
#include <iostream>

struct Default
{
    int foo() const { return 1; }
};

struct NonDefault
{
    NonDefault() = delete;
    int foo() const { return 1; }
};

int main()
{
    decltype(Default().foo()) n1 = 1;                   // type of n1 is int
     // decltype(NonDefault().foo()) n2 = n1;               // error: no default constructor
    decltype(std::declval<NonDefault>().foo()) n2 = n1; // type of n2 is int
    std::cout << "n1 = " << n1 << '\n'
              << "n2 = " << n2 << '\n';
}

//int main()
//{
//    auto foo = Foo{1};
//    foo.print();

//    callPrintOfType<Foo>();

//    return 0;
//}
