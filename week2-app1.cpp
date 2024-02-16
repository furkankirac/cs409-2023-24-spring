// Brief intro. to C++ basics.

// C++: a VALUE SEMANTIC language.
//  we work with THE VALUE. we can get references to the values as well.
// Java/Python/Javascript/C#...:
//   everything is allocated in the heap memory (some exceptions of course)
//   everything is accessed via a reference (REFERENCE SEMANTIC language)

// variables and functions and scope
//   primitive types
//   local, global, static variables
//   free, member, static functions
//   function return types

// primitive types: char, int, bool, double, float, ... (because CPU knows about them in its native language)

// reflection
//   auto, sizeof, sizeof..., typeid (RTTI), decltype, ...
//   reflexpr (C++23) -->> introduce us Real Reflection in C++,
//      provide us with new core-features called MetaClasses (by Herb Sutter)
// Creator of C++: Bjarne Stroustrup
// Chairman of C++: Herb Sutter (in Microsoft)

// OOP: struct, class, ctor/dtor, inheritance

// this ptr, static functions
// functions vs function parameters
// methods vs objects


// in C++:
//Integer a = 10; // create an integer in stack memory and assign 10 to it
//b = a; // this is deep-copy. you really copy the VALUE itself.
//Integer* a_ptr = new Integer; // allocate a space for single integer in heap memory
//// a_ptr could be 0x10004afc
//*a_ptr = 10; // assign 10 to it
//b_ptr = a_ptr; // you copy the pointer to the VALUE
//c = *b_ptr; // c is 10

// in Java
//Integer a = new Integer(10);
//b = a; // this is not a deep-copy most of the time, you just copy the reference/pointer


// OOP basics
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment (not covered in CS321)
// inheritance (not covered in CS321)

// function / operator overloading

// almost always auto - aaa rule: move type to the right
// unified/universal initialization

// namespaces
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword) (not covered in CS321)

#include <iostream>

int a = 123; // global variable

void func() {
    // int a = 123;
    static int a = 123;
    std::cout << a << std::endl;
    a++;
}



struct Vector2d {
    // static int numVector2d;

    int x;
    int y;
    char c;

    Vector2d() {
        // numVector2d++;
        x = 0;
        y = 0;
    }

    Vector2d(int x, int y)
    {
        // numVector2d++;
        this->x = x;
        this->y = y;
    }

    void print() {
        std::cout << "X=" << x << " Y=" << y << std::endl;
    }
};


auto addVector2d(Vector2d a, Vector2d b)
{
    Vector2d c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}



int main(int argc, char* argv[])
{
    // Vector2d::numVector2d = 0;


    auto a = Vector2d(1, 2);

    // Vector2d a(1, 2);
    a.print();
    // initVector2d(&a, 1, 2);
    // a.initVector2d(1, 2);

    // std::cout << Vector2d::numVector2d << std::endl;

    Vector2d b(3, 4);
    // std::cout << Vector2d::numVector2d << std::endl;
    // initVector2d(&b, 3, 4);
    // b.initVector2d(3, 4);

    Vector2d c = addVector2d(a, b);
    // std::cout << Vector2d::numVector2d << std::endl;

    std::cout << sizeof(a) << std::endl;


    // int a; // local variable
    // float b;

    // a = 5;
    // ::a = 10;
    // func();
    // func();
    // func();

    return 0;
}
