#include "argparse.h"
#include "packed_entry.h"
#include "types.h"

#include <array>
#include <fstream>
#include <string>
#include <vector>

bool verify_int(std::string s) {
    try {
        size_t pos;
        int result = std::stoi(s, &pos);
        if (pos == s.size()) {
            return true;
        } else {
            return false;
        }
    } catch (...) {
        return false;
    }
}

//data format:
//bbrnqknr/p1p1p1pp/1p1p4/5p2/2P2P2/1N6/PP1PP1PP/1RKRBNQB w DBhc - 0 4 [0.0] 32002 d2d3

int main(int argc, char* argv[]) {
    Argument_parser parser;
    parser.add_argument("--in", "infile");
    parser.add_argument("--out", "outfile");
    parser.add_argument("--append", "whether it is append", true);
    parser.set_program_name(argv[0]);

    // print help and exit if no arguments or --help flag provided
    if (argc == 1 || (argc >= 2 && std::string(argv[1]) == "--help")) {
        parser.print_help();
        return 0;
    }

    // parse arguments
    if (!parser.parse(argc, argv)) {
        return 1;
    }

    int n{}, corrupted{};
    std::string run, line, token;
    std::vector<std::string> tokens;
    int result;
    i16 eval;
    std::ofstream out(parser.get_argument_value("--out"), ((parser.get_argument_value("--append") == "") ? std::ios::out : std::ios::app) | std::ios::binary);
    std::ifstream in(parser.get_argument_value("--in"));
    while (true) {
        getline(in, line);
        if (!in) break;
        tokens.clear();
        std::istringstream parser(line);
        while (parser >> token) {tokens.push_back(token);}
        if (tokens.size() != 9) {
            //cout << "wrong num tokens" << endl;
            ++corrupted;
            continue;
        }
        if (!verify_int(tokens[5])) {
            //cout << "full move counter invalid" << endl;
            ++corrupted;
            continue;
        }
        if (!verify_int(tokens[7])) {
            //cout << "eval invalid" << endl;
            ++corrupted;
            continue;
        }
        bool bad = false;
        int board[64]{
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
            12, 12, 12, 12, 12, 12, 12, 12,
        };
        int sq = 0;
        for (auto pos = tokens[0].begin(); pos != tokens[0].end(); ++pos) {
            switch (*pos) {
                case 'p': board[sq] =  0; break;
                case 'n': board[sq] =  2; break;
                case 'b': board[sq] =  4; break;
                case 'r': board[sq] =  6; break;
                case 'q': board[sq] =  8; break;
                case 'k': board[sq] = 10; break;
                case 'P': board[sq] =  1; break;
                case 'N': board[sq] =  3; break;
                case 'B': board[sq] =  5; break;
                case 'R': board[sq] =  7; break;
                case 'Q': board[sq] =  9; break;
                case 'K': board[sq] = 11; break;
                case '/': --sq; break;
                case '1': break;
                case '2': ++sq; break;
                case '3': sq += 2; break;
                case '4': sq += 3; break;
                case '5': sq += 4; break;
                case '6': sq += 5; break;
                case '7': sq += 6; break;
                case '8': sq += 7; break;
                default: bad = true;
            }
            ++sq;
        }
        if (sq != 64) {
            //cout << "sq not 64" << endl;
            ++corrupted;
            continue;
        }
        if (bad) {
            //cout << "board bad" << endl;
            ++corrupted;
            continue;
        }
        Packed_entry packed_entry{};
        for (int i{}; i<64; ++i) {
            if (board[i] != 12) {
                packed_entry.occupied |= (1ull << i);
                int piece_count = popcount(packed_entry.occupied);
                if (piece_count & 1) {
                    packed_entry.pieces[piece_count >> 1] |= (static_cast<u8>(board[i]) << 4);
                } else {
                    packed_entry.pieces[piece_count >> 1] |= static_cast<u8>(board[i]);
                }
            }
        }
        packed_entry.side_to_move = (tokens[1][0] == 'w');
        if (tokens[6] == "[0.0]") packed_entry.result = packed_entry.side_to_move ? -1 : 1;
        if (tokens[6] == "[0.5]") packed_entry.result = 0;
        if (tokens[6] == "[1.0]") packed_entry.result = packed_entry.side_to_move ? 1 : -1;
        packed_entry.eval = std::stoi(tokens[7]);
        //occupied-8 piecelist-16 result-2 score-1 stm-1;
        out.write(reinterpret_cast<char*>(&packed_entry), sizeof(packed_entry));
        ++n;
        if (n % 100000 == 0) printf("\r%10d positions converted | %3d entries corrupted", n, corrupted);
    }
    std::cout << "\ntotal " << n << " positions" << std::endl;
}