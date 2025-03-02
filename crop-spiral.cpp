/*
We have a garden formed by N x M cells: in each cell you can plant one of K kinds of crops
(such as tomatoes, potatoes, etc). To satisfy our vegetable needs, we know exactly how many
cells need to be planted for each kind of crop (e.g. 3 cells of tomatoes, 4 cells of potatoes, etc)
and we know that the total number of crops will sum up to exactly NM, so we have to use the
whole garden without leaving empty cells.
In order to make it easier to give each plant exactly the amount of water it requires, it’s
important that crops of the same kind occupy a continuous patch of land in the garden. More
precisely: there must always be a path from a crop to all other crops of the same kind, moving
horizontally and vertically on the grid.
Find any valid crop arrangement for the given garden.
*/
#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> arrange_crops(int N, int M, vector<int> crops) {
    vector<vector<char>> grid(N, vector<char>(M));
    int crop_idx = 0, crop_streak = 0;
    for (int row = 0; row < N; ++row) {
        for (int i = 0; i < M; ++i) {
            int col = (row % 2 == 0) ? i : M - i - 1;
            if (crops[crop_idx] == crop_streak) {
                crop_idx += 1;
                crop_streak = 0;
            }
            grid[row][col] = 'A' + crop_idx;
            crop_streak += 1;
        }
    }
    return grid;
}

// Helper function to print the grid
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << "---------------------\n";
}

int main() {
    // Test Case 1: Basic 3x3 grid with 3 different crops
    vector<int> crops1 = {3, 3, 3};
    cout << "Test Case 1 (3x3 Grid):\n";
    printGrid(arrange_crops(3, 3, crops1));

    // Test Case 2: 4x4 grid with 4 crops
    vector<int> crops2 = {4, 4, 4, 4};
    cout << "Test Case 2 (4x4 Grid):\n";
    printGrid(arrange_crops(4, 4, crops2));

    // Test Case 3: 2x5 grid with 5 crops of varying lengths
    vector<int> crops3 = {2, 3, 2, 1, 2};
    cout << "Test Case 3 (2x5 Grid):\n";
    printGrid(arrange_crops(2, 5, crops3));

    // Test Case 4: 5x2 grid with 3 crops
    vector<int> crops4 = {4, 3, 3};
    cout << "Test Case 4 (5x2 Grid):\n";
    printGrid(arrange_crops(5, 2, crops4));

    // Test Case 5: Edge case with a 1x5 grid (single row)
    vector<int> crops5 = {2, 2, 1};
    cout << "Test Case 5 (1x5 Grid):\n";
    printGrid(arrange_crops(1, 5, crops5));

    return 0;
}
