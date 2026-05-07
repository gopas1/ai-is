#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class GraphColoring {
    int V;
    vector<vector<int>> graph;

public:
    GraphColoring(int v) {
        V = v;
        graph.resize(V, vector<int>(V));
    }

    void inputGraph() {
        cout << "Enter adjacency matrix:\n";

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cin >> graph[i][j];
            }
        }
    }

    // ----------------------------------------------------
    // COMMON SAFE FUNCTION
    // ----------------------------------------------------
    bool isSafe(int vertex, vector<int>& color, int c) {
        for (int i = 0; i < V; i++) {
            if (graph[vertex][i] == 1 && color[i] == c)
                return false;
        }
        return true;
    }

    // ====================================================
    // 1. BACKTRACKING METHOD
    // ====================================================

    bool backtrackingUtil(int vertex, vector<int>& color, int m) {

        // Base Case
        if (vertex == V)
            return true;

        // Try all colors
        for (int c = 1; c <= m; c++) {

            if (isSafe(vertex, color, c)) {

                color[vertex] = c;

                // Recursive Call
                if (backtrackingUtil(vertex + 1, color, m))
                    return true;

                // Backtrack
                color[vertex] = 0;
            }
        }

        return false;
    }

    void solveBacktracking(int m) {

        vector<int> color(V, 0);

        cout << "\nUsing Backtracking:\n";

        if (!backtrackingUtil(0, color, m)) {
            cout << "Solution does not exist.\n";
            return;
        }

        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i
                 << " -> Color " << color[i] << endl;
        }
    }

    // ====================================================
    // 2. BRANCH AND BOUND METHOD
    // ====================================================

    int bestColors;

    void branchBoundUtil(int vertex,
                         vector<int>& color,
                         int usedColors) {

        // If all vertices are colored
        if (vertex == V) {

            bestColors = min(bestColors, usedColors);

            cout << "\nOptimal Coloring Found:\n";

            for (int i = 0; i < V; i++) {
                cout << "Vertex " << i
                     << " -> Color " << color[i] << endl;
            }

            cout << "Total colors used = "
                 << usedColors << endl;

            return;
        }

        // BOUND CONDITION
        // If current colors already exceed best solution
        if (usedColors >= bestColors)
            return;

        // Try assigning colors
        for (int c = 1; c <= usedColors + 1; c++) {

            if (isSafe(vertex, color, c)) {

                color[vertex] = c;

                branchBoundUtil(
                    vertex + 1,
                    color,
                    max(usedColors, c)
                );

                // Backtrack
                color[vertex] = 0;
            }
        }
    }

    void solveBranchAndBound() {

        vector<int> color(V, 0);

        bestColors = INT_MAX;

        cout << "\nUsing Branch and Bound:\n";

        branchBoundUtil(0, color, 0);

        cout << "\nMinimum colors required = "
             << bestColors << endl;
    }
};

// ========================================================
// MAIN FUNCTION
// ========================================================

int main() {

    int V;

    cout << "Enter number of vertices: ";
    cin >> V;

    GraphColoring g(V);

    g.inputGraph();

    int m;

    cout << "Enter maximum colors for Backtracking: ";
    cin >> m;

    // Backtracking
    g.solveBacktracking(m);

    // Branch and Bound
    g.solveBranchAndBound();

    return 0;
}