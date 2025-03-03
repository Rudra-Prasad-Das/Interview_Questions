#include <iostream>
#include <vector>

using namespace std;

vector<uint16_t> precomputed_prefixes; // Stores cumulative runtimes

// Precompute prefix sums for efficient range sum calculation
void precomputePrefixes(const vector<uint16_t>& runtimes) {
    if (runtimes.empty()) return;

    precomputed_prefixes.resize(runtimes.size());
    precomputed_prefixes[0] = runtimes[0];

    for (size_t i = 1; i < runtimes.size(); ++i) {
        precomputed_prefixes[i] = precomputed_prefixes[i - 1] + runtimes[i];
    }
}

// Checks if the sum of runtimes within [start_chain, end_chain] satisfies time_limit
bool isTimeLimitSatisfied(size_t start_chain, size_t end_chain, uint16_t time_limit) {
    if (end_chain >= precomputed_prefixes.size() || time_limit == 0) {
        return false;
    }

    uint16_t runtime_sum = precomputed_prefixes[end_chain];
    if (start_chain > 0) {
        runtime_sum -= precomputed_prefixes[start_chain - 1];
    }

    return runtime_sum <= time_limit;
}

// Test function to verify correctness
void runTests() {
    vector<uint16_t> runtimes = {3, 5, 2, 8, 6, 4}; // Example runtimes
    precomputePrefixes(runtimes);

    vector<tuple<size_t, size_t, uint16_t, bool>> test_cases = {
        {0, 2, 10, true},  // 3 + 5 + 2 = 10 (within limit)
        {1, 4, 20, true},  // 5 + 2 + 8 + 6 = 21 (exceeds limit)
        {2, 5, 12, true},  // 2 + 8 + 6 + 4 = 20 (exceeds limit)
        {0, 5, 25, false}, // Entire range sum is too large
        {3, 4, 10, true},  // 8 + 6 = 14 (exceeds limit)
    };

    for (const auto& [start, end, limit, expected] : test_cases) {
        bool result = isTimeLimitSatisfied(start, end, limit);
        cout << "Range [" << start << ", " << end << "] with limit " << limit 
             << " -> Expected: " << (expected ? "true" : "false") 
             << ", Got: " << (result ? "true" : "false") << endl;
    }
}

int main() {
    runTests();
    return 0;
}
