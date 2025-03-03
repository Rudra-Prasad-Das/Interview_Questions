#include <iostream>
#include <vector>

using namespace std;

// Function to get position in the "V" shaped array and the next index
pair<int, int> get_pos(const vector<int>& arr, int i, int lo, int hi) {
    int left_idx = i, right_idx = i;

    while (left_idx > lo) {
        left_idx--;
        if (arr[i] != arr[left_idx]) break;
    }

    while (right_idx < hi) {
        right_idx++;
        if (arr[i] != arr[right_idx]) break;
    }

    // -1 -> left-side of V
    // 0 -> bottom of V (plateau possible)
    // 1 -> right-side of V
    if (arr[left_idx] >= arr[i] && arr[i] > arr[right_idx]) {
        return {-1, right_idx};
    }
    if (arr[left_idx] < arr[i] && arr[i] <= arr[right_idx]) {
        return {1, left_idx};
    }
    return {0, -1};
}

// Function implementing the search around solution
int search_around_solution(const vector<int>& arr) {
    int lo = 0, hi = arr.size() - 1;

    while (lo <= hi) {
        int m = (lo + hi) / 2;
        auto [pos, next_idx] = get_pos(arr, m, lo, hi);

        if (pos == 0) {
            return arr[m];
        }
        if (pos == -1) {
            lo = next_idx;
        } else {
            hi = next_idx;
        }
    }
    return -1; // Should not reach here in a valid input case
}

// Example usage
int main() {
    vector<int> arr = {9, 7, 5, 3, 1, 2, 4, 6, 8};
    cout << "Minimum value: " << search_around_solution(arr) << endl;
    return 0;
}
