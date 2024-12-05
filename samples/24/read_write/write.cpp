#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>

void screen_to_file(std::string const& filename) {
    std::ofstream file(filename);
    if(file.is_open()) {
        std::copy(
            std::istreambuf_iterator<char>(std::cin),
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(file)
        );
    }
}

int main(int argc, char** argv) {
    if(argc < 2) {
        return 0;
    }

    screen_to_file(argv[1]);
    return 0;
}