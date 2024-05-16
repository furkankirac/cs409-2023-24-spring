// multi threading, std::thread
// pre-emptive multitasking OS (even in a single core) with context switch
// NMI (non-maskable interrupt)

#include <iostream>
#include <thread>

void myThreadFunction() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << std::this_thread::get_id() << ": " << i << std::endl;
    }
}

int main() {
    // std::function f; // type-erasure

    std::thread t1(&myThreadFunction);

    myThreadFunction();

    t1.join();

    return 0;
}
