// std::optional<T>
// = default, = delete, std::declval
// [[nodiscard]], std::unique_ptr, std::shared_ptr
// duck typing? type erasure: std::function
// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>
#include <optional>
#include <vector>

using namespace std;

// Function to find an element in a vector that meets a certain condition
std::optional<int> findFirstEven(const std::vector<int>& data) {
    for (int num : data) {
        if (num % 2 == 0) {
            return num; // Returns the first even number found
        }
    }
    return {}; // Return an empty std::optional (std::nullopt works as well)
}

int main() {
    std::vector<int> values = {1, 3, 5, 6, 7};

    auto result = findFirstEven(values);

    if (result) { // Checks if result has a value
        std::cout << "First even number: " << *result << std::endl;
    } else {
        std::cout << "No even number found." << std::endl;
    }

    return 0;
}
