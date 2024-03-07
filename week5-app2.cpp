// Write a Value<T> class that uses heap memory for storage! with all ctors and dtors
// move-ctor, move-assignment

// initializer_list<T>
// a Stack<T> implementation

#include <iostream>
#include <string>
#include <vector>

using namespace std; // namespace import into our namespace. do not ever use this in a header file!

template<typename T> // assume T does not contain any modifiers (no ref, no refref)
struct HeapValue
{
    T* ptr = nullptr;

    // new style c-tor accessible by curly brackets
    HeapValue(std::initializer_list<int> content) {
        cout << "new ctor is called with a size of " << content.size() << endl;
    }

    HeapValue(int) { // old style c-tor
        cout << "old ctor is called" << endl;
    }

    // default ctor: delegate construction to type T's default ctor: T{}
    HeapValue() : ptr(new T{}) { }

    // constructing HeapValue<T> from T types
    HeapValue(const T& t) : ptr(new T{t})  { }

    // copy c-tor of HeapValue<T>: clone the right hand side value by delegating to its own copy ctor
    HeapValue(const HeapValue<T>& other) : ptr(new T{*other.ptr}) { }

    // r-value ref binding to HeapValue<T>:
    // we use this kind of binding for signalling us that right side is a temporary value
    HeapValue(HeapValue<T>&& other)
        : ptr(other.ptr) // move the treasure of right side to yourself
    {
        other.ptr = nullptr; // then mark the right side's treasure pointer as null so that only owner is you
    }

    ~HeapValue() {
        delete ptr;
    }
};

int main(int argc, char* argv[])
{
    auto i = HeapValue<int>{};

    {
        auto j = HeapValue<int>{5};
    }

    auto s = HeapValue<string>{"dhrfbkhdgbkdjgbdkgjfdzkjgn"};
    auto s2 = s; // s2 is being constructed
    // auto s3 = HeapValue<string>{string("kjdfbvjhrsbgzsfjhgbzjfhgdbzsjh")}; // move from s2 (steal from s2)
    // auto s3 = (HeapValue<string>&&)s2; // move from s2 (steal from s2)

    cout << s2.ptr << endl;

    auto s3 = std::move(s2); // move from s2 (steal from s2)

    cout << s2.ptr << endl;
    cout << s3.ptr << endl;

    auto s4 = HeapValue<string>({1, 2, 3, 4, 10, 20});
    // auto v = std::vector<int>{10}; // size is 1 integer. that integer is 10
    // auto v2 = std::vector<int>(10); // size is 10 integers. all integers are default constructed


    return 0;
}
