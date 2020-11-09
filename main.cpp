#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const unsigned int BOARD_SIZE = 3;
const char CROSS = 'X';
const char ZERO = 'O';
const char EMPTY = '-';
enum BoardState { cross, zero, empty };
enum GameState { crossWon, zeroWon, tie, inProgress, gameOver };
typedef vector<vector<BoardState>> Board;

bool isRowComplete(const Board &board, BoardState state, int row) {
  for (int i = 0; i < BOARD_SIZE; i++)
    if (board[row][i] != state)
      return false;
  return true;
}
bool isColumnComplete(const Board &board, BoardState state, int column) {
  for (int i = 0; i < BOARD_SIZE; i++)
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
  for (int i = 0; i < BOARD_SIZE; i++) {
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

void playerMove(Board &board, BoardState state) {
  bool isValidMove = false;
  while (!isValidMove) {
    int r = 0, c = 0;
    cout << "Your move (r, c)";
    cout << "...\n";
    cout << "r: ";
    cin >> r;
    cout << "c: ";
    cin >> c;
    if (board[r][c] == empty) {
      board[r][c] = state;
      isValidMove = true;
    } else {
      cout << "The board is occupied there \n";
    }
  }
}

void printBoard(const Board &board) {
  for (const auto &row : board) {
    for (const auto &state : row) {
      if (state == cross)
        cout << CROSS << '\t';
      else if (state == zero)
        cout << ZERO << '\t';
      else if (state == empty)
        cout << EMPTY << '\t';
    }
    cout << "\n";
  }
}

int mainMenuOption() {
  int option = 0;
  cout << "Welcome to tic tac toe\n";
  cout << "MENU:\n";
  cout << "1: New Game\n";
  cout << "0: Exit\n";
  cout << "...\n";
  cin >> option;
  return option;
}

bool player1Choice() {
  bool playAsCross = true;
  char ch = 'y';
  cout << "Player 1 as Cross(x)? [y/n] ";
  cout << "...\n";
  cin >> ch;
  if (ch == 'y' || ch == 'Y') {
    playAsCross = true;
  } else if (ch == 'n' || ch == 'N') {
    playAsCross = false;
  }
  return playAsCross;
}

int main() {
  unsigned int player1Score = 0;
  unsigned int player2Score = 0;
  GameState gameState = inProgress;
  Board board{
      {empty, empty, empty}, {empty, empty, empty}, {empty, empty, empty}};
  const int option = mainMenuOption();
  if (option) {
    const bool player1AsCross = player1Choice();
    bool gameOver = false;
    std::cout << "Begin! \n";
    printBoard(board);
    while (true) {
      playerMove(board, cross);
      printBoard(board);
      gameState = isGameOver(board);
      if (gameState != inProgress)
        break;
      playerMove(board, zero);
      printBoard(board);
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
