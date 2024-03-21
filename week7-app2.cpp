#include <iostream>
//#include <string>

// move semantics pitfalls

// pitfall #1:
// T&& in deduced context is a forwarding reference
// it can match to both lvalues and rvalues.
// using std::move is an unconditional cast to rvalue.
// this is wrong if constructor of A is used with an lvalue in call site.
namespace PF1
{
struct B { };
struct A
{
    B b_;

    template<typename T>
    A(T&& t) : b_{std::move(t)}
    { }
};
}

// pitfall #2:
// T&& here is not a forwarding reference!
// because T's deduction is done when struct A is instantiated.
// A's constructor is not itself templated. Hence, T&& means rvalue reference
// in an rvalue context, using std::forward is wrong
// std::forward is a CONDITIONAL cast to rvalue. However, we are sure that
// the context is already rvalue. std::move would be correct.
namespace PF2
{
struct B { };
template<typename T>
struct A
{
    B b_;

    A(T&& t) : b_{std::forward<T>(t)}
    { }
};
}

// pitfall #3:
// T&& is a forwarding reference.
// however, if A's contructor is called with an rvalue
// std::forward will cast t to &&.
// unfortunately there is only one 't' instance.
// first move constructor using 't' will steal its internals.
// 't' will be useless for its second usage.
// will cause major bug that cannot be easily detected
namespace PF3
{
struct B { };
struct C { };
struct A
{
    B b_;
    C c_;

    template<typename T>
    A(T&& t)
        : b_{std::forward<T>(t)}
        , c_{std::forward<T>(t)}
    {
    }
};
}


// pitfall #4:
// THIS WAS A TRICK DURING CLASS LECTURE. NOTHING IS WRONG WITH BELOW CODE
// looks like if t1 and t2 are both referencing the same value at the call-site, it is an error.
// but it is not. Because the dangerous thing is stealing/moving from the same value.
// However, two real r-values (temporaries) cannot be the same object at the call site.
// Imagine first r-value is 5, 2nd r-value is 5. There are two different 5s. It's not the same 5.
// So we can move them on their own. No stealing/moving happens on the same l-value.
namespace PF4
{
struct B { };
struct C { };
struct A
{
    B b_;
    C c_;

    template<typename T1, typename T2>
    A(T1&& t1, T2&& t2)
        : b_{std::forward<T1>(t1)}
        , c_{std::forward<T2>(t2)}
    {
    }
};
}

template<typename ...>
struct TypeDisplayer;

#include <type_traits>

// pitfall #5:
// std::is_integral<T>::value waits for a T that does not contain & or *
// However a forwarding reference may deduce T with a & inside.
// For instance, T can be deduced as float&
// passing float& to is_integral such as std::is_integral<float&> is wrong
// a reference is a pointer in its implementation
// pointers are memory addresses that are actually integral values
// in below code, you should remove a potential reference yourself and use that
// for instance use new type K in below code
template<typename T>
void foo(T&&)
{
    //    using K = std::remove_reference_t<T>;

    //    TypeDisplayer<K> a;
    if constexpr(std::is_integral<T>::value) // use K here, instead of T
    {
        // deal with integral types: char, short, int, long, ...
    }
    else
    {
        // deal with non-integral types
    }
}

int main(int argc, char* argv[])
{
    int a = 5;
    foo(a);

    return 0;
}
