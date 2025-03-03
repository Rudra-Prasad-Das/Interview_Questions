//     Warm Up   
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef pair<int, int> Tire;

int calculateFastestTimeWarmup(int n, const vector<Tire>& tires) {
    int min_time = INT_MAX;
    
    for (const auto& [t, f] : tires) {
        int total_time = 0;
        int lap_time = t;
        
        for (int i = 0; i < n; ++i) {
            total_time += lap_time;
            lap_time *= f;
        }
        
        min_time = min(min_time, total_time);
    }
    
    return min_time;
}

int main() {
    vector<Tire> tires = {{2, 2}, {3, 3}};  //ans =  2 + 2*f +2*f^2
    int n = 2;
    cout << "Minimum race time: " << calculateFastestTimeWarmup(n, tires) << endl;
    return 0;
}

// Main Problem : 

double calculateFastestTime(int n, const vector<pair<int, double>>& tires, int p) {
    vector<double> dp(n + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 laps take 0 time
    
    for (const auto& [t, f] : tires) {
        double stintTime = 0;
        double lapTime = t;
        for (int laps = 1; laps <= n; ++laps) {
            stintTime += lapTime;
            dp[laps] = min(dp[laps], stintTime);
            lapTime *= f;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int laps = 1; laps <= ceil((i + 1) / 2); ++laps) {
            if (i - laps >= 0) {
                dp[i] = min(dp[i], dp[i - laps] + p + dp[laps]);
            }
        }
    }
    
    return dp[n];
}

int main() {
    int n = 5;
    vector<pair<int, double>> tires = {{2, 1.5}, {3, 1.2}};
    int p = 4;
    
    cout << "Minimum race time: " << calculateFastestTime(n, tires, p) << endl;
    return 0;
}

// Recursive Code.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <limits>

using namespace std;

struct Tire {
    int t; // Initial lap time
    int f; // Degradation factor
};

// Memoization map: stores the minimum time required for `n` laps
unordered_map<int, double> memo;

// Recursive function to calculate the minimum race time
double calculateMinTime(int laps, const vector<Tire>& tires, int pitStopCost) {
    // Base case: No laps remaining
    if (laps == 0) return 0;
    
    // Check if result is already computed
    if (memo.find(laps) != memo.end()) return memo[laps];

    double min_time = numeric_limits<double>::infinity();

    // Try each tire compound
    for (const auto& tire : tires) {
        double stint_time = 0;
        double lap_time = tire.t;

        // Simulate laps using the same tire
        for (int i = 1; i <= laps; i++) {
            stint_time += lap_time;

            // Recursively check the minimum time for remaining laps after a pit stop
            double total_time = stint_time + pitStopCost + calculateMinTime(laps - i, tires, pitStopCost);
            min_time = min(min_time, total_time);

            // Tire degradation
            lap_time *= tire.f;
        }
    }

    // Store the result in memoization map and return it
    return memo[laps] = min_time;
}

int main() {
    int n = 10;  // Total number of laps
    vector<Tire> tires = {{2, 2}, {3, 3}};  // {initial lap time, degradation factor}
    int pitStopCost = 5;

    // Compute and print the minimum race time
    cout << "Minimum race time: " << calculateMinTime(n, tires, pitStopCost) << endl;

    return 0;
}


