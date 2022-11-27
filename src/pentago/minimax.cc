// #pragma once

#include <iostream>

#include "position.h"

namespace pen {

int minimax(Position position, int depth, int alpha, int beta) {
	GameResult result = GameResult::UNDECIDED;

	if (position.GetMoveCount() >= 9) {
		result = position.ComputeGameResult();
	}

	if (depth == 0 || result != GameResult::UNDECIDED) {
		if (result == GameResult::WHITE_WON) {
			return 1;
		} else if (result == GameResult::DRAW) {
			return 0;
		} else if (result == GameResult::BLACK_WON) {
			return -1;
		} else {
			// TODO: implement heuristic value function
			return 0;
		}
	}

	if (position.IsBlackToMove()) {
		int minEval = 2;
		for ( Move m : position.GetBoard().GenerateLegalMoves() ) {
			int eval = minimax(Position(position, m), depth-1, alpha, beta);

			minEval = std::min(minEval, eval);
			beta = std::min(beta, eval);

			if (beta <= alpha) {
				break;
			}
		}
		return minEval;
	} else {
		int maxEval = -2;
		for ( Move m : position.GetBoard().GenerateLegalMoves() ) {
			int eval = minimax(Position(position, m), depth-1, alpha, beta);

			maxEval = std::max(maxEval, eval);
			alpha = std::max(alpha, eval);

			if (beta <= alpha) {
				break;
			}
		}
		return maxEval;
	}
}

}

int main(void) {
	int depth = 3;

	pen::PositionHistory history = pen::PositionHistory();

	pen::Move m = pen::minimax(history.Last(), depth, -2, 2);

	std::cout << m.as_string() << std::endl;

	return 0;
}