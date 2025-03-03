#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class WordPredictor {
public:
    // Constructor that processes input data
    WordPredictor(const std::vector<std::vector<std::string>>& data) {
        std::unordered_map<std::string, std::unordered_map<std::string, int>> counts;
        
        // Count occurrences of word pairs
        for (const auto& sentence : data) {
            for (size_t i = 0; i < sentence.size() - 1; ++i) { // Prevent out-of-bounds access
                ++counts[sentence[i]][sentence[i + 1]];
            }
        }

        // Determine the most frequent next word for each word
        for (const auto& [word, next_words] : counts) {
            predicted_next_word[word] = std::max_element(
                next_words.begin(), next_words.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; }
            )->first;
        }
    }

    // Predicts the next word based on past occurrences
    std::string predict(const std::string& word) const {
        auto result = predicted_next_word.find(word);
        return (result == predicted_next_word.end()) ? "" : result->second;
    }

private:
    std::unordered_map<std::string, std::string> predicted_next_word;
};

// Test the WordPredictor class
int main() {
    // Sample training data (sentences)
    std::vector<std::vector<std::string>> data = {
        {"hello", "world"},
        {"hello", "there"},
        {"hello", "world"},
        {"good", "morning"},
        {"good", "evening"},
        {"good", "morning"}
    };

    // Create predictor from data
    WordPredictor predictor(data);

    // Test predictions
    std::cout << "Prediction for 'hello': " << predictor.predict("hello") << "\n";  // Expected: "world"
    std::cout << "Prediction for 'good': " << predictor.predict("good") << "\n";    // Expected: "morning"
    std::cout << "Prediction for 'morning': " << predictor.predict("morning") << "\n";  // Expected: ""

    return 0;
}
