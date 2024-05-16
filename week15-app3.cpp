// RAII (Resource Acquisition is Initialization)

#include <fstream>
#include <iostream>

class File { // class starts as private
public: // we make it public
    File(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
    }

    ~File() {
        file.close();
    }

    // Other methods to interact with the file...

private: // we make it private again
    std::fstream file;
};

int main() {
    try {
        auto myFile = File("somefile.txt");

        // Interact with myFile...
        // Once we leave this scope, myFile is destructed and the file is automatically closed
    } catch (const std::runtime_error& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
