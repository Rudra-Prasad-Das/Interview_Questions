#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Conversion table to map digits to their upside-down equivalents
unordered_map<int, char> conversion_table = {
    {0, 'o'}, {1, 'i'}, {2, 'z'}, {3, 'e'}, {4, 'h'},
    {5, 's'}, {6, 'g'}, {7, 'l'}, {8, 'b'}, {9, '9'}
};

// Function to turn a number upside down
string turn_upside_down(int number) {
    if (number == 0) {
        return string(1, conversion_table[0]);
    }

    string result = "";
    while (number != 0) {
        result += conversion_table[number % 10];
        number /= 10;
    }

    return result;
}

// Function to check if the upside-down version of a number contains any word from a list
bool contains_word(int number, const vector<string>& word_list) {
    string upside_down_str = turn_upside_down(number);

    for (const string& word : word_list) {
        if (upside_down_str.find(word) != string::npos) {
            return true;
        }
    }
    return false;
}

// Main function for testing
int main() {
    int num = 12345;
    vector<string> words = {"his", "egg", "lo"};

    cout << "Upside-down of " << num << " is: " << turn_upside_down(num) << endl;
    
    if (contains_word(num, words)) {
        cout << "The upside-down version contains a word from the list!" << endl;
    } else {
        cout << "No words found in the upside-down version." << endl;
    }

    return 0;
}
