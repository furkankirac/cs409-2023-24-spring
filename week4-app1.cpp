#include <iostream>

// operator overloading
// function-call operator
// function objects
// function pointers

// returning a reference
// l-value, r-value, r-value binding reference
// repeat-it algorithm

// copy-ctor, copy-assignment
// move-ctor, move-assignment

using namespace std;

// overloading vs overriding

struct STRING {
    char* data;
    STRING() { data = new char[1]; data[0] = 0; }

    void operator=(const char* value) {
        // ...
    }
};


struct COUT {
    string name;
    // ....

    void operator() () {
        cout << "Hi there " << name << endl;
    }

    void operator<<(int value)
    {
        auto& self = *this;
        self.name = "blabla"; // "blabla" is of type const char[7]
        // left: string
        // in between we have operator=
        // right: const char[7] --> gets demoted const char*
        // operator=(self.name, "blabla");

        cout << value;
    }
};

void operator<<(COUT& self, int value)
{
    // auto& self = *this;
    self.name = "blabla"; // "blabla" is of type const char[7]
    // left: string
    // in between we have operator=
    // right: const char[7] --> gets demoted const char*
    // operator=(self.name, "blabla");

    cout << value;
}

COUT console;

auto lambda_console = [name=string("blabla")]() {
    cout << "Hi there " << name << endl;
};


void dummy() {
    cout << "Hello world!" << endl;
}


int main(int argc, char* argv[])
{
    // 1 << 2; // bitshift to left operator.

    // cout << 5;
    // operator<<(cout, 5);

    console.operator<<(5);
    // console << 5;

    // dummy();
    // console.operator()();
    console();

    lambda_console();


}
