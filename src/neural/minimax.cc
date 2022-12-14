#include "minimax.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "neural/heuristic.h"
#include "pentago/position.h"
#include "utils/bitops.h"

namespace pentago {
ReturnValue minimax(Position position, Move prevMove, int depth, int alpha,
                    int beta, bool maximizingPlayer, PositionLookup* lookup,
                    int* nodesVisited) {
  GameResult result = GameResult::UNDECIDED;
  std::uint8_t plyCount = std::uint8_t(position.GetPlyCount());
  (*nodesVisited)++;

  if (plyCount >= 9) {
    result = position.ComputeGameResult();
  }

  // Value function
  if (depth == 0 || result != GameResult::UNDECIDED) {
    int value;

    if (result == GameResult::WHITE_WON) {
      value = kMaxPositionValue;
    } else if (result == GameResult::DRAW) {
      value = 0;
    } else if (result == GameResult::BLACK_WON) {
      value = kMinPositionValue;
    } else {
      value = heuristic_value(position);
    }

    return ReturnValue{value, prevMove, plyCount};
  }

  MoveList legalMoves = position.GetBoard().GenerateLegalMoves();

  // Search function
  if (maximizingPlayer) {
    ReturnValue currentBest;
    currentBest.value = kNegativeInfinity;  // maxValue

    for (Move& m : legalMoves) {
      // SAME ABOVE AS BELOW
      ReturnValue candidate;
      candidate.move = m;

      Position candidatePosition = Position(position, m);
      std::uint64_t hashes[] = {candidatePosition.Hash(),
                                candidatePosition.ReverseHash()};
      bool foundMatchingHash = false;

      for (std::uint64_t& hash : hashes) {
        if (lookup->find(hash) != lookup->end()) {
          LookupItem item = lookup->find(hash)->second;
          candidate.value = item.value;
          candidate.plyCount = item.plyCount;

          (*nodesVisited)++;
          foundMatchingHash = true;
          break;
        }
      }

      if (!foundMatchingHash) {
        ReturnValue result =
            minimax(candidatePosition, m, depth - 1, alpha, beta,
                    !maximizingPlayer, lookup, nodesVisited);
        candidate.value = result.value;
        candidate.plyCount = result.plyCount;

        LookupItem item = LookupItem{candidate.value, candidate.plyCount};
        (*lookup)[hashes[0]] = item;
      }
      /////////////////////

      if (candidate.value > currentBest.value) {
        currentBest = candidate;
      } else if (candidate.value == currentBest.value) {
        // Losing, take longest path
        if (candidate.value == kMinPositionValue &&
            candidate.plyCount > currentBest.plyCount) {
          currentBest = candidate;
          // Winning, take shortest path
        } else if (candidate.value == kMaxPositionValue &&
                   candidate.plyCount < currentBest.plyCount) {
          currentBest = candidate;
        }
      }

      if (currentBest.value >= beta) {
        break;
      }
      alpha = std::max(currentBest.value, alpha);
    }
    return currentBest;
  } else {
    ReturnValue currentBest;
    currentBest.value = kPositiveInfinity;  // minValue

    for (Move& m : legalMoves) {
      // SAME ABOVE AS BELOW
      ReturnValue candidate;
      candidate.move = m;

      Position candidatePosition = Position(position, m);
      std::uint64_t hashes[] = {candidatePosition.Hash(),
                                candidatePosition.ReverseHash()};
      bool foundMatchingHash = false;

      for (std::uint64_t& hash : hashes) {
        if (lookup->find(hash) != lookup->end()) {
          LookupItem item = lookup->find(hash)->second;
          candidate.value = item.value;
          candidate.plyCount = item.plyCount;

          (*nodesVisited)++;
          foundMatchingHash = true;
          break;
        }
      }

      if (!foundMatchingHash) {
        ReturnValue result =
            minimax(candidatePosition, m, depth - 1, alpha, beta,
                    !maximizingPlayer, lookup, nodesVisited);
        candidate.value = result.value;
        candidate.plyCount = result.plyCount;

        LookupItem item = LookupItem{candidate.value, candidate.plyCount};
        (*lookup)[hashes[0]] = item;
      }
      /////////////////////

      if (candidate.value < currentBest.value) {
        currentBest = candidate;
      } else if (candidate.value == currentBest.value) {
        // Losing, take longest path
        if (candidate.value == kMaxPositionValue &&
            candidate.plyCount > currentBest.plyCount) {
          currentBest = candidate;
          // Winning, take shortest path
        } else if (candidate.value == kMinPositionValue &&
                   candidate.plyCount < currentBest.plyCount) {
          currentBest = candidate;
        }
      }

      if (currentBest.value <= alpha) {
        break;
      }
      beta = std::min(currentBest.value, beta);
    }
    return currentBest;
  }
}

ReturnValue minimax(Position position, PositionLookup* lookup,
                    int* nodesVisited) {
  return minimax(position, Move(std::uint16_t(0)), kMaxSearchDepth,
                 kNegativeInfinity, kPositiveInfinity,
                 !position.IsBlackToMove(), lookup, nodesVisited);
}
}  // namespace pentago
