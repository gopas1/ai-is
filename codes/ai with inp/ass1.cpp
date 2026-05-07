#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ================= DFS =================

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;

        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    // ================= BFS =================

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        cout << endl;
    }

    // ================= DLS =================

    void DLSUtil(int node,
                 vector<bool>& visited,
                 int depth,
                 int limit) {

        if (depth > limit)
            return;

        visited[node] = true;

        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DLSUtil(neighbor,
                        visited,
                        depth + 1,
                        limit);
            }
        }
    }

    void DLS(int start, int limit) {
        vector<bool> visited(V, false);

        cout << "DLS Traversal: ";
        DLSUtil(start, visited, 0, limit);

        cout << endl;
    }

    // ================= IDDFS =================

    void IDDFS(int start, int maxDepth) {
        cout << "IDDFS Traversal:\n";

        for (int depth = 0; depth <= maxDepth; depth++) {
            vector<bool> visited(V, false);

            cout << "Depth " << depth << ": ";

            DLSUtil(start, visited, 0, depth);

            cout << endl;
        }
    }

    // ================= FIND ELEMENT =================

    bool findElementDFSUtil(int node,
                            int target,
                            vector<bool>& visited) {

        if (node == target)
            return true;

        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findElementDFSUtil(neighbor,
                                       target,
                                       visited)) {
                    return true;
                }
            }
        }

        return false;
    }

    void findElementDFS(int start, int target) {
        vector<bool> visited(V, false);

        if (findElementDFSUtil(start,
                               target,
                               visited)) {
            cout << "Element Found\n";
        } else {
            cout << "Element Not Found\n";
        }
    }

    // ================= FIND ELEMENT WITH DEPTH =================

    bool findWithDepthUtil(int node,
                           int target,
                           vector<bool>& visited,
                           int depth,
                           int limit) {

        if (depth > limit)
            return false;

        if (node == target)
            return true;

        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                if (findWithDepthUtil(neighbor,
                                      target,
                                      visited,
                                      depth + 1,
                                      limit)) {
                    return true;
                }
            }
        }

        return false;
    }

    void findWithDepth(int start,int target,int limit) {

        vector<bool> visited(V, false);

        if (findWithDepthUtil(start,target,visited,0,limit)) {
            cout << "Element Found Within Depth\n";
        } else {
            cout << "Element Not Found Within Depth\n";
        }
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter all edges:\n";

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;

        if (u >= V || v >= V || u < 0 || v < 0) {
            cout << "Invalid edge!\n";
            i--;
        } else {
            g.addEdge(u, v);
        }
    }

    int choice, start, limit;

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. DFS\n";
        cout << "2. BFS\n";
        cout << "3. DLS\n";
        cout << "4. IDDFS\n";
        cout << "5. Find Element\n";
        cout << "6. Find Element With Depth\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter starting vertex: ";
                cin >> start;

                g.DFS(start);
                break;

            case 2:
                cout << "Enter starting vertex: ";
                cin >> start;

                g.BFS(start);
                break;

            case 3:
                cout << "Enter starting vertex: ";
                cin >> start;

                cout << "Enter depth limit: ";
                cin >> limit;

                g.DLS(start, limit);
                break;

            case 4:
                cout << "Enter starting vertex: ";
                cin >> start;

                cout << "Enter max depth: ";
                cin >> limit;

                g.IDDFS(start, limit);
                break;

            case 5: {
                int target;

                cout << "Enter starting vertex: ";
                cin >> start;

                cout << "Enter target element: ";
                cin >> target;

                g.findElementDFS(start, target);
                break;
            }

            case 6: {
                int target;

                cout << "Enter starting vertex: ";
                cin >> start;

                cout << "Enter target element: ";
                cin >> target;

                cout << "Enter depth limit: ";
                cin >> limit;

                g.findWithDepth(start,
                                target,
                                limit);
                break;
            }

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

/*
================ SAMPLE INPUT =================

Enter number of vertices: 5
Enter number of edges: 5

Enter all edges:
0 1
0 2
1 3
2 3
3 4

--------------- DFS ----------------

Enter choice: 1
Enter starting vertex: 0

Output:
DFS Traversal: 0 1 3 2 4

--------------- BFS ----------------

Enter choice: 2
Enter starting vertex: 0

Output:
BFS Traversal: 0 1 2 3 4

--------------- DLS ----------------

Enter choice: 3
Enter starting vertex: 0
Enter depth limit: 1

Output:
DLS Traversal: 0 1 2

--------------- IDDFS ----------------

Enter choice: 4
Enter starting vertex: 0
Enter max depth: 3

Output:
IDDFS Traversal:
Depth 0: 0
Depth 1: 0 1 2
Depth 2: 0 1 3 2
Depth 3: 0 1 3 2 4

--------------- FIND ELEMENT ----------------

Enter choice: 5
Enter starting vertex: 0
Enter target element: 4

Output:
Element Found

--------------- FIND ELEMENT WITH DEPTH ----------------

Enter choice: 6
Enter starting vertex: 0
Enter target element: 4
Enter depth limit: 2

Output:
Element Not Found Within Depth

Enter depth limit: 3

Output:
Element Found Within Depth
*/