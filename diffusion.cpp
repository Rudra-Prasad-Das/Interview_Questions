#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Node {
    string label;
    double value;
    vector<Node*> neighbors;

    Node(string lbl, double val = 0) : label(lbl), value(val) {}

    void print() const {
        cout << "Node " << label << ": " << value << endl;
    }
};

class DiffusionSimulator {
private:
    unordered_set<Node*> next_diffused;

public:
    void trigger(Node* node, double k) {
        node->value = k;
        next_diffused.insert(node);
    }

    bool step() {
        unordered_set<Node*> new_next_diffused;

        while (!next_diffused.empty()) {
            auto it = next_diffused.begin();
            Node* node = *it;
            next_diffused.erase(it);

            double value_sum = node->value;
            for (Node* neighbor : node->neighbors) {
                value_sum += neighbor->value;
            }

            double average = 1.0*value_sum / (node->neighbors.size() + 1);
            node->value = average;

            for (Node* neighbor : node->neighbors) {
                if (neighbor->value - average !=0) {
                    cout<<neighbor->value<<" "<<average<<"<---\n";
                    neighbor->value = average;
                    new_next_diffused.insert(neighbor);
                }
            }
        }

        next_diffused = new_next_diffused;
        if ( next_diffused.size() == 0)return false;
        return true;
    }

    void printNodes(vector<Node*>& nodes) {
        for (Node* node : nodes) {
            node->print();
        }
        cout << "--------------------\n";
    }
};

// Test Case: Question Scenario
void questionScenario() {
    Node a("a"), b("b"), c("c"), d("d"), e("e");

    a.neighbors.push_back(&c);
    b.neighbors.push_back(&c);
    c.neighbors = {&a, &b, &d};
    d.neighbors = {&c, &e};
    e.neighbors.push_back(&d);

    vector<Node*> nodes = {&a, &b, &c, &d, &e};

    DiffusionSimulator sim;
    sim.trigger(&c, 10);

    while (sim.step()) {
        sim.printNodes(nodes);
    }
}

// Test Case: Diamond Scenario
void diamondScenario() {
    Node a("a"), b("b"), c("c"), d("d");

    a.neighbors = {&b, &c};
    b.neighbors = {&a, &d};
    c.neighbors = {&a, &d};
    d.neighbors = {&b, &c};

    vector<Node*> nodes = {&a, &b, &c, &d};

    DiffusionSimulator sim;
    sim.trigger(&a, 10);

    while (sim.step()) {
        sim.printNodes(nodes);
    }
}

// Main function to run test cases
int main() {
    cout << "Question Scenario:\n";
    questionScenario();

    cout << "\nDiamond Scenario:\n";
    // diamondScenario();

    return 0;
}
