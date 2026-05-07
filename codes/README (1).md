# Artificial Intelligence (AI) Assignments

This repository contains detailed C++ implementations of classical Artificial Intelligence search, optimization, and constraint satisfaction algorithms.

---

## 1. Breadth-First Search (BFS) & Depth-First Search (DFS) (`ass1.cpp`)

**Theory**:

- **BFS** is an uninformed search strategy that explores a graph level by level radially. It guarantees the shortest path in an unweighted graph, utilizing a First-In-First-Out (FIFO) mechanics.
- **DFS** dives deep into a graph's branches before backtracking. It is memory-efficient and naturally implemented via recursion (an implicit Last-In-First-Out stack).

**Implementation details**:

- **Data Structures**: The undirected graph is modeled utilizing an adjacency list `std::vector<int> adj[VERTICES]`. A boolean array `std::vector<bool> visited` ensures nodes are processed identically once.
- **BFS Logic**: Introduces a `std::queue<int>`. The starting node is pushed and marked visited. A `while(!queue.empty())` loop pops the front node, processes it, and pushes all unvisited adjacent neighbors into the queue sequentially.
- **DFS Logic**: Utilizes the system call stack via recursion. The `DFS(vertex)` function marks the current `vertex` as visited, processes it, and iterates over its adjacency list. For every unvisited adjacent node, the function calls `DFS(neighbor)` recursively, diving to the maximum depth before gracefully backtracking.

---

## 2. A\* Algorithm (`ass2.cpp`)

**Theory**:
A\* is a best-first informed search algorithm that finds the most cost-effective path. It uses the cost function $f(n) = g(n) + h(n)$, where $g(n)$ is the exact cost to reach node $n$ from the start and $h(n)$ is the heuristic estimated cost optimally reaching the goal from $n$.

**Implementation details**:

- **State Representation**: Nodes are encapsulated in a `struct` or `class` holding coordinates/identifier, $g\_cost$, $h\_cost$, and $f\_cost$.
- **Priority Queue**: A `<queue>` (specifically a `std::priority_queue` customized as a min-heap) actively sorts candidate nodes evaluating the lowest continuous $f(n)$ parameter.
- **Open and Closed Lists**: An `open_set` (nodes to be evaluated) and a `closed_set` (visited nodes, usually a boolean array or hash map) prevent infinite cycles.
- **Execution**: The algorithm pops the node with the lowest $f(n)$. If it evaluates to the target goal, it reconstructs the parent paths. Otherwise, it generates neighbors, calculates their localized $g(n)$ and heuristic $h(n)$, and pushes them into the priority queue if they present a strictly better path than previously recorded configurations.

---

## 3. Greedy Search Algorithms (`ass3.cpp`)

**Theory**:
Greedy algorithms make the locally optimal choice at each stage with the hope of finding a global optimum. Typical applications include Selection Sort, Job Scheduling, or Minimum Spanning Trees (like Prim's or Kruskal's), and Dijkstra's Shortest Path.

**Implementation details**:

- **Selection Sort Variant**: Employs nested `for` loops. The outer loop selects the target position, while the inner loop linearly scans the remaining unsorted array chunk to greedily pluck the absolute minimum value and `std::swap` it.
- **Minimum Spanning Tree (Prim's)**: Maintains a heavily weighted `key[]` array (initialized to infinity) and a boolean `inMST` array. The algorithm greedily picks the minimum weight vertex not yet in the MST. Once picked, it evaluates adjacent nodes. If the mapped edge weight is functionally lesser than the stored `key[]`, it structurally updates the mapping, sequentially building the lowest-cost spanning branches over $V-1$ iterations.
- **Dijkstra's (Shortest Path)**: Similar greedy array structure to Prim's, but evaluates the _aggregate_ distance from the source vertex. Edge relaxation evaluates `if (distance[u] + weight(u, v) < distance[v])`, forcefully updating the shortest scalar traversal lengths dynamically.

---

## 4. N-Queens Problem (CSP & Backtracking) (`nQueen.cpp`)

**Theory**:
The N-Queens problem is a classic Constraint Satisfaction Problem (CSP). The objective is to place $N$ queens on an $N \times N$ chessboard such that no two queens threaten each other. This means no two queens can share the same row, column, or diagonal.

**Implementation details**:

- **Condition Checking (`isSafe`)**: Utilizes a `bool isSafe(board, row, col)` function that specifically checks the left side of the current row, the upper-left diagonal, and the lower-left diagonal on the 2D `board[][]` to ensure no queens are present.
- **Backtracking Engine (`solve`)**: Follows a recursive column-by-column placement strategy:
  1. **Base Case**: If all queens are placed (current column evaluates to $N$), return `true` (success).
  2. **Iterative Placement**: Loop through candidate rows (0 to $N-1$) for the given column.
  3. **Assignment**: Execute `isSafe()`. If true, assign the queen (`board[row][col] = 1`).
  4. **Recursive Step**: Call `solveNQUtil(board, col + 1)`. If it returns true, cascade the success upward.
  5. **Backtracking / Pruning**: If the subsequent recursive sequence fails, trigger the backtrack by removing the queen (`board[row][col] = 0`) and proceed to evaluate the next row down.

---

## 5. Graph Coloring Problem (CSP & Backtracking) (`graph_coloring.cpp`)

**Theory**:
Graph Coloring is another foundational CSP. The goal is to assign colors from a given set of $M$ colors to all adjacent vertices of a graph such that no two directly interconnected vertices share exactly the same color.

**Implementation details**:

- **Condition Checking (`isSafe`)**: Employs a `bool isSafe(vertex, color)` function that traverses the adjacency matrix `graph[][]`. It verifies that no adjacent connected neighbor natively matches the proposed assigned `color` index.
- **Backtracking Engine (`solve`)**: Utilizes a vertex-by-vertex recursive mechanism:
  1. **Base Case**: If all vertices have been assigned a color (vertex ID evaluates to total vertices), return `true` (success).
  2. **Iterative Placement**: Loop through all available colors (`1` to `M`).
  3. **Assignment**: Test the color with `isSafe()`. If valid, assign it (`colorArray[vertex] = c`).
  4. **Recursive Step**: Call `graphColoringUtil(graph, m, colorArray, vertex + 1)`.
  5. **Backtracking / Pruning**: If coloring the remainder of the graph using this path strictly fails, clear the color assignment (`colorArray[vertex] = 0`) and attempt the next color index in the loop.
