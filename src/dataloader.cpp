#include <iostream>

#include "dataloader.h"
#include "packed_entry.h"
#include "settings.h"

void Data_loader::load_batch() {
    reader.read(reinterpret_cast<char*>(&buffer), sizeof(Packed_entry) * chunk_size);
    u64 bytes_read = reader.gcount();
    while (bytes_read != sizeof(Packed_entry) * chunk_size) {
        reader = std::ifstream(input_file_path);
        reader.read(reinterpret_cast<char*>(&buffer), sizeof(Packed_entry) * chunk_size);
        bytes_read = reader.gcount();
    }
}
