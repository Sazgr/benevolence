#include "argparse.h"

#include <sstream>

int main(int argc, char* argv[]) {
    Argument_parser parser;
    parser.add_argument("--data", "path to training data");
    parser.set_program_name(argv[0]);

    // print help and exit if no arguments or --help flag provided
    if (argc == 1 || (argc >= 2 && std::string(argv[1]) == "--help")) {
        parser.print_help();
        return 0;
    }

    // parse arguments
    if (!parser.parse(argc, argv)) {
        return 1;
    }

    // Extract values from parsed arguments
    std::string dataset_path    = parser.get_argument_value("--data");
    std::cout << "Dataset Path: " << dataset_path << "\n";
    std::cout << std::endl;

    return 0;
}