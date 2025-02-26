/*
You and a friend have received a special gold chain as a gift. The chain links each have an
integer weight, not necessarily the same. You and your friend must choose one of the links to be
removed and provided to charity, after which the chain will be reconnected. After that, you can
choose one place along the chain to split it in two, such that it creates two equally-weighted
sections for you and your friend to take home. For a given input chain (list of link weights),
determine if a solution is possible.

Q1 Does a split exist
Q2 If yes what is the split
Q3 min deletions to reach the split

*/

#include<bits/stdc++.h>
using namespace std;

bool canDeleteAndSplit(vector<int>& lst) {
    unordered_set<int> values;
    int totalSum = 0;
    
    for (int num : lst) totalSum += num; // Calculate total sum

    // Traversal from the left
    int leftSum = lst[0];
    int rightSum = totalSum - leftSum;
    values.insert(leftSum);

    for (int i = 1; i < lst.size() - 1; i++) {
        values.insert(lst[i]);
        leftSum += lst[i];
        rightSum -= lst[i];
        if (values.count(leftSum - rightSum)) {
            return true;
        }
    }

    // Traversal from the right
    rightSum = lst.back();
    leftSum = totalSum - rightSum;
    values.clear();
    values.insert(rightSum);

    for (int i = lst.size() - 2; i > 0; i--) {
        values.insert(lst[i]);
        rightSum += lst[i];
        leftSum -= lst[i];
        if (values.count(rightSum - leftSum)) {
            return true;
        }
    }

    return false;
}
// main for Q1
/*
int main() {
    vector<vector<int>> testCases = {
        {2, 3, 4, 5, 6}, 
        {1, 1, 1, 1, 2}, 
        {3, 7, 5, 1}, 
        {10, 10, 10, 10, 10, 10, 10}, 
        {5, 5, 5, 5, 5, 5, 4}
    };

    for (auto& testCase : testCases) {
        cout << "Input: ";
        for (int num : testCase) cout << num << " ";
        cout << "\nSolution Exists? " << (canDeleteAndSplit(testCase) ? "YES" : "NO") << "\n\n";
    }

    return 0;
}
*/

vector<pair<int, vector<int>>> pointAndValuesToDeleteForEvenSplit(vector<int>& lst) {
    unordered_map<int, vector<int>> values;
    int totalSum = 0;
    vector<pair<int, vector<int>>> result;

    for (int num : lst) totalSum += num; // Calculate total sum

    // Traversal from the left
    int leftSum = lst[0];
    int rightSum = totalSum - leftSum;
    values[leftSum] = {0};

    for (int i = 1; i < lst.size() - 1; i++) {
        values[lst[i]].push_back(i);
        leftSum += lst[i];
        rightSum -= lst[i];
        int diff = leftSum - rightSum;
        
        if (values.find(diff) != values.end()) {
            result.push_back({i, values[diff]});
        }
    }

    // Traversal from the right
    rightSum = lst.back();
    leftSum = totalSum - rightSum;
    values.clear();
    values[rightSum] = {(int)lst.size() - 1};

    for (int i = lst.size() - 2; i > 0; i--) {
        values[lst[i]].push_back(i);
        rightSum += lst[i];
        leftSum -= lst[i];
        int diff = rightSum - leftSum;

        if (values.find(diff) != values.end()) {
            result.push_back({i, values[diff]});
        }
    }

    return result;
}
// main for Q3
/*
int main() {
    vector<vector<int>> testCases = {
        {2, 3, 4, 5, 6}, 
        {1, 1, 1, 1, 2}, 
        {3, 7, 5, 1}, 
        {10, 10, 10, 10, 10, 10, 10}, 
        {5, 5, 5, 5, 5, 5, 4}
    };

    for (auto& testCase : testCases) {
        cout << "Input: ";
        for (int num : testCase) cout << num << " ";
        cout << "\nResults: ";
        
        auto result = pointAndValuesToDeleteForEvenSplit(testCase);
        if (result.empty()) {
            cout << "No valid split found.\n\n";
        } else {
            for (auto& [index, valuesToDelete] : result) {
                cout << "\nSplit at index " << index << ", delete values: ";
                for (int v : valuesToDelete) cout << v << " ";
            }
            cout << "\n\n";
        }
    }

    return 0;
}
*/
int minRemovalsForEquallyWeightedChains(vector<int>& lst) {
    unordered_map<int, int> diffs;
    diffs[0] = 0; // Initial state

    for (int e : lst) {
        unordered_map<int, int> newDiffs = diffs; // Copy current state

        for (const auto& [d, count] : diffs) {
            int l = d + e;
            int r = abs(d - e);

            newDiffs[l] = max(newDiffs.count(l) ? newDiffs[l] : 0, count + 1);
            newDiffs[r] = max(newDiffs.count(r) ? newDiffs[r] : 0, count + 1);
        }

        diffs = newDiffs; // Update diffs map
    }

    return lst.size() - diffs[0]; // Minimum removals
}

int main() {
    vector<vector<int>> testCases = {
        {2, 3, 4, 5, 6}, 
        {1, 1, 1, 1, 2}, 
        {3, 7, 5, 1}, 
        {10, 10, 10, 10, 10, 10, 10}, 
        {5, 5, 5, 5, 5, 5, 4}
    };

    for (auto& testCase : testCases) {
        cout << "Input: ";
        for (int num : testCase) cout << num << " ";
        cout << "\nMinimum Removals: " << minRemovalsForEquallyWeightedChains(testCase) << "\n\n";
    }

    return 0;
}
