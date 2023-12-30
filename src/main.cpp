#include "argparse.h"
#include "constants.h"
#include "dataloader.h"
#include "data_entry.h"
#include "timer.h"

//file           priority  done?
//dataloader.cpp *****
//dataloader.h   *****
//gradients.h    *****     DONE
//lrscheduler.h  **
//nn.cpp         ***
//nn.h           ***
//optimizer.cpp  **
//optimizer.h    **
//quantize.cpp   *
//quantize.h     *
//trainer.cpp    ****
//trainer.h      ****

//todo: make sure converting works, make sure loading works

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
    Data_loader data_loader(dataset_path, false);
    std::cout << "testing loading speed..." << std::endl;
    Timer timer;
    const int num_chunks = 1000;
    for (int i{}; i < num_chunks; ++i) {
        data_loader.load_from_buffer();
        data_loader.load_from_file();
        //std::cout << data_loader.buffer[0] << '\n';
    }
    std::cout << num_chunks * chunk_size << " positions loaded in " << timer.elapsed() << " seconds" << std::endl;
    std::cout << num_chunks * chunk_size / timer.elapsed() / 1000000 << " mpos/s" << std::endl;
    return 0;
}
