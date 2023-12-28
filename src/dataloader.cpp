#include "constants.h"
#include "dataloader.h"
#include <iostream>

void Data_loader::load_batch() {
    reader.read(reinterpret_cast<char*>(&buffer), sizeof(Packed_entry) * batch_size);
    u64 bytes_read = reader.gcount();
    u64 positions_read = bytes_read / sizeof(Packed_entry);
    while (positions_read != batch_size) {
        reader = std::ifstream(input_file_path, std::ios::binary);
        reader.read(reinterpret_cast<char*>((&buffer[positions_read])), sizeof(Packed_entry) * (batch_size - positions_read));
        bytes_read = reader.gcount();
        positions_read += bytes_read / sizeof(Packed_entry);
    }
}
