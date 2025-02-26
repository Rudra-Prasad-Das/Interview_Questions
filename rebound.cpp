/*
Given a 2D Matrix where each cell has a height, you can jump to adjacent cells (up, down, left, or
right). The jumping follows these rules:
● If you jump from cell A to an adjacent cell B, the height of B must be less than or equal to
the height of A (i.e., you can only jump to a lower or equal height).
● After jumping from A to B, if you want to continue jumping to another cell C, the
following conditions must be satisfied:
○ C <= B (you can continue going downwards), or
○ C <= A (you can "bounce back up" but not exceed the starting height A).
● Every node can only be visited once.
The goal is to find the longest valid jumping path starting from any point in the matrix, following
the rules above.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int n, m;
    vector<vector<bool>> vis;
    vector<vector<int>> matrix;
    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int dfs(int x, int y, int diff) {
        vis[x][y] = true;
        int cur_path = 0;

        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (vis[nx][ny]) continue;

            if (matrix[nx][ny] <= matrix[x][y]) {
                cur_path = max(cur_path, dfs(nx, ny, matrix[x][y] - matrix[nx][ny]));
            } else if (matrix[nx][ny] <= matrix[x][y] + diff) {
                cur_path = max(cur_path, dfs(nx, ny, 0));
            }
        }
        
        vis[x][y] = false;
        return cur_path + 1;
    }

    int maxPath(vector<vector<int>>& mat) {
        matrix = mat;
        n = matrix.size();
        m = matrix[0].size();
        vis.assign(n, vector<bool>(m, false));

        int max_path = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max_path = max(max_path, dfs(i, j, 0));
            }
        }
        return max_path;
    }
};

int main() {
    vector<vector<int>> matrix = {
        {4, 8, 7},
        {3, 9, 6},
        {2, 1, 5}
    };

    Solution sol;
    cout << "Max Path Length: " << sol.maxPath(matrix) << endl;
    return 0;
}
