#include "../../include/game/application.h"

int main(const int argc, const char** argv) {
    std::string input;
    if (argc == 1) {
        input = "default";
        std::cout << "No arguments passed, using \'default\' profile.\n";
    } else if (argc == 2) {
        input = *(argv + 1);
        std::cout << "Attempting to load \'" << input << "\'...\n";
    } else {
        std::cout << "Too many arguments.\n";
        return 1;
    }
    start(input);
    return 0;
}

