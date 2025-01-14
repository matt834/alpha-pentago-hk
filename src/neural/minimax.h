#include <array>
#include <cfloat>
#include <unordered_map>

#include "neural/heuristic.h"
#include "pentago/bitboard.h"
#include "pentago/position.h"

#pragma once

namespace pentago {
static const float kPositiveInfinity = FLT_MAX;
static const float kNegativeInfinity = -FLT_MAX;
static const int kMaxSearchDepth = 3;

static const std::array<float, kNumWeights> kDefaultWeights = {
    13.38, 16.57, 16.60, 15.48, 15.92, 16.16, 14.23, 14.73};

struct ReturnValue {
  float value;
  Move move;
  std::uint8_t plyCount;
};

// To reduce size of position_lookup tables
struct LookupItem {
  float value;
  std::uint8_t plyCount;
};

using PositionLookup = std::unordered_map<std::uint64_t, LookupItem>;

ReturnValue minimax(Position position, Move prevMove, int depth, float alpha,
                    float beta, bool maximizingPlayer,
                    PositionLookup* position_lookup, int* nodesVisited,
                    HeuristicEvaluator evaluator);

ReturnValue minimax(Position position, int depth,
                    PositionLookup* position_lookup, int* nodesVisited,
                    HeuristicEvaluator evaluator);

std::pair<LookupItem, bool> lookupPosition(Position position,
                                           PositionLookup* position_lookup);

void addPositionToLookup(Position position, ReturnValue candidate,
                         PositionLookup* position_lookup);

void maybeSetCurrentBest(ReturnValue& current_best, ReturnValue& candidate,
                         bool maximizingPlayer);

void setReturnValueFromLookupItem(ReturnValue& return_value,
                                  LookupItem lookup_item);

bool willLose(Position position);
}  // namespace pentago