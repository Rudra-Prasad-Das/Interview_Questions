#include <iostream>
#include <vector>
#include <algorithm>

class Debris {
public:
    int id;
    int estimated_cost;
    
    Debris(int id, int cost) : id(id), estimated_cost(cost) {}
};

// Function to select the median value (using nth_element for linear time selection)
int SelectMedian(std::vector<int>& costs) {
    size_t median_index = costs.size() / 2;
    std::nth_element(costs.begin(), costs.begin() + median_index, costs.end());
    return costs[median_index];
}

std::vector<Debris> SelectDebrisWithinBudget(std::vector<Debris>& debris_list, int budget) {
    if (debris_list.empty()) return {};
    
    std::vector<int> costs;
    for (const auto& debris : debris_list) {
        costs.push_back(debris.estimated_cost);
    }
    
    int median_cost = SelectMedian(costs);
    
    std::vector<Debris> below_median, at_median, above_median;
    for (const auto& debris : debris_list) {
        if (debris.estimated_cost < median_cost) {
            below_median.push_back(debris);
        } else if (debris.estimated_cost > median_cost) {
            above_median.push_back(debris);
        } else {
            at_median.push_back(debris);
        }
    }
    
    int sum_cost_below = 0;
    for (const auto& debris : below_median) {
        sum_cost_below += debris.estimated_cost;
    }
    
    if (sum_cost_below > budget) {
        return SelectDebrisWithinBudget(below_median, budget);
    }
    
    int budget_remain = budget - sum_cost_below;
    int sum_cost_at_median = at_median.size() * median_cost;
    
    if (sum_cost_at_median < budget_remain) {
        budget_remain -= sum_cost_at_median;
        std::vector<Debris> result = below_median;
        result.insert(result.end(), at_median.begin(), at_median.end());
        std::vector<Debris> above_result = SelectDebrisWithinBudget(above_median, budget_remain);
        result.insert(result.end(), above_result.begin(), above_result.end());
        return result;
    }
    
    int select_n_from_at_median = budget_remain / median_cost;
    std::vector<Debris> result = below_median;
    result.insert(result.end(), at_median.begin(), at_median.begin() + select_n_from_at_median);
    return result;
}

int main() {
    std::vector<Debris> debris_list = {
        {1, 100}, {2, 200}, {3, 150}, {4, 80}, {5, 120}, {6, 90}, {7, 250}, {8, 60}
    };
    int budget = 500;
    
    std::vector<Debris> selected_debris = SelectDebrisWithinBudget(debris_list, budget);
    
    std::cout << "Selected Debris within Budget:\n";
    for (const auto& debris : selected_debris) {
        std::cout << "ID: " << debris.id << " | Cost: " << debris.estimated_cost << "\n";
    }
    
    return 0;
}
