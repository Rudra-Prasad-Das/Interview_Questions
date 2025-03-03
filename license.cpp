#include <iostream>
#include <vector>
#include <string>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Base 26 Alphabet
const int BASE = ALPHABET.size(); // Base value (26)
const int PLATE_LENGTH = 10;

// Computes sequence range limits
vector<long long> computeSequenceRangeLimits() {
    vector<long long> sequence_limits(PLATE_LENGTH + 1, 0);
    for (int i = 0; i <= PLATE_LENGTH; i++) {
        sequence_limits[i] = pow(26, i) * pow(10, PLATE_LENGTH - i);
    }
    return sequence_limits;
}

// Convert a base-10 number to a base-26 string (padded with 'A' to required length)
string base10ToBase26(long long num, int length) {
    string result;
    
    while (num > 0) {
        int remainder = num % BASE;
        result = ALPHABET[remainder] + result; // Prepend character
        length--;
        num /= BASE;
    }

    // Pad with 'A' if needed
    return  result;
}

int main() {
    // Test the function with example values
    vector<long long> test_cases = {0, 1, 25, 26, 27, 703, 18278, 77936330}; // Edge cases and general values
    
    for (long long num : test_cases) {
        string result = base10ToBase26(num, PLATE_LENGTH);
        cout << "Base10: " << num << " -> Base26: " << result << endl;
    }

    return 0;
}
