#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
namespace game {
using std::vector;
const unsigned int BOARD_SIZE = 3;
enum BoardState { cross, zero, empty };
enum GameState { crossWon, zeroWon, tie, inProgress, gameOver };
typedef vector<vector<BoardState>> Board;

bool isRowComplete(const Board &board, BoardState state, int row) {
  for (unsigned int i = 0; i < BOARD_SIZE; i++)
    if (board[row][i] != state)
      return false;
  return true;
}
bool isColumnComplete(const Board &board, BoardState state, int column) {
  for (unsigned int i = 0; i < BOARD_SIZE; i++)
    if (board[i][column] != state)
      return false;
  return true;
}
bool isDiagonalComplete(const Board &board, BoardState state) {
  return (board[0][0] == state && board[1][1] == state &&
          board[2][2] == state) ||
         (board[0][2] == state && board[1][1] == state && board[2][0] == state);
}
bool hasStateWon(const Board &board, BoardState state) {
  for (unsigned int i = 0; i < BOARD_SIZE; i++) {
    if (isRowComplete(board, state, i))
      return true;
    if (isColumnComplete(board, state, i))
      return true;
  }
  if (isDiagonalComplete(board, state)) {
    return true;
  }
  return false;
}

bool isAllOccupied(const Board &board) {
  for (const auto &row : board) {
    for (const auto &state : row) {
      if (state == empty)
        return false;
    }
  }
  return true;
}

GameState isGameOver(const Board &board) {
  if (hasStateWon(board, cross)) {
    return crossWon;
  }
  if (hasStateWon(board, zero)) {
    return zeroWon;
  }
  if (isAllOccupied(board))
    return tie;
  return inProgress;
}

} // namespace game
#endif

