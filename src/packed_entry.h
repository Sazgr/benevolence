#ifndef BENEVOLENCE_PACKED_ENTRY
#define BENEVOLENCE_PACKED_ENTRY

#include "types.h"

#include <array>

struct Packed_entry {
    u64 occupied;               //8
    std::array<u8, 16> pieces;  //16
    i16 eval;                   //2
    i8 result;                  //1
    bool side_to_move;          //1
};

#endif