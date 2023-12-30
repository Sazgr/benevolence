#ifndef BENEVOLENCE_DATALOADER
#define BENEVOLENCE_DATALOADER

#include "data_entry.h"
#include "packed_entry.h"
#include <array>
#include <fstream>
#include <string>
#include <thread>

class Data_loader {
    std::string input_file_path;
    std::ifstream reader;
    bool background_loading;
    std::thread reading_thread;
    int position_index = 0;
    std::array<Data_entry, chunk_size> current_data;
public:
    std::array<Packed_entry, chunk_size> buffer;
    Data_loader(const std::string& path, const bool bg = false) : input_file_path(path), reader(path, std::ios::binary), background_loading(bg) {
        init();
    }
    void load_from_file();
    void load_from_buffer();
    void load_next_batch();
    void init();
};

#endif