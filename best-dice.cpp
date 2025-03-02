#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function to find the best dice with the most wins
int findBestDiceOptimal(const vector<vector<int>>& dices) {
    int num_dices = dices.size();

    // Min-heap to process dice faces in sorted order
    auto compare = [&dices](const pair<int, int>& a, const pair<int, int>& b) {
        return dices[a.first][a.second] > dices[b.first][b.second];
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);

    // Initialize heap with the first face of each dice
    for (int i = 0; i < num_dices; ++i) {
        minHeap.push({i, 0});
    }

    vector<int> wins_for_dice(num_dices, 0);
    vector<int> faces_seen(num_dices, 0);
    int total_faces_seen = 0;

    while (!minHeap.empty()) {
        vector<pair<int, int>> ties;
        
        // Process the first item in the heap
        pair<int, int> first = minHeap.top();
        cout<<first.first<<" "<<first.second<<"\n";
        cout<<dices[first.first][first.second]<<"<===\n";
        ties.push_back(first);
        minHeap.pop();

        if (first.second + 1 < dices[first.first].size()) {
            minHeap.push({first.first, first.second + 1});
        }

        // Collect all tied dice faces
        while (!minHeap.empty() &&
               dices[minHeap.top().first][minHeap.top().second] ==
               dices[first.first][first.second]) {
            pair<int, int> he = minHeap.top();
            cout<<he.first<<" "<<he.second<<"\n";
            cout<<dices[he.first][he.second]<<"<---\n";
            minHeap.pop();
            ties.push_back(he);

            if (he.second + 1 < dices[he.first].size()) {
                minHeap.push({he.first, he.second + 1});
            }
        }

        // Count wins for each dice in the tie
        for (const auto& he : ties) {
            wins_for_dice[he.first] += total_faces_seen - faces_seen[he.first];
        }

        // Update the count of faces seen
        for (const auto& he : ties) {
            ++total_faces_seen;
            ++faces_seen[he.first];
        }
    }

    // Find the dice with the most wins
    int best_dice = 0;
    for (int i = 0; i < num_dices; ++i) {
        if (wins_for_dice[i] > wins_for_dice[best_dice]) {
            best_dice = i;
        }
    }

    return best_dice;
}

int main() {
    vector<vector<int>> dices = {
        {1, 2, 3, 4, 5, 6},
        {2, 3, 4, 5, 6, 7},
        {1, 1, 2, 2, 3, 3}
    };

    int bestDice = findBestDiceOptimal(dices);
    cout << "The best dice is: " << bestDice << endl;

    return 0;
}
