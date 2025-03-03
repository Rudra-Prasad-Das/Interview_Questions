#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;

struct Cake {
    double x, y, side;
};

double solve(const vector<Cake>& cakes) {
    vector<pair<double, double>> y_to_change;
    double total_area = 0;

    y_to_change.reserve(cakes.size() * 2);
    for (const auto& cake : cakes) {
        y_to_change.emplace_back(cake.y, cake.side);
        y_to_change.emplace_back(cake.y + cake.side, -cake.side);
        total_area += cake.side * cake.side;
    }

    double target_area = total_area / 2;
    if (target_area == 0) return 0;

    sort(y_to_change.begin(), y_to_change.end());

    double previous_area = 0, current_derivative = 0, previous_y = 0;
    
    for (const auto& [current_y, derivative_change] : y_to_change) {
        double new_area = previous_area + current_derivative * (current_y - previous_y);
        
        if (target_area <= new_area) {
            return previous_y + (target_area - previous_area) / current_derivative;
        }

        current_derivative += derivative_change;
        previous_area = new_area;
        previous_y = current_y;
    }

    exit(1); // Should never happen
}

int main() {
    vector<vector<Cake>> test_cases = {
        {{0, 0, 4}, {1, 1, 2}},       // Multiple cakes with different sizes
        {{0, 0, 5}},                  // Single cake
        {{0, 0, 3}, {0, 3, 3}},       // Stacked cakes
        {},                            // No cakes
        {{0, 0, 2}, {1, 1, 2}, {2, 2, 2}} // Non-overlapping cakes
    };

    for (int i = 0; i < test_cases.size(); i++) {
        cout << "Test Case " << i + 1 << ": ";
        double result = solve(test_cases[i]);
        cout << fixed << setprecision(6) << result << endl;
    }

    return 0;
}
