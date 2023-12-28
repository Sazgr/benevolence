#include "packed_entry.h"

std::ostream& operator<<(std::ostream& out, Packed_entry pe) {
    for (int i{63}; i>=0; --i) out << static_cast<bool>(pe.occupied & (1ull << i));
    out << '\n';
    for (int i{}; i<16; ++i) out << static_cast<int>(pe.pieces[i] >> 4) << ' ' << static_cast<int>(pe.pieces[i] & 15) << ' ';
    out << '\n';
    out << "eval " << static_cast<int>(pe.eval) << " result " << static_cast<int>(pe.result) << " stm " << pe.side_to_move << std::endl;
    return out;
}