// chrono, random, atomics

#include <iostream>
#include <random> // pseudo-random
#include <atomic>
#include <thread>
#include <chrono>

std::default_random_engine generator;

std::uniform_int_distribution<int> distribution(1, 6); // uniform distribution between [1, 6]

// int counter = 0;
std::atomic<int> counter(0); // atomic integer

template<typename T>
inline void increment_(T& whatever) {
    // read whatever from stack
    ++whatever; // do the job
    // read the previous PC from the stack and jump there
}


void increment() {
    for (int i = 0; i < 10000000; ++i) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(distribution(generator)));
//        mutex.lock();
        // this line -> PC -> save it in the stack
        // push counter to the stack
        // jump to function location in memory
        // increment_(counter);
       ++counter; // atomic increment operation
//        mutex.unlock();
    }
}

int main() {

   // for (int i = 0; i < 10; ++i) {
   //     int random_number = distribution(generator);
   //     std::cout << random_number << std::endl;
   // }

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Counter: " << counter << std::endl;

    return 0;
}
