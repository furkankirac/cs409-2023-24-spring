// future, promise, std::async

#include <iostream>
#include <future>

// will be called by std::async
int ComputeSum(int a, int b) {
    return a + b;
}

// web programming, javascript/typescript

int main() {
    std::future<int> fut = std::async(ComputeSum, 2, 3);

    // ....

    // get result of ComputeSum by waiting for it to complete if necessary
    int result = fut.get();

    std::cout << "The sum is: " << result << std::endl;

    return 0;
}
