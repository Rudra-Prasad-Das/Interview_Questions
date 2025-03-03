#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int follow_up_question_solution_1(vector<queue<int>>& arrays) {
    int min_sum = numeric_limits<int>::max();
    vector<int> partial_sums(arrays.size(), 0);
    vector<bool> done(arrays.size(), false);
    int num_done = 0; // Number of `true` elements in `done`

    while (num_done < arrays.size()) {
        for (size_t i = 0; i < arrays.size(); i++) {
            if (done[i]) continue;

            if (arrays[i].empty()) {
                min_sum = min(min_sum, partial_sums[i]);
                if (partial_sums[i] >= min_sum) {
                    done[i] = true;
                    num_done++;
                }
                continue;
            }

            partial_sums[i] += arrays[i].front();
            arrays[i].pop();
        }
    }
    return min_sum;
}

// Example usage
int main() {
    vector<queue<int>> arrays = {
        queue<int>({3, 1, 4}),
        queue<int>({2, 5}),
        queue<int>({6, 7, 8})
    };

    int result = follow_up_question_solution_1(arrays);
    cout << "Minimum sum: " << result << endl;

    return 0;
}
