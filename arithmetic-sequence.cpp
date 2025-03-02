#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class Interview {
public:
    static int solve_dp(vector<int>& nums) {
        int res = 0;
        int trend_length = 0; // length of a trend (a good subarray) ending with
                              // the previous number
        int prev_sum =
            0; // sum of sums of good subarrays ending with the previous number
        int prev_delta = 0; // the common difference of the trend ending with
                            // the previous number
        int prev_num = 0;   // the previous number

        for (const int num : nums) {
            const int delta = num - prev_num;
            if (delta == 1 || delta == -1) {
                if (delta == prev_delta ||
                    prev_delta == 0) { // matching previous trend
                    ++trend_length;
                    prev_sum += num * trend_length; // key optimization
                } else { // does not match and starting a reversal trend
                    trend_length = 2;
                    prev_sum = prev_num + num * trend_length;
                }
                prev_delta = delta;
            } else {
                trend_length = 1;
                prev_sum = num;
                prev_delta = 0; // wildcard that can be matched for +1 or -1
            }
            res += prev_sum;
            prev_num = num;
        }
        return res;
    }
};

// Function to run test cases
void run_tests() {
    // Test Case 1: Simple Increasing Sequence
    vector<int> nums = {1,2,3};
    cout<<Interview::solve_dp(nums)<<"\n";
    nums = {5,4,3};
    cout<<Interview::solve_dp(nums)<<"\n";
}

// Main function
int main() {
    run_tests();
    cout << "All tests passed successfully!\n";
    return 0;
}
