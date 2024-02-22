// OOP:
// inheritance
// dynamic polymorphism / virtual functions vs RTTI

// move-ctor, move-assignment (delayed)

// functional programming:
// - overloading
//   (all the operators are implemented as functions and they also can ve overloaded)

// Generics / Templates:
// function, class, variable, type templates

#include <iostream>
#include <string>

using namespace std;

namespace Utils {
int VALUE = 123;
}

struct Animal
{
    string name;

    Animal() { }
    Animal(const string& name) : name(name) { };

    // Animal(const Animal& other) : name(other.name) { }
    // ~Animal() { }

    virtual void whoAmI() { // this is the 0th index in the vtable
        cout << "I am an arbitrary animal!" << endl;
    }
};

struct Dog : Animal {
    // string name;
    string breed;

    // Dog() { }
    Dog(const string& name, const string& breed = "")
        : Animal(name), breed(breed) { };

    void whoAmI() override {
        cout << "I am a dog!" << endl;
    }
};


int main(int argc, char* argv[])
{
    using Utils::VALUE;
    cout << VALUE << endl;

    auto animal = Animal("Elephant"); // const char[9]
    auto dog = Dog("Poppy", "Rotweiler");

    animal.whoAmI();
    dog.whoAmI();

    // Animal* animalptr;
    // typedef Animal* AnimalPtr;
    using AnimalPtr = Animal*; // type aliasing
    AnimalPtr animals[] = { &animal, &dog, &animal, &dog };

    cout << "Size of Animal = " << sizeof(Animal) << endl;
    cout << "Size of Dog = " << sizeof(Dog) << endl;

    cout << sizeof(animals) << endl;
    cout << sizeof(AnimalPtr) << endl;
    const auto size = sizeof(animals) / sizeof(AnimalPtr);

    for(auto i=0; i<size; i++) {
        animals[i]->whoAmI();
    }

    return 0;
}
