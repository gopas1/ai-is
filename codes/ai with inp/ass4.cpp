#include <iostream>
#include <vector>
using namespace std;

// ================== N-QUEENS ==================
bool isSafeQueen(vector<vector<int>> &board, int row, int col, int n) {
    // column check
    for(int i=0;i<row;i++)
        if(board[i][col]) return false;

    // left diagonal
    for(int i=row, j=col; i>=0 && j>=0; i--, j--)
        if(board[i][j]) return false;

    // right diagonal
    for(int i=row, j=col; i>=0 && j<n; i--, j++)
        if(board[i][j]) return false;

    return true;
}

bool solveNQueens(vector<vector<int>> &board, int row, int n) {
    if(row == n) return true;

    for(int col=0; col<n; col++) {
        if(isSafeQueen(board, row, col, n)) {
            board[row][col] = 1;

            if(solveNQueens(board, row+1, n))
                return true;

            board[row][col] = 0; 
        }
    }
    return false;
}

void nQueens() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    if(solveNQueens(board, 0, n)) {
        cout << "Solution:\n";
        for(auto &row : board) {
            for(int val : row)
                cout << val << " ";
            cout << endl;
        }
    } else {
        cout << "No solution exists.\n";
    }
}

// ================== GRAPH COLORING ==================
// ---------- SAFE CHECK ----------
bool isSafeColor(int node, int color, vector<int> adj[], vector<int> &colors) {
    // check all adjacent nodes
    for(auto neighbor : adj[node]) {
        if(colors[neighbor] == color)
            return false;
    }
    return true;
}
bool solveGraphColoring(vector<int> adj[], int m, vector<int> &colors, int node, int V) {
    // all vertices colored
    if(node == V)
        return true;

    // try all colors
    for(int c = 1; c <= m; c++) {
        if(isSafeColor(node, c, adj, colors)) {
            colors[node] = c;
            // recursive call
            if(solveGraphColoring( adj, m, colors, node + 1, V ))
                return true;

            // backtrack
            colors[node] = 0;
        }
    }

    return false;
}

// ---------- DRIVER FUNCTION ----------
void graphColoring() {

    int V, E, m;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    vector<int> adj[V];

    cout << "Enter edges (u v):\n";
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Enter number of colors: ";
    cin >> m;
    vector<int> colors(V, 0);

    if(solveGraphColoring( adj, m, colors, 0, V )){
        cout << "\nColor Assignment:\n";
        for(int i = 0; i < V; i++) {
            cout << "Vertex "<< i<< " -> Color "<< colors[i]<< endl;
        }
    }
    else {
        cout << "\nNo solution exists.\n";
    }
}

// ================== MAIN MENU ==================
int main() {
    int choice;

    do {
        cout << "\n---MENU ---\n";
        cout << "1. N-Queens (Backtracking)\n";
        cout << "2. Graph Coloring (Backtracking + B&B)\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                nQueens();
                break;

            case 2:
                graphColoring();
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 3);

    return 0;
}
/*
================ SAMPLE INPUT 1 ================

Enter number of vertices: 4
Enter number of edges: 4

Enter edges (u v):
0 1
0 2
1 2
1 3

Enter number of colors: 3

Output:

Color Assignment:
Vertex 0 -> Color 1
Vertex 1 -> Color 2
Vertex 2 -> Color 3
Vertex 3 -> Color 1


================ SAMPLE INPUT 2 ================

Enter number of vertices: 3
Enter number of edges: 3

Enter edges (u v):
0 1
1 2
0 2

Enter number of colors: 2

Output:

No solution exists.


================ SAMPLE INPUT 3 ================

Enter number of vertices: 5
Enter number of edges: 5

Enter edges (u v):
0 1
0 2
1 3
2 4
3 4

Enter number of colors: 3

Output:

Color Assignment:
Vertex 0 -> Color 1
Vertex 1 -> Color 2
Vertex 2 -> Color 2
Vertex 3 -> Color 1
Vertex 4 -> Color 3

*/

/*
================ SAMPLE INPUT 1 ================

Enter number of queens: 4

Output:

Solution:
0 1 0 0
0 0 0 1
1 0 0 0
0 0 1 0


================ SAMPLE INPUT 2 ================

Enter number of queens: 5

Output:

Solution:
1 0 0 0 0
0 0 1 0 0
0 0 0 0 1
0 1 0 0 0
0 0 0 1 0


================ SAMPLE INPUT 3 ================

Enter number of queens: 3

Output:

No solution exists.

*/