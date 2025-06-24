/**
 * @file filter.cpp
 * @brief An application that obtains a string as command line argument,
 * reads standard input, filters lines containing the string and
 * writes them to standard output.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filter_string>\n";
        return 1;
    }

    std::string filter_string = argv[1];
    std::string line;

    // Read lines from standard input
    while (std::getline(std::cin, line)) {
        // Check if the line contains the filter string
        if (line.find(filter_string) != std::string::npos) {
            // Write the line to standard output
            std::cout << line << '\n';
        }
    }

    return 0;
}
