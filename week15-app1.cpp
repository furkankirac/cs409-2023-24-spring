// app1:
// CRTP: curiously recurring template pattern (compile time polymorphism)

// app2: design patterns:
// singleton, factory, observer

// app3:
// RAII (Resource Acquisition is Initialization)

// app4:
// std::optional

// app5:
// multi threading, std::thread

// app6:
// multi threading, mutex

// app7:
// future, promise, std::async

// app8:
// chrono, random, atomics


#include <iostream>

using namespace std;

template <typename Derived> // Derived is equal to any class that is derived from Base
struct Base {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

struct Derived : Base<Derived> {
    void implementation() {
        // implementation details
    }
};

int main() {
    auto d = Derived{}; // AAA notation
    d.interface();  // Calls Derived::implementation

    // static_cast
    {
        int a = 5;
        double b = static_cast<double>(a);
    }

    // dynamic_cast
    {
        struct Base {
            int b;
            virtual void foo() { }
        };
        struct Derived1 : Base {
            int d;
            void foo() override { }
        };
        struct Derived2 : Base {
            void foo() override { }
        };

        Base* basePtr = new Derived1; // 0x12345678: at this location we have a "b" and "d" attribute
        basePtr->foo();

        auto* derived1Ptr = dynamic_cast<Derived1*>(basePtr); // 0x12345678
        auto* derived2Ptr = dynamic_cast<Derived2*>(basePtr); // nullptr
    }

    // reinterpret_cast
    {
        int a = 5;
        int* p = &a; // p = 0x87654321 ----> it stores value 5, its length is sizeof(int) either 4/8
        char* c = reinterpret_cast<char*>(p); // char* can be 4 bytes with 32bits of OS
    }

    // const_cast
    {
        const int a = 5;
        int* p = const_cast<int*>(&a);
        *p = 10;
    }
}
