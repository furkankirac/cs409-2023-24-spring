#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct BigObject {
    string s;
    vector<char> data;

    // BigObject(const char* s) {

    // }

    BigObject() = default;

    template<typename T>
    BigObject(T&& s, const char* p)
        : s(std::forward<T>(s))
        , data(strlen(p) + 1)
    {
        for(int i=0; i<data.size(); i++)
            data[i] = p[i];
        // if constexpr(std::is_same_v<T, string>) {

        // }
    }

    template<typename T>
    BigObject(T&& other)
        : s(std::forward<T>(other.s))
        , data(std::forward<T>(other.data))
    {
        // ...
        // ...
        // ...
        // ...
        // ...
        // ...
        // ...
        // ...
    }

    // BigObject(const BigObject& other) : s(other.s), data(other.data)
    // {
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    // }
    // BigObject(BigObject&& other) : s(std::move(other.s)), data(std::move(other.data)) {
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    //     // ...
    // }

    // BigObject(const string& s) : s(s) { }
    // BigObject(string&& s) : s(std::move(s)) { }
};

auto foo(auto&& func) {
    char data[] = {'h', 'i', ' ', 't', 'h', 'e', 'r', 'e', '!', 0};
    auto bo = BigObject{"abc", data};
    func();
    return bo;
}


// struct FFFF {
//     BigObject k;
//     // void* _vtable; // 8 bytes

//     void operator() () {
//         cout << "I am a dying lambda" << endl;
//     }

//     // virtual void another() { }
//     // virtual void another2() { }
// };

int main(int argc, char* argv[])
{
    // auto f = FFFF{};
    // auto g = FFFF{};
    // cout << sizeof(f) << endl;
    BigObject k;
    auto f = []() { cout << "I am a dying lambda" << endl; };
    BigObject bo = foo(f); // copy ctor? move ctor?

    BigObject bo2 = std::move(bo);

    return 0;
}
