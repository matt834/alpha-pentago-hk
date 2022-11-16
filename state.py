from pentago import Board
import random


class State():
    board: Board

    def __init__(self):
        self.board = Board()

    def serialize(self):
        ...

    def edges(self):
        return self.board.legal_moves()

    def value(self):
        return self.minimax(self.board, 3)

    def heuristic_value(self):
        # For now just a random float from -1 to 1
        # Returning a heuristic value makes the minimax a lot faster
        # It allows the ab pruning to actually prune the tree
        return 0

    def minimax(self, depth, red, alpha=-2, beta=2):
        outcome = self.board.outcome()
        if depth == 0 or outcome is not None:
            if outcome == Board.Outcome.RED_WIN:
                return 1
            elif outcome == Board.Outcome.BLACK_WIN:
                return -1
            elif outcome == Board.Outcome.DRAW:
                return 0
            else:
                return self.heuristic_value()

        if red:
            max_eval = -2
            for move in self.edges():
                self.board.push(move)
                eval = self.minimax(depth-1, alpha, beta, not red)
                self.board.pop()
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
            return max_eval
        else:
            min_eval = 2
            for move in self.edges():
                self.board.push(move)
                eval = self.minimax(depth-1, alpha, beta, not red)
                self.board.pop()
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
            return min_eval


if __name__ == "__main__":
    s = State()
    print(s.minimax(4, s.board.current_player))
