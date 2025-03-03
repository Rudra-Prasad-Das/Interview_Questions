#include <iostream>
#include <string>

using namespace std;

void handle_num(int remove_length, int &remaining_length, int &opened, int &closed, int &excess_closed, int &closes_incoming) {
    remaining_length -= remove_length;

    // Remove excess closed parentheses
    int excess_closed_removed = min(excess_closed, remove_length);
    excess_closed -= excess_closed_removed;
    remove_length -= excess_closed_removed;

    // Remove excess opened parentheses
    if (opened - closed > closes_incoming) {
        int excess_opened = (opened - closed) - closes_incoming;
        int excess_opened_removed = min(excess_opened, remove_length);
        opened -= excess_opened_removed;
        remove_length -= excess_opened_removed;
    }

    // Remove matched pairs
    int pairs_removed = min(closed, remove_length / 2);
    closed -= pairs_removed;
    opened -= pairs_removed;
    remove_length -= pairs_removed * 2;

    // Remove closed parentheses
    int closed_removed = min(closed, remove_length);
    closed -= closed_removed;
    remove_length -= closed_removed;

    // Remove opened parentheses as a last resort
    int opened_removed = min(opened, remove_length);
    opened -= opened_removed;
    remove_length -= opened_removed;
}

bool soln(const string &s) {
    int remaining_length = 0, opened = 0, closed = 0, excess_closed = 0;
    int closes_incoming = count(s.begin(), s.end(), ')');

    for (char x : s) {
        if (x == '(') {
            opened++;
            remaining_length++;
        } else if (x == ')') {
            if (closed == opened) {
                excess_closed++;
            } else {
                closed++;
            }
            closes_incoming--;
            remaining_length++;
        } else {
            int remove_length = x - '0';  // Convert character to integer
            if (remove_length > remaining_length) {
                return false;
            }
            handle_num(remove_length, remaining_length, opened, closed, excess_closed, closes_incoming);
        }
    }
    return opened == closed && excess_closed == 0;
}

// Example usage
int main() {
    vector<pair<string, bool>> test_cases = {
        {"", true}, {"()", true}, {"(())", true}, {"()()", true}, {")(", false}, 
        {"()(", false}, {")()", false}, {")", false}, {"(", false}, {"())()", false}, 
        {"()(()", false}, {"(()", false}, {"())", false}, {"1", false}, {"()2", true}, 
        {"()1", false}, {"(1)", false}, {"1()", false}, {"(())4", true}, {"(()2)", true}, 
        {"(1())1", true}, {"(())1", false}, {"(()1)", false}, {"((1))", false}, {"(1())", false}, 
        {"1(())", false}, {"((11))", false}, {"()()2", true}, {"()()1", false}, {")1(", false}, 
        {"()(1", true}, {")1()", true}, {")1", true}, {"1(", false}, {"(5", false}, 
        {"())1()", true}, {"()(6()", false}, {"(()3", true}, {"()2)", false}, {"(()1(1))", true}, 
        {"(1())1", true}, {"(1)()(((3", false}, {"0", true}, {"()0", true}, {")0", false}, 
        {"((2))", false}, {"((((2))2", true}, {"))))))6()(()1(1))", true}, {"((2)1)", false}
    };

    int num = 1;
    for (auto &tc : test_cases) {
        cout << "#TC " << num++ << " ";
        if (soln(tc.first) == tc.second)
            cout << "Passed\n";
        else
            cout << "Failed XXXXXXXXXXXX\n";
    }
    return 0;
}
