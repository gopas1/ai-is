#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// ---------- 1. Selection Sort ----------

void selectionSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }

        swap(arr[i], arr[minIdx]);
    }

    cout << "Sorted array:\n";

    for(int x : arr)
        cout << x << " ";

    cout << endl;
}

// ---------- 2. Job Scheduling ----------

struct Job {
    int id, deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);

    for(int i = 0; i < n; i++) {
        cout << "Enter id, deadline, profit: ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    sort(jobs.begin(), jobs.end(), cmp);

    int maxDeadline = 0;

    for(auto j : jobs)
        maxDeadline = max(maxDeadline, j.deadline);

    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;

    for(auto j : jobs) {
        for(int t = j.deadline; t > 0; t--) {
            if(slot[t] == -1) {
                slot[t] = j.id;
                totalProfit += j.profit;
                break;
            }
        }
    }

    cout << "Selected Jobs: ";

    for(int i = 1; i <= maxDeadline; i++) {
        if(slot[i] != -1)
            cout << slot[i] << " ";
    }

    cout << "\nTotal Profit: "<< totalProfit << endl;
}

// ---------- 3. Prim's MST ----------

void primMST() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj[V];

    cout << "Enter edges (u v w):\n";

    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> vis(V, 0);
    vector<int> parent(V, -1);

    int total = 0;
    pq.push({0, 0});
    cout << "\nEdges in MST:\n";

    while(!pq.empty()) {

        auto it = pq.top();
        pq.pop();

        int weight = it.first;
        int node = it.second;

        if(vis[node] == 1)
            continue;

        vis[node] = 1;

        total += weight;

        if(parent[node] != -1) {

            cout << parent[node]
                << " - "
                << node
                << " : "
                << weight
                << endl;
        }

        for(auto it : adj[node]) {

            int adjNode = it[0];
            int edW = it[1];

            if(!vis[adjNode]) {
                pq.push({edW, adjNode});
                parent[adjNode] = node;
            }
        }
    }

    cout << "\nTotal Cost: "<< total << endl;
}

// ---------- 4. Kruskal MST ----------

struct Edge {

    int u, v, w;
};

bool cmpEdge(Edge a, Edge b) {

    return a.w < b.w;
}

// ---------- Disjoint Set ----------

class DisjointSet {
    vector<int> parent, size;

public:

    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findUPar(int node) {
        if(node == parent[node])
            return node;
        return parent[node] =
            findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v)
            return;
        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

void kruskalMST() {

    int V, E;

    cout << "Enter vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    for(int i = 0; i < E; i++) {

        cout << "Enter u v weight: ";

        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].w;
    }

    sort(edges.begin(), edges.end(), cmpEdge);

    DisjointSet ds(V);

    int total = 0;

    cout << "\nEdges in MST:\n";

    for(auto e : edges) {

        int u = e.u;
        int v = e.v;
        int w = e.w;

        if(ds.findUPar(u) != ds.findUPar(v)) {
            cout << u<< " - "<< v<< " : "<< w<< endl;
            total += w;
            ds.unionBySize(u, v);
        }
    }

    cout << "\nTotal Cost: "
        << total
        << endl;
}

// ---------- 5. Dijkstra ----------

void dijkstra() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj[V];

    cout << "Enter edges (u v w):\n";

    for(int i = 0; i < E; i++) {

        int u, v, w;

        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    pq.push({0, src});

    while(!pq.empty()) {

        auto it = pq.top();
        pq.pop();

        int dis = it.first;
        int node = it.second;

        for(auto it : adj[node]) {

            int adjNode = it[0];
            int edgeWeight = it[1];

            if(dis + edgeWeight < dist[adjNode]) {
                dist[adjNode] = dis + edgeWeight;
                pq.push({
                    dist[adjNode],
                    adjNode
                });
            }
        }
    }

    cout << "\nShortest distances:\n";

    for(int i = 0; i < V; i++) {

        cout << src
            << " -> "
            << i
            << " = "
            << dist[i]
            << endl;
    }
}

// ---------- 6. Bubble Sort ----------

void bubbleSort() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    for(int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for(int j = 0; j < n - i - 1; j++) {

            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }

    cout << "Sorted array:\n";
    for(int x : arr)
        cout << x << " ";

    cout << endl;
}

// ---------- MAIN MENU ----------

int main() {

    int choice;

    do {

        cout << "\n--- MENU ---\n";

        cout << "1. Selection Sort\n";
        cout << "2. Job Scheduling\n";
        cout << "3. Prim's MST\n";
        cout << "4. Kruskal MST\n";
        cout << "5. Dijkstra\n";
        cout << "6. Bubble Sort\n";
        cout << "7. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                selectionSort();
                break;

            case 2:
                jobScheduling();
                break;

            case 3:
                primMST();
                break;

            case 4:
                kruskalMST();
                break;

            case 5:
                dijkstra();
                break;

            case 6:
                bubbleSort();
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 7);

    return 0;
}

/*

================ SAMPLE INPUTS ================

---------- 1. Selection Sort ----------

Enter choice: 1
Enter number of elements: 5
Enter elements:
64 25 12 22 11

Output:
11 12 22 25 64


---------- 2. Job Scheduling ----------

Enter choice: 2
Enter number of jobs: 4

1 4 20
2 1 10
3 1 40
4 1 30

Output:
Selected Jobs: 3 1
Total Profit: 60


---------- 3. Prim's MST ----------

Enter choice: 3

Enter number of vertices: 5
Enter number of edges: 6

0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7

Output:
Edges in MST:
0 - 1 : 2
1 - 2 : 3
1 - 4 : 5
0 - 3 : 6

Total Cost: 16


---------- 4. Kruskal MST ----------

Enter choice: 4

Enter vertices and edges: 4 5

0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Output:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10

Total Cost: 19


---------- 5. Dijkstra ----------

Enter choice: 5

Enter number of vertices: 5
Enter number of edges: 6

0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1

Enter source vertex: 0

Output:
0 -> 0 = 0
0 -> 1 = 2
0 -> 2 = 3
0 -> 3 = 7
0 -> 4 = 6


---------- 6. Bubble Sort ----------

Enter choice: 6

Enter number of elements: 5
Enter elements:
5 1 4 2 8

Output:
1 2 4 5 8

*/