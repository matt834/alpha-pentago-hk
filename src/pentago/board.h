#pragma once

#include <cstdint>

#include "pentago/bitboard.h"

namespace pentago {

enum class BoardResult : uint8_t { UNDECIDED, THEY_WON, DRAW, WE_WON };

class PentagoBoard {
 public:
  PentagoBoard() = default;

  // Gaetano Rispoli Notation!
  PentagoBoard(const std::string& grn) { SetFromGrn(grn); }

  void Clear();

  void SetFromGrn(std::string grn);

  void ApplyMove(Move move);

  bool IsLegalMove(Move move) const;

  MoveList SmartGenerateLegalMoves() const;

  MoveList GenerateLegalMoves() const;

  BoardResult ComputeBoardResult() const;

  bool full() const { return (our_pieces() | their_pieces()) == 0xFFFFFFFFF; }

  void SwapBitBoards() { swap(our_pieces_, their_pieces_); }

  std::string DebugString(bool blackToMove) const;

  BitBoard our_pieces() const { return our_pieces_; }

  BitBoard their_pieces() const { return their_pieces_; }

 private:
  BitBoard our_pieces_;
  BitBoard their_pieces_;
};

}  // namespace pentago
