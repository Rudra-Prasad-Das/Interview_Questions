#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<int>> dp;
vector<int> block_colors;

// Recursive function to compute max beauty
int getMaxBeauty(int color_index, int repaint_count, int n) {
    if (repaint_count > n) return 0; // Base case: Invalid repaint count
    if (dp[color_index][repaint_count] != -1) return dp[color_index][repaint_count]; // Memoization

    int max_beauty = 0, current_repaint = 0;

    for (int block_i = 0; block_i < n; ++block_i) {
        current_repaint = 0;
        for (int block_j = block_i; block_j < n; ++block_j) {
            if (block_colors[block_j] != color_index) ++current_repaint;
            if (current_repaint > repaint_count) break;
            max_beauty = max(max_beauty, block_j - block_i + 1);
        }
    }

    return dp[color_index][repaint_count] = max_beauty;
}

// Main function to compute beauty values
vector<int> GetMaximumBeautyValues(int n, int k, const vector<int>& m,
                                   const vector<int>& favorite_colors, const vector<int>& blocks) {
    block_colors = blocks;
    dp.assign(k + 1, vector<int>(n + 1, -1)); // Initialize DP table

    vector<int> beauty_values;
    for (int query_i = 0; query_i < m.size(); ++query_i) {
        int color = favorite_colors[query_i];
        int repaint = m[query_i];
        beauty_values.push_back(getMaxBeauty(color, repaint, n));
    }
    
    return beauty_values;
}

// Test function
void test() {
    int n = 5, k = 3;
    vector<int> m = {1, 2}; 
    vector<int> favorite_colors = {0, 1};
    vector<int> block_colors = {0, 1, 0, 2, 1};

    vector<int> result = GetMaximumBeautyValues(n, k, m, favorite_colors, block_colors);
    for (int val : result) cout << val << " ";
}

int main() {
    test();
    return 0;
}
