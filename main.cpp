#include "Game.hpp"
int main() {
  using namespace game;
  GameState gameState = inProgress;
  Board board{
      {empty, empty, empty}, {empty, empty, empty}, {empty, empty, empty}};
  const int option = mainMenuOption();
  if (option) {
    const bool player1AsCross = player1Choice();
    std::cout << "Begin! \n";
    while (true) {
      playerMove(board, cross);
      gameState = isGameOver(board);
      if (gameState != inProgress)
        break;
      playerMove(board, zero);
      gameState = isGameOver(board);
      if (gameState != inProgress)
        break;
    }
    if (gameState == crossWon) {
      cout << "Cross won!";
      if (player1AsCross)
        cout << "Player 1 won!\n";
      else
        cout << "Player 2 won!\n";
    } else if (gameState == zeroWon) {
      cout << "Zero won!";
      if (player1AsCross)
        cout << "Player 2 won!\n";
      else
        cout << "Player 1 won!\n";
    } else if (gameState == tie) {
      cout << "It's a tie!";
    }
  }
  return 0;
}
