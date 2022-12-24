#include <cstdint>
#include <unordered_map>

#include "neural/minimax.h"
#include "pentago/position.h"

namespace pentago {
void selfPlay(int depth);

class Game {
 private:
  int max_search_depth = 4;
  PositionLookup* position_lookup;
  PositionHistory position_history;
  HeuristicEvaluator heuristic_evaluator;

 public:
  Game();
  ~Game();

  void SetMaxSearchDepth(int max_search_depth);

  MoveList LegalMoves();

  void MakeMove(Move move);
  void UnmakeMove();

  GameResult ComputeResult();

  Move BestMove();
};
}  // namespace pentago