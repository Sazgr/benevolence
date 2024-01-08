#include "constants.h"
#include "dataloader.h"
#include <iostream>
#include <omp.h>

void Data_loader::load_from_file() {
    reader.read(reinterpret_cast<char*>(&buffer), sizeof(Packed_entry) * read_size);
    u64 bytes_read = reader.gcount();
    u64 positions_read = bytes_read / sizeof(Packed_entry);
    while (positions_read != chunk_size) {
        if (positions_read != read_size) reader = std::ifstream(input_file_path, std::ios::binary);
        reader.read(reinterpret_cast<char*>((&buffer[positions_read])), sizeof(Packed_entry) * std::min(read_size, chunk_size - positions_read));
        bytes_read = reader.gcount();
        positions_read += bytes_read / sizeof(Packed_entry);
    }
}

void Data_loader::load_from_buffer() {
    #pragma omp parallel for schedule(static) num_threads(8)
    for (u64 i = 0; i < chunk_size; ++i) {
        current_data[i].load(buffer[i]);
    }
}

void Data_loader::load_next_batch() {
    if (position_index >= chunk_size) {
        if (background_loading && reading_thread.joinable()) {
            reading_thread.join();
        }
        position_index = 0;
        load_from_buffer();
        if (background_loading) {
            reading_thread = std::thread(&Data_loader::load_from_file, this);
        } else {
            load_from_file();
        }
    } else {
        position_index += batch_size;
    }
}

void Data_loader::init() {
    position_index = 0;

    load_from_file();
    load_from_buffer();
    load_from_file();
}