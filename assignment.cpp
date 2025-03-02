/*
*/
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

void assign_gifts(const vector<string>& participants, const vector<string>& gifts) {
    deque<string> ppts(participants.begin(), participants.end());

    for (size_t i = 0; i < participants.size(); ++i) {
        string recipient = ppts.front();
        ppts.pop_front();

        // Print recipient's name in uppercase
        // transform(recipient.begin(), recipient.end(), recipient.begin(), ::toupper);
        cout << recipient << " RECEIVES: " << endl;

        // Print gift assignments
        vector<pair<string, string>> assignments;
        for (size_t j = 0; j < gifts.size() && j < ppts.size(); ++j) {
            assignments.emplace_back(gifts[j], ppts[j]);
        }

        for (const auto& pair : assignments) {
            cout << "(" << pair.first << ", " << pair.second << ") ";
        }
        cout << endl;

        // Rotate the queue
        ppts.push_back(recipient);
        cout << "\n";
    }
}

int main() {
    vector<string> participants = {"Alice", "Bob", "Charlie"};
    vector<string> gifts = {"Book", "Watch"};

    assign_gifts(participants, gifts);

    return 0;
}
