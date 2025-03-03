#include <iostream>
#include <vector>

using namespace std;

// Function to print the combination
int num = 1;
void emitCombination(const vector<int>& combination, int combinationLength) {
    cout<<"# "<<num++<<" ";
    for (int i = 0; i < combinationLength; i++) {
        for (int j = 0; j < 5; j++) {
            if ((combination[i] >> j) & 1) {
                cout << (j + 1);
            }
        }
        cout << '-';
    }
    cout << endl;
}

// Recursive function to generate combinations
void generateCombinations(int usedBits, vector<int>& combination, int combinationLength) {
    emitCombination(combination, combinationLength);

    // If all keys are pressed (bitmask 11111), return
    if (usedBits == (1 << 5) - 1) {
        return;
    }

    // Try all possible key presses
    for (int press = 1; press < (1 << 5); press++) {
        // Ensure no key is pressed twice
        if ((usedBits & press) == 0) {
            combination[combinationLength] = press;
            generateCombinations(usedBits | press, combination, combinationLength + 1);
        }
    }
}

// Main function
int main() {
    vector<int> combination(5, 0); // Equivalent to new int[5] in Java
    generateCombinations(0, combination, 0);
    return 0;
}
