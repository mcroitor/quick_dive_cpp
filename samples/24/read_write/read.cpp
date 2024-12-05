#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

void file_to_screen(std::string const& filename) {
    if(!std::filesystem::exists(filename)) {
        // skip non-existing files
        return;
    }
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

int main(int argc, char** argv) {
    if(argc < 2) {
        return 0;
    }

    for(int i = 1; i < argc; ++i) {
        file_to_screen(argv[i]);
    }
    return 0;
}