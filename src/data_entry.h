#ifndef BENEVOLENCE_DATA_ENTRY
#define BENEVOLENCE_DATA_ENTRY

#include "constants.h"
#include "features.h"
#include "packed_entry.h"
#include "types.h"
#include <array>

struct Data_entry {
    Features features;
    i16 eval;
    i8 result;
    bool side_to_move;
    Data_entry() : features(), eval(), result(), side_to_move() {}
    Data_entry(Packed_entry pe) {
        eval = pe.eval / eval_scale;
        result = pe.result;
        side_to_move = pe.side_to_move;
    }
    void load(Packed_entry pe) {
        eval = pe.eval / eval_scale;
        result = pe.result;
        side_to_move = pe.side_to_move;
        features.clear();
        u64 bb = pe.occupied;
        for (int i{}; bb != 0; ++i) {
            int square = pop_lsb(bb);
            int piece = pe.piece(i);
            features.add(index(piece, square, 0, pe.king_square[0]), index(piece, square, 1, pe.king_square[1]));
        }
    }
    const float wdl() const {
        return (result + 1.0f) / 2.0f;
    }
};

#endif