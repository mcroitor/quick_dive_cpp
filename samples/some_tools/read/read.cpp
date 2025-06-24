/**
 * @file read.cpp
 * @brief Application obtains a set of file names as command line arguments,
 *        reads each file, and prints its content to the standard output.
 */

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> [<file2> ...]\n";
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        const char* filename = argv[i];
        std::ifstream file(filename);

        if (!file) {
            std::cerr << "Error opening file: " << filename << "\n";
            continue;
        }

        std::cout << file.rdbuf(); // Read and print the file content
    }

    return 0;
}
