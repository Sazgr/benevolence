#ifndef BENEVOLENCE_DATALOADER
#define BENEVOLENCE_DATALOADER

#include <array>
#include <fstream>
#include <string>

class Data_loader {
    std::string input_file_path;
    std::ifstream reader;
    std::array<char, 1000000> buffer;
public:
    Data_loader(const std::string& path) : input_file_path(path), reader(path, std::ios::binary) {}
    void load_batch();
};

#endif