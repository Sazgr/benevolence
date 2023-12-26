#include "argparse.h"
#include "dataloader.h"
#include "settings.h"
#include "timer.h"

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
    std::string dataset_path = parser.get_argument_value("--data");
    std::cout << "dataset path - " << dataset_path << "\n";
    std::cout << std::endl;
    Data_loader data_loader(dataset_path);
    std::cout << "testing loading speed..." << std::endl;
    Timer timer;
    const int num_batches = 1000;
    for (int i{}; i < num_batches; ++i) {
        data_loader.load_batch();
    }
    std::cout << num_batches * batch_size << " positions loaded in " << timer.elapsed() << " seconds" << std::endl;
    std::cout << num_batches * batch_size / timer.elapsed() / 1000000 << " mpos/s" << std::endl;
    return 0;
}
