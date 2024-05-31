// Student Name:
// Student ID:
// Course: (409/509?)
// !!!!!!!!! FILL ABOVE !!!!!!!!!!!

// PREFACE
// The aim of this project is to show you that advanced C++ is more advanced than you might think :)
// Finishing this course must have introduced you to the realm of reading/understanding advanced codebases at least.
// One very important aspect to learn is to understand how to research new stuff about C++ and integrate into your mental model.
// This project will demand you to learn two uncovered topics (1: compile-time method existence checking, 2: C macros)
// I urged you not to use C macros if possible during the lectures. However, there are still good usage of C macros for library devs.
// You are the library developer now!

// ABSTRACT
// In this project you will develop a solution for compile-time polymorphic behaviour (i.e. CRTP)
// This project involves researching new stuff.
// You need to understand checking whether a "method_with_a_name" exists under a typename T at compile-time (search Internet, use GPT)
// You need to learn the C macros. You are allowed to use only 1 macro in this file. (At most 1 (one) #define usage is allowed)

// OUTLINE
// You will store the same Animal object instances:
// 1) in a Tuple (std::tuple is FORBIDDEN for CS509 students, CS409 student can use std::tuple if they wish)
// 2) in a std::vector<std::variant>
// You will then traverse each element in the tuple or std::vector<std::variant> and print them to the console.

// DETAIL
// CRTP part must be able to check the derived class for specific methods' existence and change behavior accordingly.
// Imagine that ObjectBase<T> is written in a LIBRARY and below supplied code is using it.
// Your code additions can be considered as the LIBRARY.
// So, LIBRARY had already predefined how to act depending on the methods in the Derived classes.
// Derived classes aren't known when the LIBRARY was finalized.
// But LIBRARY sets some rules such that
// - A Derived class might or might not have a "class_name() const" method
// - A Derived class might or might not have a "travel_style() const" method
// - A Derived class might or might not have a "__xstr__() const" method
// Depending on the availability of above three methods, ObjectBase<Derived> chooses how to act at compile-time!
// (Check console output for understanding how it acts)
// __str__ name in the code is borrowed from Python. It is a std::string representation of the object in human language.
// __xstr__ name is an invention for the purpose of this project and means an additional concatenation to the __str__ result.

// WARNING
// Do not write your code relying on the returned string values from Derived object's functions.
// For instance, do not write "run-time if" to check whether the class_name() returns "Dog" or not
// We will test your ObjectBase<T> with completely different objects.

// Make the code work by EXACTLY MATCHING the console output supplied for you.

// CS409 RULES
// std::tuple is usable for CS409 students.
// Everything (including the std::tuple) in the standart library is allowed for CS409.
// You can use only one macro in your code for any purpose (#define).
// I repeat, you can use macro feature. But at most 1 macro is allowed.
// If you use a macro then it cannot be something like this to escape semicolon count
// #define _SEMI_ ; // FORBIDDEN

// CS509 RULES
// std::tuple is FORBIDDEN for CS509 students.
// I repeat, you CANNOT use std::tuple if you are a CS509 student.
// Everything else in the standart library is allowed to be used (except std::tuple).
// You can use only one macro in your code for any purpose (#define).
// I repeat, you can use macro feature. But at most 1 macro is allowed.
// If you use a macro then it cannot be something like this to escape semicolon count
// #define _SEMI_ ; // FORBIDDEN

// Different courses (CS409 and CS509) will have their own curves for grading.

// GRADING:
// We will test your tuple part and variant part independently by leaving the relevant part active.
// For tuple part your code must compile, else you get zero.
// For variant part your code must compile, else you get zero.
// Stage 1: Collect points
// - An exactly correct console output line gives you +18 points each. You have 12 lines. You can collect 216 points.
// Stage 2: Lose points
// This codebase has already 32 semicolons.
// Any extra semicolon you use will cost you 5pts each.
// Example:
// Total semicolons in the file is 62. Codebase uses 32 already. So you added 30 semicolons.
// Let's consider you solved for all 12 console output lines correctly --> 12*18 - 5*30 = 66 (you get 66 from the exam)
// So, to get 100 you need to solve all lines correctly by using at most 23 semicolons.

#include <iostream>

using namespace std;

// !!!!!!!!! BE SURE TO READ ALL THE INFORMATION ABOVE   !!!!!!!!!!

// !!!!!!!!! WRITE YOUR CODE BELOW STARTING HERE         !!!!!!!!!!
// !!!!!!!!! DO NOT EVER CHANGE CODE ABOVE THIS LINE     !!!!!!!!!!
// !!!!!!!!! YOU WILL GET 0/ZERO FROM THE EXAM IF YOU DO !!!!!!!!!!









// !!!!!!!!! DO NOT EVER CHANGE CODE BELOW THIS LINE     !!!!!!!!!!
// !!!!!!!!! YOU WILL GET 0/ZERO FROM THE EXAM IF YOU DO !!!!!!!!!!

struct Dog : ObjectBase<Dog> {
    auto class_name() const { return "Dog"s; }
    auto travel_style() const { return "walking"s; }
};

struct Bird : ObjectBase<Bird> {
    auto class_name() const { return "Bird"s; }
    auto travel_style() const { return "flying"s; }
    // has no __xstr__()
};

struct SpecialBird : ObjectBase<SpecialBird> {
    auto class_name() const { return "Bird"s; }
    auto travel_style() const { return "flying"s; }
    auto __xstr__() const { return "I am special."s; }
};

struct Rock : ObjectBase<Rock> {
    auto class_name() const { return "Rock"s; }
    // has no travel_style()
    // has no __xstr__()
};

struct RollingRock : ObjectBase<RollingRock> {
    auto class_name() const { return "Rock"s; }
    auto travel_style() const { return "rolling"s; }
    // has no __xstr__()
};

struct ThirdPartyObject : ObjectBase<ThirdPartyObject> {
    // has no class_name()
    // has no travel_style()
    // but it has extra attribute called location
    string location;
    auto __xstr__() const { return location.empty() ? "" : "I live by "s + location + ".";}
};

int main() {
    auto obj = ThirdPartyObject{"3rd-party"};
    auto printer = [](const auto& obj) { cout << obj.__str__() << endl; };

    { // compile-time Tuple structure and suitable print function
        auto objects = Tuple(
            Dog{"Duman"},
            Bird{"Geveze"},
            SpecialBird{},
            Rock(),
            RollingRock(),
            obj
            );
        print(objects, printer);
    }

    cout << endl;

    obj.location = "Nevsehir";

    { // run-time vector+variant usage for solving the same problem
        using AnimalVariant = variant<Dog, Bird, SpecialBird, Rock, RollingRock, ThirdPartyObject>;
        auto objects = vector<AnimalVariant>{
            Dog{"Duman"},
            Bird{"Geveze"},
            SpecialBird{},
            Rock(),
            RollingRock(),
            obj
        };
        print(objects, printer);
    }

    return 0;
}

// EXPECTED CONSOLE OUTPUT
// I am a Dog with name 'Duman'. I travel by walking.
// I am a Bird with name 'Geveze'. I travel by flying.
// I am a Bird. I travel by flying. I am special.
// I am a Rock. I don't travel.
// I am a Rock. I travel by rolling.
// I am an Unknown Class with name '3rd-party'. I don't travel.
//
// I am a Dog with name 'Duman'. I travel by walking.
// I am a Bird with name 'Geveze'. I travel by flying.
// I am a Bird. I travel by flying. I am special.
// I am a Rock. I don't travel.
// I am a Rock. I travel by rolling.
// I am an Unknown Class with name '3rd-party'. I don't travel. I live by Nevsehir.
