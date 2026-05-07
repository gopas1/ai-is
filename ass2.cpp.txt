#include <bits/stdc++.h>
using namespace std;

#define N 3

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Node {
    vector<vector<int>> state;
    int x, y;        // blank position
    int g;           // cost from start
    int h;           // heuristic
    Node* parent;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return (a->g + a->h) > (b->g + b->h);
    }
};

// Manhattan distance heuristic for arbitrary goal
int manhattan(vector<vector<int>>& s, vector<vector<int>>& goal) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = s[i][j];
            if (val != 0) {
                int gx, gy;
                for (int r = 0; r < N; r++)
                    for (int c = 0; c < N; c++)
                        if (goal[r][c] == val) { gx = r; gy = c; }
                dist += abs(i - gx) + abs(j - gy);
            }
        }
    }
    return dist;
}

// Convert state to string (for visited)
string encode(vector<vector<int>>& s) {
    string res;
    for (auto &r : s)
        for (int x : r)
            res += char(x + '0');
    return res;
}

// Print board
void printBoard(vector<vector<int>>& s) {
    for (auto &r : s) {
        for (int x : r)
            cout << x << " ";
        cout << "\n";
    }
    cout << "\n";
}

// Print solution path
void printPath(Node* node) {
    if (!node) return;
    printPath(node->parent);
    printBoard(node->state);
}

// Count inversions
int countInversions(vector<vector<int>>& s) {
    vector<int> arr;
    for (auto &r : s)
        for (int x : r)
            if (x != 0) arr.push_back(x);

    int inv = 0;
    for (int i = 0; i < arr.size(); i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[i] > arr[j]) inv++;

    return inv;
}

// Check solvability for arbitrary goal
bool isSolvable(vector<vector<int>>& start, vector<vector<int>>& goal) {
    // Flatten and map goal positions
    vector<int> sArr, gArr;
    for (auto &r : start) for (int x : r) sArr.push_back(x);
    for (auto &r : goal) for (int x : r) gArr.push_back(x);

    // Map start tiles to goal order
    unordered_map<int,int> pos;
    for (int i = 0; i < 9; i++) pos[gArr[i]] = i;

    vector<int> mapped;
    for (int x : sArr) if (x != 0) mapped.push_back(pos[x]);

    int inv = 0;
    for (int i = 0; i < mapped.size(); i++)
        for (int j = i + 1; j < mapped.size(); j++)
            if (mapped[i] > mapped[j]) inv++;

    return (inv % 2 == 0);
}

// A* algorithm for arbitrary goal
void solve(vector<vector<int>>& start, int sx, int sy, vector<vector<int>>& goal) {
    if (!isSolvable(start, goal)) {
        cout << "This puzzle is NOT solvable.\n";
        return;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    unordered_set<string> visited;

    Node* root = new Node{start, sx, sy, 0, manhattan(start, goal), nullptr};
    pq.push(root);

    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();

        string code = encode(cur->state);
        if (visited.count(code)) continue;
        visited.insert(code);

        if (manhattan(cur->state, goal) == 0) {
            cout << "Solution Found!\n\n";
            printPath(cur);
            cout << "Total moves: " << cur->g << endl;
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur->x + dx[i];
            int ny = cur->y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                vector<vector<int>> newState = cur->state;
                swap(newState[cur->x][cur->y], newState[nx][ny]);

                string nextCode = encode(newState);
                if (visited.count(nextCode)) continue;

                Node* child = new Node{
                    newState,
                    nx,
                    ny,
                    cur->g + 1,
                    manhattan(newState, goal),
                    cur
                };
                pq.push(child);
            }
        }
    }
    cout << "No solution exists.\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== 8-PUZZLE MENU =====\n";
        cout << "1. Enter initial & goal state and solve\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 2) {
            cout << "Exiting program...\n";
            break;
        } else if (choice == 1) {
            vector<vector<int>> start(N, vector<int>(N));
            vector<vector<int>> goal(N, vector<int>(N));
            int sx, sy;

            cout << "Enter initial puzzle state (0 = blank) row by row:\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cin >> start[i][j];
                    if (start[i][j] == 0) {
                        sx = i; sy = j;
                    }
                }
            }

            cout << "Enter goal puzzle state (0 = blank) row by row:\n";
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    cin >> goal[i][j];

            solve(start, sx, sy, goal);
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
