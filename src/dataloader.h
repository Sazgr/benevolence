#ifndef BENEVOLENCE_DATALOADER
#define BENEVOLENCE_DATALOADER

#include "packed_entry.h"
#include <array>
#include <fstream>
#include <string>

class Data_loader {
    std::string input_file_path;
    std::ifstream reader;
public:
    std::array<Packed_entry, batch_size> buffer;
    Data_loader(const std::string& path) : input_file_path(path), reader(path, std::ios::binary) {}
    void load_batch();
};

#endif