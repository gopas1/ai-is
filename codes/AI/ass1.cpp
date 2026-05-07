#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Global variables for search state
vector<vector<int>> graph;
vector<bool> visited;
bool found;

/* Reset visited array and found flag */
void reset(int n) {
    visited.assign(n, false);
    found = false;
}

/* 1. DFS Traversal */
void dfsTraversal(int node) {
    visited[node] = true;
    cout << node << " ";
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsTraversal(neighbor);
        }
    }
}

/* 2. BFS Traversal */
void bfsTraversal(int start) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

/* 3. Simple BFS Search */
void bfsSearch(int start, int target) {
    queue<pair<int, int>> q; // node, level
    visited[start] = true;
    q.push({start, 0});

    while (!q.empty()) {
        auto [node, level] = q.front();
        q.pop();

        if (node == target) {
            cout << "Element " << target << " found at level " << level << endl;
            found = true;
            return;
        }

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, level + 1});
            }
        }
    }
}

/* 4. Full DFS Search */
void fullDFS(int node, int target, int level) {
    if (found) return;
    visited[node] = true;

    if (node == target) {
        cout << "Element " << target << " found at level " << level << endl;
        found = true;
        return;
    }

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            fullDFS(neighbor, target, level + 1);
        }
    }
}

/* 5. Depth Limited DFS Search */
void depthLimitedDFS(int node, int target, int level, int limit) {
    if (found || level > limit) return;
    visited[node] = true;

    if (node == target) {
        cout << "Element " << target << " found at level " << level << endl;
        found = true;
        return;
    }

    if (level < limit) { // Only recurse if we haven't hit the limit
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                depthLimitedDFS(neighbor, target, level + 1, limit);
            }
        }
    }
}

/* 6. Level Range DFS Search */
void levelRangeDFS(int node, int target, int level, int minL, int maxL) {
    if (found || level > maxL) return;
    visited[node] = true;

    if (node == target && level >= minL) {
        cout << "Element " << target << " found at level " << level << endl;
        found = true;
        return;
    }

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            levelRangeDFS(neighbor, target, level + 1, minL, maxL);
        }
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter number of nodes: ";
    cin >> numNodes;
    cout << "Enter number of edges: ";
    cin >> numEdges;

    graph.resize(numNodes);
    
    cout << "Enter edges (format: source destination):\n";
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        cin >> u >> v;
        if(u < numNodes && v < numNodes) {
            graph[u].push_back(v);
            // graph[v].push_back(u); // Uncomment this for Undirected Graph
        }
    }

    int choice, target;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. DFS Traversal\n2. BFS Traversal\n3. Simple BFS Search\n";
        cout << "4. Full DFS Search\n5. Depth Limited DFS Search\n6. Level Range DFS Search\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 7) break;
        reset(numNodes);

        switch (choice) {
            case 1:
                cout << "DFS Traversal starting from node 0: ";
                dfsTraversal(0);
                cout << endl;
                break;
            case 2:
                cout << "BFS Traversal starting from node 0: ";
                bfsTraversal(0);
                cout << endl;
                break;
            case 3:
                cout << "Enter element to search: "; cin >> target;
                bfsSearch(0, target);
                break;
            case 4:
                cout << "Enter element to search: "; cin >> target;
                fullDFS(0, target, 0);
                break;
            case 5: {
                int limit;
                cout << "Enter element to search: "; cin >> target;
                cout << "Enter depth limit: "; cin >> limit;
                depthLimitedDFS(0, target, 0, limit);
                break;
            }
            case 6: {
                int minL, maxL;
                cout << "Enter element to search: "; cin >> target;
                cout << "Enter min level: "; cin >> minL;
                cout << "Enter max level: "; cin >> maxL;
                levelRangeDFS(0, target, 0, minL, maxL);
                break;
            }
            default:
                cout << "Invalid choice!\n";
                continue;
        }

        // Only show "Not Found" for search operations (3, 4, 5, 6)
        if (choice >= 3 && choice <= 6 && !found) {
            cout << "Element not found within the specified constraints.\n";
        }

    } while (true);

    return 0;
}