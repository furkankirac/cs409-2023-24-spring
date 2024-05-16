// std::optional: c++17

#include <optional>
#include <iostream>

using namespace std;

auto Compute(bool condition) -> optional<int> {
    if (condition) {
        return 42;
    } else {
        return nullopt;
    }
}


int main() {
    auto result = Compute(true);
    if (result.has_value()) {
        std::cout << "Value: " << result.value() << std::endl;
    } else {
        std::cout << "No value" << std::endl;
    }

    return 0;
}

