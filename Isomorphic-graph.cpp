/*
1. IsIsomorph(A, B, N)
This is the main function that:

Converts the graph A into an adjacency matrix.
Converts the graph B into an adjacency list.
Calls _Trace() to find a valid mapping of vertices.
Steps:
Check basic constraints

If the number of edges in A and B are different, return False (not isomorphic).
Convert A into an adjacency matrix (A_connected)

A_connected[i][j] = True means there is an edge between i and j.
Convert B into an adjacency list (B_neighbors)

Stores edges in a dictionary where each key represents a vertex and its value is a list of neighbors.
Call _Trace() function

Starts finding an isomorphic mapping.
2. _Trace(current, N, A_connected, B_neighbors, mappings)
This is a backtracking function that recursively finds a valid vertex mapping.

Steps:
If all vertices are mapped (current == N), print and return True.
Try to map current vertex in A to any unmapped vertex i in B:
Check if i is already assigned → skip it.
Use _Validate() to see if assigning i maintains graph structure.
If valid, store the mapping and recursively call _Trace() for current + 1.
If unsuccessful, backtrack and remove the mapping.
If no valid mapping is found, return False.
3. _Validate(i, current, A_connected, B_neighbors, mappings)
This function checks if mapping vertex current in A to i in B is valid.

Steps:
If current has neighbors in B_neighbors:
For each neighbor in B_neighbors[current]:
If the neighbor is already mapped, check if an edge exists in A_connected[i][mappings[neighbor]].
If not, return False.
If no violations, return True.


*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool Validate(int i, int current, const vector<vector<bool>>& A_connected,
              const unordered_map<int, vector<int>>& B_neighbors,
              const unordered_map<int, int>& mappings) {
    if (B_neighbors.find(current) != B_neighbors.end()) {
        for (int neighbor : B_neighbors.at(current)) {
            if (mappings.find(neighbor) != mappings.end() &&
                !A_connected[i][mappings.at(neighbor)]) {
                return false;
            }
        }
    }
    return true;
}

bool Trace(int current, int N, const vector<vector<bool>>& A_connected,
           const unordered_map<int, vector<int>>& B_neighbors,
           unordered_map<int, int>& mappings) {
    if (current == N) {
        return true;
    }
    for (int i = 0; i < N; i++) {
        if (mappings.find(i) == mappings.end()) {
            if (!Validate(i, current, A_connected, B_neighbors, mappings)) {
                continue;
            }
            mappings[current] = i;
            if (Trace(current + 1, N, A_connected, B_neighbors, mappings)) {
                return true;
            }
            mappings.erase(current);
        }
    }
    return false;
}

bool IsIsomorph(const vector<vector<int>>& A, const vector<vector<int>>& B, int N) {
    if (A.size() != B.size()) {
        return false;
    }
    
    vector<vector<bool>> A_connected(N, vector<bool>(N, false));
    for (const auto& edge : A) {
        A_connected[edge[0]][edge[1]] = true;
        A_connected[edge[1]][edge[0]] = true;
    }
    
    unordered_map<int, vector<int>> B_neighbors;
    for (const auto& edge : B) {
        B_neighbors[edge[0]].push_back(edge[1]);
        B_neighbors[edge[1]].push_back(edge[0]);
    }
    
    unordered_map<int, int> mappings;
    return Trace(0, N, A_connected, B_neighbors, mappings);
}

int main() {
    vector<vector<int>> A = {{0, 1}, {1, 2}, {2, 0}};
    vector<vector<int>> B = {{0, 2}, {2, 1}, {1, 0}};
    int N = 3;
    
    if (IsIsomorph(A, B, N)) {
        cout << "Graphs are isomorphic" << endl;
    } else {
        cout << "Graphs are not isomorphic" << endl;
    }
    
    return 0;
}
