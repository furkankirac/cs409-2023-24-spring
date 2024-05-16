// singleton, factory, observer

#include <iostream>
#include <vector>

using namespace std;

// ------------------------------------------------
// SINGLETON
// ------------------------------------------------
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;


// ------------------------------------------------
// FACTORY
// ------------------------------------------------
class Product { // abstract class, because it contains at least 1 unimplemented function
public:
    virtual void function() = 0; // unimplemented
};

class ConcreteProductA : public Product {
public:
    void function() override {
        // Implementation
    }
};

class ConcreteProductB : public Product {
public:
    void function() override {
        // Implementation
    }
};

class Factory {
public:
    static Product* createProduct(std::string type) {
        if (type == "A") {
            return new ConcreteProductA();
        } else if (type == "B") {
            return new ConcreteProductB();
        } else {
            return nullptr;
        }
    }
};

// ------------------------------------------------
// OBSERVER: publish-subscribe model
// ------------------------------------------------
class Observer {
public:
    virtual void update(int value) = 0;
};

class ConcreteObserver : public Observer {
public:
    void update(int value) override {
        // Handle the update
    }
};

class Subject {
private:
    int myValue;
    std::vector<Observer*> myObservers;

public:
    void attach(Observer* observer) {
        myObservers.push_back(observer);
    }

    void set_val(int value) {
        myValue = value;
        notify();
    }

    void notify() {
        for (Observer* observer : myObservers) {
            observer->update(myValue);
        }
    }
};


int main()
{
    auto* ptr1 = Singleton::getInstance(); // 0x12345678
    auto* ptr2 = Singleton::getInstance(); // 0x12345678
    auto* ptr3 = Singleton::getInstance(); // 0x12345678
}
