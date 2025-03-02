#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Define a type for debris as a vector of {id, cost, risk}
using Debris = std::vector<int>;  // {id, cost, risk}

// Comparator function for sorting debris
bool compareDebris(const Debris& a, const Debris& b) {
    return (a[1] < b[1]) || (a[1] == b[1] && a[2] > b[2]);  
}

// Function to find the median debris based on cost
Debris selectMedian(std::vector<Debris>& debris_list) {
    size_t mid = debris_list.size() / 2;
    std::nth_element(debris_list.begin(), debris_list.begin() + mid, debris_list.end(), compareDebris);
    return debris_list[mid];
}

// Function to select debris within the budget
std::vector<Debris> selectDebrisWithinBudget(std::vector<Debris>& debris_list, int budget) {
    if (debris_list.empty() || budget <= 0) return {}; 

    // Step 1: Find median
    Debris median_debris = selectMedian(debris_list);

    // Step 2: Partition debris
    std::vector<Debris> below_median, at_median, above_median;
    for (const auto& debris : debris_list) {
        if (compareDebris(debris, median_debris)) {
            below_median.push_back(debris);
        } else if (debris[1] == median_debris[1] && debris[2] == median_debris[2]) {
            at_median.push_back(debris);
        } else {
            above_median.push_back(debris);
        }
    }

    // Step 3: Check cost of debris below median
    int cost_below = std::accumulate(below_median.begin(), below_median.end(), 0, 
                                     [](int sum, const Debris& d) { return sum + d[1]; });

    if (cost_below > budget) {
        return selectDebrisWithinBudget(below_median, budget);
    }

    // Step 4: Allocate budget to at_median debris
    int remaining_budget = budget - cost_below;
    int cost_at_median = at_median.size() * median_debris[1];

    if (cost_at_median < remaining_budget) {
        remaining_budget -= cost_at_median;
        std::vector<Debris> result = below_median;
        result.insert(result.end(), at_median.begin(), at_median.end());
        std::vector<Debris> above_result = selectDebrisWithinBudget(above_median, remaining_budget);
        result.insert(result.end(), above_result.begin(), above_result.end());
        return result;
    }

    // Step 5: Select some at_median debris
    int select_n = remaining_budget / median_debris[1];
    std::vector<Debris> result = below_median;
    result.insert(result.end(), at_median.begin(), at_median.begin() + select_n);
    return result;
}

int main() {
    std::vector<Debris> debris_list = {
        {1, 50, 3}, {2, 30, 2}, {3, 20, 1}, {4, 10, 3}, {5, 40, 2},
        {6, 60, 1}, {7, 70, 3}, {8, 90, 2}
    };
    int budget = 120;

    std::vector<Debris> selected = selectDebrisWithinBudget(debris_list, budget);

    std::cout << "Selected Debris (ID, Cost, Risk Level):\n";
    for (const auto& debris : selected) {
        std::cout << debris[0] << " | " << debris[1] << " | " << debris[2] << '\n';
    }
    return 0;
}
