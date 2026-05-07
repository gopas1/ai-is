#include <iostream>
using namespace std;

#define MAX 10

int N;


bool isSafeBT(int board[MAX][MAX], int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    for (int i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j]) return false;

    for (int i=row, j=col; i<N && j>=0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solveBT(int board[MAX][MAX], int col) {
    if (col >= N) return true;

    for (int i = 0; i < N; i++) {
        if (isSafeBT(board, i, col)) {
            board[i][col] = 1;

            if (solveBT(board, col + 1))
                return true;

            board[i][col] = 0; // backtrack
        }
    }
    return false;
}


bool leftRow[MAX], upperDiag[2*MAX], lowerDiag[2*MAX];

bool solveBB(int board[MAX][MAX], int col) {
    if (col >= N) return true;

    for (int i = 0; i < N; i++) {
        if (!leftRow[i] && !lowerDiag[i+col] && !upperDiag[N-1+col-i]) {

            board[i][col] = 1;
            leftRow[i] = lowerDiag[i+col] = upperDiag[N-1+col-i] = true;

            if (solveBB(board, col + 1))
                return true;

            board[i][col] = 0;
            leftRow[i] = lowerDiag[i+col] = upperDiag[N-1+col-i] = false;
        }
    }
    return false;
}

// ------------------ PRINT ------------------

void printBoard(int board[MAX][MAX]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

// ------------------ MAIN MENU ------------------

int main() {
    int choice;

    cout << "Enter value of N: ";
    cin >> N;

    int board[MAX][MAX] = {0};

    cout << "\n1. Backtracking\n2. Branch and Bound\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        if (solveBT(board, 0))
            printBoard(board);
        else
            cout << "No solution\n";
    }
    else if (choice == 2) {
        // initialize helper arrays
        for (int i = 0; i < MAX; i++) leftRow[i] = false;
        for (int i = 0; i < 2*MAX; i++) {
            lowerDiag[i] = false;
            upperDiag[i] = false;
        }

        if (solveBB(board, 0))
            printBoard(board);
        else
            cout << "No solution\n";
    }
    else {
        cout << "Invalid choice\n";
    }

    return 0;
}