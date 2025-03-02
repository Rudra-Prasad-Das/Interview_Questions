#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
using namespace std;

pair<int, int> restricted_soln(const vector<int>& arr) {
    if (arr.empty()) return {-1, -1};
    
    int n = arr.size();
    vector<int> prefix_sum(n, 0);
    unordered_map<int, vector<int>> elem_to_indices;
    int res_tail = 0, res_head = 0;
    int res_sum = numeric_limits<int>::min();
    int running_sum = 0;
    
    for (int i = 0; i < n; ++i) {
        running_sum += arr[i];
        prefix_sum[i] = running_sum;
        elem_to_indices[arr[i]].push_back(i);
    }
    
    auto _helper = [&](const vector<int>& indices) {
        int cur_tail = indices[0], res_tail = indices[0], res_head = indices[0];
        int max_sum = arr[indices[0]];
        
        for (size_t i = 1; i < indices.size(); ++i) {
            int cur_sum = prefix_sum[indices[i]] - prefix_sum[cur_tail] + arr[cur_tail];
            
            if (cur_sum > arr[indices[0]]) {
                if (cur_sum > max_sum) {
                    res_tail = cur_tail;
                    res_head = indices[i];
                    max_sum = cur_sum;
                }
            } else {
                cur_tail = indices[i];
            }
        }
        return make_tuple(res_tail, res_head, max_sum);
    };
    
    for (const auto& entry : elem_to_indices) {
        auto [indices_tail, indices_head, indices_sum] = _helper(entry.second);
        if (indices_sum > res_sum) {
            res_tail = indices_tail;
            res_head = indices_head;
            res_sum = indices_sum;
        }
    }
    
    return {res_tail, res_head};
}

int main() {
    vector<int> arr = {1, -2, 3, 1, -1, 3, 2};
    auto [start, end] = restricted_soln(arr);
    cout << "Subarray start index: " << start << ", end index: " << end << endl;
    return 0;
}
