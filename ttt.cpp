#include <iostream>
using namespace std;

const int ROWS = 3;
const int COLS = ROWS;
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void PrintBoard(char board[][COLS], bool showIndexes);
int Prompt(char player, char board[][COLS]);

bool AnyMovesAvailable(char board[][COLS]);
bool IsLegalMove(char board[][COLS], int move);
void MakeMove(char board[][COLS], int move, char player);
char Winner(char board[][COLS]);

int main() {
  int moveCount = 0;
  char board[ROWS][COLS] = {0};
  char currentPlayer = PLAYER_X;

  while ((Winner(board) == 0 && AnyMovesAvailable(board))) {
    PrintBoard(board, true);
    int move = Prompt(currentPlayer, board);
    MakeMove(board, move, currentPlayer);
    ++moveCount;
    currentPlayer = currentPlayer == PLAYER_X ? PLAYER_O : PLAYER_X;
  }

  PrintBoard(board, true);

  if (Winner(board) == PLAYER_X) {
    cout << "Game over after " << moveCount << " moves. X's win." << endl;
  } else if (Winner(board) == PLAYER_O) {
    cout << "Game over after " << moveCount << " moves. O's win." << endl;
  } else {
    cout << "Game over after " << moveCount << " moves. Tie game." << endl;
  }
}

void PrintBoard(char board[][COLS], bool showIndexes) {
  const string RED("\033[0;31m");
  const string GREEN("\033[1;32m");
  const string RESET_COLOR("\033[0m");

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      char value = board[row][col];
      if (value == 0) {
        if (showIndexes) {
          int index = row * COLS + col;
          cout << index;
        }
      } else {
        string color = board[row][col] == PLAYER_X ? RED : GREEN;
        cout << color << board[row][col] << RESET_COLOR;
      }
      cout << " ";
    }
    cout << endl;
  }
}

int Prompt(char player, char board[][COLS]) {
  int move = -1;

  while (1) {
    cout << endl << "Player " << player << " choose an index to move." << endl;
    cin >> move;

    if (IsLegalMove(board, move)) {
      break;
    } else {
      cout << "That isn't a valid move" << endl;
    }
  }

  return move;
}

bool AnyMovesAvailable(char board[][COLS]) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (board[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool IsLegalMove(char board[][COLS], int move) {
    if (move < 0 || move >= ROWS*COLS) {
        return false;
    }
    int row = move / COLS;
    int col = move % COLS;
    return (board[row][col] == 0);
}

void MakeMove(char board[][COLS], int move, char player) {
    int row = move / COLS;
    int col = move % COLS;
    board[row][col] = player;
}

char Winner(char board[][COLS]) {
    for (int row = 0; row < ROWS; ++row) {
        if (board[row][0] != 0 && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            return board[row][0];
        }
    }
    for (int col = 0; col < COLS; ++col) {
        if (board[0][col] != 0 && board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            return board[0][col];
        }
    }
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    return 0;
}
