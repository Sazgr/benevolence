#ifndef BENEVOLENCE_PACKED_ENTRY
#define BENEVOLENCE_PACKED_ENTRY

#include "types.h"
#include <array>
#include <iostream>

struct Packed_entry {
    u64 occupied{};                       //8
    std::array<u8, 16> pieces{};          //16
    i16 eval{};                           //2
    i8 result{};                          //1
    bool side_to_move{};                  //1
    std::array<u8, 2> king_square{64, 64};//2
    std::array<u8, 2> padding;            //2
    u8 piece(int index) {
        return (index & 1) ? (pieces[index >> 1] & 15) : (pieces[index >> 1] >> 4);
    }
};

std::ostream& operator<<(std::ostream& out, Packed_entry pe);

#endif