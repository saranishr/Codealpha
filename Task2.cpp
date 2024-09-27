#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to check if it's safe to place a number in a cell
bool isSafe(const vector<vector<int>>& board, int row, int col, int num, int N) {
    int boxSize = sqrt(N);

    // Check the row and column
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num || board[x][col] == num) {
            return false;
        }
    }

    // Check the box
    int startRow = row - row % boxSize, startCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& board, int N) {
    int row, col;
    bool empty = true;

    // Find an empty space in the board
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                empty = false;
                break;
            }
        }
        if (!empty) break;
    }

    // If there is no empty space left, we are done
    if (empty) {
        return true;
    }

    // Try numbers 1 to N
    for (int num = 1; num <= N; num++) {
        if (isSafe(board, row, col, num, N)) {
            board[row][col] = num;

            // Recursively try to fill in the rest of the board
            if (solveSudoku(board, N)) {
                return true;
            }

            // If adding num didn't lead to a solution, reset and try again
            board[row][col] = 0;
        }
    }
    return false; // Trigger backtracking
}

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Enter the size of the Sudoku grid (N): ";
    cin >> N;

    if (sqrt(N) != static_cast<int>(sqrt(N))) {
        cout << "N must be a perfect square (e.g., 4, 9, 16)." << endl;
        return 1;
    }

    vector<vector<int>> board(N, vector<int>(N, 0));
    
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    if (solveSudoku(board, N)) {
        cout << "Solved Sudoku:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
