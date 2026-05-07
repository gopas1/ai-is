#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int g, h;
    int x, y;

    Node(vector<vector<int>> s, int g_, int h_, int x_, int y_) {
        state = s;
        g = g_;
        h = h_;
        x = x_;
        y = y_;
    }

    int f() const {
        return g + h;
    }
};

string serialize(vector<vector<int>> &state) {
    string s = "";
    for (auto &row : state)
        for (int val : row)
            s += to_string(val);
    return s;
}

void printState(vector<vector<int>> &state) {
    for (auto &row : state) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
    cout << "------\n";
}

// Manhattan heuristic (based on goal)
int calculateH(vector<vector<int>> &state, vector<vector<int>> &goal) {
    int dist = 0;

    // map goal positions
    int pos[9][2];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++) {
            pos[goal[i][j]][0] = i;
            pos[goal[i][j]][1] = j;
        }

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            int val = state[i][j];
            if(val != 0) {
                dist += abs(i - pos[val][0]) + abs(j - pos[val][1]);
            }
        }
    }

    return dist;
}


struct Compare {
    bool operator()(Node const& a, Node const& b) {
        return a.f() > b.f();
    }
};

void printPath(map<string,string> &parent, string goalKey) {
    vector<string> path;

    while(goalKey != "") {
        path.push_back(goalKey);
        goalKey = parent[goalKey];
    }

    reverse(path.begin(), path.end());

    cout << "\nSolution Path:\n";
    for(auto &s : path) {
        for(int i=0;i<9;i++) {
            cout << s[i] << " ";
            if((i+1)%3==0) cout << endl;
        }
        cout << "------\n";
    }
}

// Count inversions
int getInversions(vector<vector<int>> &state) {
    vector<int> arr;
    for(auto &row : state)
        for(int val : row)
            if(val != 0) arr.push_back(val);

    int inv = 0;
    for(int i=0;i<arr.size();i++)
        for(int j=i+1;j<arr.size();j++)
            if(arr[i] > arr[j]) inv++;

    return inv;
}

// Check solvability
bool isSolvable(vector<vector<int>> &start, vector<vector<int>> &goal) {
    return (getInversions(start) % 2) == (getInversions(goal) % 2);
}

// A* Algorithm
void AStar(vector<vector<int>> start, vector<vector<int>> goal) {

    if(!isSolvable(start, goal)) {
        cout << "\nThis puzzle is NOT solvable.\n";
        return;
    }

    int sx, sy;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(start[i][j]==0) {
                sx=i; sy=j;
            }

    priority_queue<Node, vector<Node>, Compare> pq;
    set<string> visited;
    map<string,string> parent;

    string startKey = serialize(start);
    parent[startKey] = "";

    pq.push(Node(start, 0, calculateH(start, goal), sx, sy));

    while(!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        string key = serialize(curr.state);

        if(visited.count(key)) continue;
        visited.insert(key);

        if(curr.state == goal) {
            cout << "\nGoal Reached!\n";
            printPath(parent, key);
            return;
        }

        int dx[] = {-1,1,0,0};
        int dy[] = {0,0,-1,1};

        for(int i=0;i<4;i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if(nx>=0 && nx<3 && ny>=0 && ny<3) {
                vector<vector<int>> newState = curr.state;
                swap(newState[curr.x][curr.y], newState[nx][ny]);

                string newKey = serialize(newState);

                if(!visited.count(newKey)) {
                    parent[newKey] = key;

                    pq.push(Node(
                        newState,
                        curr.g + 1,
                        calculateH(newState, goal),
                        nx, ny
                    ));
                }
            }
        }
    }

    cout << "No solution found.\n";
}

// ---------- MENU ----------
int main() {
    vector<vector<int>> start(3, vector<int>(3));
    vector<vector<int>> goal(3, vector<int>(3));
    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Enter Initial State\n";
        cout << "2. Enter Goal State\n";
        cout << "3. Solve using A*\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Initial State:\n";
                for(int i=0;i<3;i++)
                    for(int j=0;j<3;j++)
                        cin >> start[i][j];
                break;

            case 2:
                cout << "Enter Goal State:\n";
                for(int i=0;i<3;i++)
                    for(int j=0;j<3;j++)
                        cin >> goal[i][j];
                break;

            case 3:
                AStar(start, goal);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 4);

    return 0;
}

/*

================ SAMPLE INPUT =================

--- MENU ---
1. Enter Initial State
2. Enter Goal State
3. Solve using A*
4. Exit

Enter choice: 1

Enter Initial State:
1 2 3
4 0 6
7 5 8

Enter choice: 2

Enter Goal State:
1 2 3
4 5 6
7 8 0

Enter choice: 3

================ OUTPUT =================

Goal Reached!

Final State:
1 2 3
4 5 6
7 8 0

*/