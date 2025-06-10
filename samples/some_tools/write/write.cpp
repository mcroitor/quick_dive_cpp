/**
 * @file write.cpp
 * @brief An application that obtains a file name as command line argument
 *        and writes standard input to that file.
 */

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ofstream file(argv[1], std::ios::out | std::ios::trunc);
    if (!file) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }
    std::string line;
    while (std::getline(std::cin, line)) {
        file << line << '\n';
    }
    if (file.bad()) {
        std::cerr << "Error writing to file: " << argv[1] << "\n";
        return 1;
    }
    file.close();
    if (file.fail()) {
        std::cerr << "Error closing file: " << argv[1] << "\n";
        return 1;
    }
    return 0;
}
