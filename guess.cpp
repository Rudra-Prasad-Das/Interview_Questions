#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

// Function to compare two words and return (right_position_matches, wrong_position_matches)
std::pair<int, int> compare(const std::string &s, const std::string &t) {
    std::pair<int, int> result = {0, 0};

    if (s.size() != t.size()) {
        return result; // Invalid case
    }

    std::unordered_map<char, int> count_in_t;
    
    // Count occurrences of each character in string `t`
    for (char c : t) {
        count_in_t[c]++;
    }

    // Count exact matches (correct position)
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == t[i]) {
            result.first++; // Increase right_position_match_count
            count_in_t[s[i]]--;
        }
    }

    // Count wrong position matches
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i] && count_in_t[s[i]] > 0) {
            result.second++; // Increase wrong_position_match_count
            count_in_t[s[i]]--;
        }
    }

    return result;
}

// Function to simulate the system-provided guess function (for testing)
std::pair<int, int> guess(const std::string &s) {
    return compare(s, "boy"); // Assume "boy" is the secret word for testing
}

// Function to find the secret word from a list of words
std::string find_secret_word(std::vector<std::string> words) {
    while (!words.empty()) {
        if (words.size() == 1) {
            return words[0]; // Only one word left, it must be the answer
        }

        std::string guess_word = words[0]; // Pick the first word to guess
        std::pair<int, int> r = guess(guess_word);

        if (r.first == guess_word.size()) { 
            return guess_word; // Found the secret word
        }

        std::vector<std::string> filtered;
        
        // Keep only words that have the same (right, wrong) match pattern
        for (int i = 1; i < words.size(); i++) {
            if (compare(guess_word, words[i]) == r) {
                filtered.push_back(words[i]);
            }
        }
        
        words = filtered;
    }

    return ""; // This shouldn't happen: Secret word not found
}

int main() {
    // Test cases for compare function
    assert(compare("boy", "leo") == std::make_pair(0, 1));
    assert(compare("boy", "bye") == std::make_pair(1, 1));
    assert(compare("boy", "boy") == std::make_pair(3, 0));
    assert(compare("aaa", "abb") == std::make_pair(1, 0));
    assert(compare("aab", "bbb") == std::make_pair(1, 0));

    // Test cases for find_secret_word function
    assert(find_secret_word({"boy", "hot", "son", "soy", "leo", "bye"}) == "boy");
    assert(find_secret_word({"hot", "son", "soy", "leo", "bye", "boy"}) == "boy");
    assert(find_secret_word({"leo", "hot", "son", "soy", "bye", "boy"}) == "boy");

    std::cout << "All test cases passed!\n";
    return 0;
}
