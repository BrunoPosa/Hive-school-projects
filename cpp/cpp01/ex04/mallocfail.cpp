#include <stdexcept>
#include <iostream>
#include <string>
#include <limits>

int main() {
    try {
        // Try to allocate a string with the maximum size
        std::string large_string(150, 'A');
        std::cout << "String successfully initialized with size: " << large_string.size() << std::endl;
    } catch (const std::exception& e) {
        // Catch allocation failure
        std::cerr << "Failed to initialize string: " << e.what() << std::endl;
    }

    // Alternative attempt to initialize SIZE_MAX directly (will almost always fail)
    try {
        std::string another_large_string(SIZE_MAX, 'A');
        std::cout << "String initialized to SIZE_MAX: " << another_large_string.size() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialize string with SIZE_MAX: " << e.what() << std::endl;
    }

    return 0;
}
