#include <iostream>

#include "interpreter.hpp"

int main(int argc, char *argv[]) {
	if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
	} else if (argc > 2) {
        std::cerr << "Error: Too many arguments\n";
        return 1;
	}
	
    Interpreter().interpret_file(argv[1]);

    return 0;
}