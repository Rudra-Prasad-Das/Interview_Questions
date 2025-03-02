#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

typedef vector<string> State;
map<State, int> position_to_result;

// Function to move stacks[i] on top of stacks[j]
vector<string> move(const State &stacks, int i, int j) {
    if (i == j) return {};
    if (stacks[i].size() != stacks[j].size() && stacks[i][0] != stacks[j][0]) return {};
    
    vector<string> new_stacks = stacks;
    new_stacks[i] += string(new_stacks[j].size(), '-'); // Forget tiles below the top
    new_stacks.erase(new_stacks.begin() + j);
    // cout<<"Old_state\n";
    // for(auto s: stacks)cout<<s<<" ";
    // cout<<"\n";
    // cout<<"New State\n";
    // for(auto s : new_stacks)cout<<s<<" ";
    // cout<<"\n";
    sort(new_stacks.begin(), new_stacks.end()); // Canonical representation
    return new_stacks;
}

// Recursive function to determine the winner
int who_wins(State current) {
    if (position_to_result.count(current)) return position_to_result[current];
    
    int winner = 1; // If no moves, the player to play has lost.
    
    for (int i = 0; i < current.size(); ++i) {
        for (int j = 0; j < current.size(); ++j) {
            if (i == j) continue;
            vector<string> next = move(current, i, j);
            if (!next.empty() && who_wins(next) == 1) {
                winner = 0;
                break;
            }
        }
    }
    
    position_to_result[current] = winner;
    return winner;
}

int main() {
    State start_position = {"a", "a", "a", "b", "b", "b", "c", "c", "c", "d", "d", "d"};
    int result = who_wins(start_position);
    cout << "Winner: " << (result == 0 ? "First Player" : "Second Player") << endl;
    return 0;
}
