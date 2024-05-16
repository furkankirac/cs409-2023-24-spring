// multi threading, mutex

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // mutually exclusive

void print(int num) {
    mtx.lock();
    std::cout << "Thread " << std::this_thread::get_id() << ": " << num << std::endl;
    mtx.unlock();
}

int main() {
    // print(1);
    // print(2);
    std::thread t1(print, 1);
    std::thread t2(print, 2);

    t1.join();
    t2.join();

    return 0;
}
