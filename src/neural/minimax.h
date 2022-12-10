#include <unordered_map>

#include "pentago/bitboard.h"
#include "pentago/position.h"

#pragma once

namespace pen {
static const int MAX_POSITION_VALUE = 1000;
static const int DEPTH = 3;

struct ReturnValue {
  int value;
  Move move;
  int plyCount;
};

ReturnValue minimax(Position position, Move prevMove, int depth, int alpha,
                    int beta,
                    std::unordered_map<std::uint64_t, ReturnValue>* lookup);

ReturnValue minimax(Position position,
                    std::unordered_map<std::uint64_t, ReturnValue>* lookup);
}  // namespace pen