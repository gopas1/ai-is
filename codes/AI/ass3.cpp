#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void selectionSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }

    cout << "Sorted array:\n";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

void primMST() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    vector<int> key(n, INT_MAX), parent(n, -1);
    vector<bool> mst(n, false);

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!mst[i] && (u == -1 || key[i] < key[u]))
                u = i;

        mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mst[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Edges in Prim's MST:\n";
    for (int i = 1; i < n; i++)
        cout << parent[i] << " - " << i << endl;
}

struct Edge {
    int u, v, w;
};

bool edgeCompare(Edge a, Edge b) {
    return a.w < b.w;
}

int findParent(int v, vector<int>& parent) {
    if (parent[v] == v)
        return v;
    return parent[v] = findParent(parent[v], parent);
}

void kruskalMST() {
    int v, e;
    cout << "Enter number of vertices and edges: ";
    cin >> v >> e;

    vector<Edge> edges(e);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), edgeCompare);

    vector<int> parent(v);
    for (int i = 0; i < v; i++)
        parent[i] = i;

    cout << "Edges in Kruskal's MST:\n";
    for (Edge edge : edges) {
        int x = findParent(edge.u, parent);
        int y = findParent(edge.v, parent);

        if (x != y) {
            cout << edge.u << " - " << edge.v << endl;
            parent[x] = y;
        }
    }
}

void dijkstra() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix (0 if no edge):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Shortest distances from source:\n";
    for (int i = 0; i < n; i++)
        cout << "Vertex " << i << " : " << dist[i] << endl;
}

void jobScheduling() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<pair<int, int>> jobs(n);
    cout << "Enter jobs (deadline profit):\n";
    for (int i = 0; i < n; i++)
        cin >> jobs[i].first >> jobs[i].second;

    sort(jobs.begin(), jobs.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second > b.second; // Sort by profit
    });

    vector<int> schedule(n, -1);
    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = min(n, jobs[i].first) - 1; j >= 0; j--) {
            if (schedule[j] == -1) {
                schedule[j] = i;
                totalProfit += jobs[i].second;
                break;
            }
        }
    }

    cout << "Total Profit: " << totalProfit << endl;
}

int main() {
    int choice;
    do {
        cout << "\n----- GREEDY ALGORITHMS MENU -----\n";
        cout << "1. Selection Sort\n";
        cout << "2. Prim's Minimum Spanning Tree\n";
        cout << "3. Kruskal's Minimum Spanning Tree\n";
        cout << "4. Dijkstra's Shortest Path\n";
        cout << "5. Job Scheduling\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: selectionSort(); break;
            case 2: primMST(); break;
            case 3: kruskalMST(); break;
            case 4: dijkstra(); break;
            case 5: jobScheduling(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
