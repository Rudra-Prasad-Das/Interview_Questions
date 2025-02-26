/*
You are given a list of domain names and an integer "score" for each of them.
A domain is a "leaf" if it doesn't have any child domains in the input.
A leaf domain's "total score" is the sum of the scores of itself and all its ancestor domains.
Write a program that, given a list
*/
void calculateTotalScores(const string& domain, int score, 
                          unordered_map<string, unordered_set<string>>& tree, 
                          unordered_map<string, int>& scores) {
    // If the domain has no subdomains, print its final score
    if (tree[domain].empty()) {
        cout << domain << " " << score + scores[domain] << endl;
        return;
    }
    
    // Recursively compute the total scores for child domains
    for (const string& child : tree[domain]) {
        calculateTotalScores(child + "." + domain, score + scores[domain], tree, scores);
    }
}

// Main function to read input and process the domain hierarchy
void processDomains(const vector<string>& inputLines) {
    unordered_map<string, unordered_set<string>> tree;
    unordered_map<string, int> scores;

    // Reading input
    for (const string& line : inputLines) {
        istringstream iss(line);
        string domain;
        int score;
        iss >> domain >> score;
        scores[domain] = score;
        // Build the hierarchy
        string child = domain;
        cout<<child<<"<-------\n";
        while (true) {
            size_t pos = child.find('.');
            if (pos == string::npos) break;

            string parent = child.substr(pos + 1);
            // cout<<parent<<" === "<<child.substr(0,pos)<<" "<<child<<"\n";
            tree[parent].insert(child.substr(0, pos));
            child = parent;
        }
    }
    cout<<"printing the graph\n";
    for(auto it : tree){
        cout<<it.first<<"-->";
        for(auto v : it.second){
            cout<<v<<" ";
        }
        cout<<"\n";
    }
    // Process only root domains (those without a parent)
    for (const auto& entry : tree) {
        if (entry.first.find('.') == string::npos) { // Root domain
            calculateTotalScores(entry.first, 0, tree, scores);
        }
    }
}

// Driver code for testing
int main() {
    vector<vector<string>> testCases = {
        {
            "google.com 50",
            "mail.google.com 30",
            "maps.google.com 20",
            "youtube.com 100",
            "gaming.youtube.com 40"
        },
        {
            "example.com 70",
            "shop.example.com 40",
            "blog.example.com 20",
            "news.example.com 10",
            "uk.example.com 50",
            "london.uk.example.com 30"
        }
    };

    for (size_t i = 0; i < testCases.size(); i++) {
        cout << "Test Case " << i + 1 << ":\n";
        processDomains(testCases[i]);
        cout << "---------------------------\n";
    }

    return 0;
}


/*
Test Case 1:
google.com<-------
mail.google.com<-------
maps.google.com<-------
youtube.com<-------
gaming.youtube.com<-------
printing the graph
youtube.com-->gaming 
google.com-->maps mail 
com-->youtube google 
gaming.youtube.com 140
maps.google.com 70
mail.google.com 80
---------------------------
Test Case 2:
example.com<-------
shop.example.com<-------
blog.example.com<-------
news.example.com<-------
uk.example.com<-------
london.uk.example.com<-------
printing the graph
uk.example.com-->london 
example.com-->uk news blog shop 
com-->example 
london.uk.example.com 150
news.example.com 80
blog.example.com 90
shop.example.com 110
---------------------------
*/
