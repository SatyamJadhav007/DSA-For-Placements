#include <iostream>
#include <cstring>
using namespace std;

int N;                  // Size of chessboard (N x N)
int board[20][20];      // Board (supports N up to 20)

// --------------------------------------------------
// Check if a queen can be placed at board[row][col]
// --------------------------------------------------
bool isSafe(int row, int col) {
    // Check left side in same row
    for (int j = 0; j < col; j++) {
        if (board[row][j] == 1)
            return false;
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check lower left diagonal
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// --------------------------------------------------
// Recursive function to place queens column by column
// --------------------------------------------------
bool solveNQueens(int col) {
    // All queens placed successfully
    if (col == N)
        return true;

    // Try placing a queen in each row of this column
    for (int row = 0; row < N; row++) {
        if (isSafe(row, col)) {

            board[row][col] = 1;  // Place queen
            cout << "Placing queen at (" << row << ", " << col << ")\n";

            // Recur to place rest of the queens
            if (solveNQueens(col + 1))
                return true;

            // If placing here didn’t lead to a solution → backtrack
            board[row][col] = 0;
            cout << "Backtracking from (" << row << ", " << col << ")\n";
        }
    }

    return false;  // No safe position found in this column
}

// --------------------------------------------------
// Driver function
// --------------------------------------------------
int main() {
    cout << "Enter the value of N (size of chessboard): ";
    cin >> N;

    memset(board, 0, sizeof(board));

    if (!solveNQueens(0)) {
        cout << "\nNo solution exists for " << N << " queens.\n";
        return 0;
    }

    // Print final board
    cout << "\nFinal Board Arrangement:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << "\n";
    }

    cout << "\nTime Complexity: O(N!)\n";
    return 0;
}
