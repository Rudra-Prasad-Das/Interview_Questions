#include <iostream>
#include <vector>

using namespace std;

bool reverse_helper(vector<int>& dp, vector<int>& res, size_t i) {
    if (i >= dp.size()) {
        return true; // Base case: successfully reached the end
    }
    if (dp[i] == 1) {
        int coin = i;
        res.push_back(coin);
        for (size_t j = dp.size() - 1; j >= coin; j--) {
            dp[j] -= dp[j - coin];
        }
    }
    if (dp[i] != 0) {
        return false; // Invalid case
    }
    return reverse_helper(dp, res, i + 1);
}

vector<int> reverse_coin_change_deconstruct(vector<int> dp) {
    vector<int> res;
    if (reverse_helper(dp, res, 1)) {
        return res;
    }
    return {}; // Return empty vector if not valid
}

int main() {
    vector<vector<int>> test_cases = {
        {1, 1, 1, 1, 1},      // Expected: {1}
        {1, 0, 1, 0, 1, 1, 2, 1, 2, 1, 3}, // Expected: {2, 5, 6}
        {1, 1, 2, 3, 5},      // Expected: {1, 2, 3, 4}
        {1, 1, 1, 3, 2}       // Expected: {}
    };

    for (const auto& test : test_cases) {
        vector<int> result = reverse_coin_change_deconstruct(test);
        if (result.empty()) {
            cout << "None" << endl;
        } else {
            for (int coin : result) {
                cout << coin << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
