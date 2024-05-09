// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>

using namespace std;

namespace Mine
{

    struct Bar
    {
        friend struct Foo;
    };

    struct Foo {
    private:
        int i = 1111;

    public:
        void print() const {
            cout << "I am a Foo with value " << i << endl;
        }

        friend struct Bar;
        friend void print(const Foo& foo); // this is still a free function not a method
    };

    void print(const Foo& foo) { // this is still a free function not a method
        foo.print();
        cout << "but I am free (with value = " << foo.i << ")" << endl;
    }

}


int main()
{
//    std::cout << "Hi" << std::endl;
//    std::operator<<(std::cout, "");

    cout << "Hi" << endl;
    operator<<(std::cout, "");

    auto foo = Mine::Foo{};
    foo.print();

    print(foo);
}
