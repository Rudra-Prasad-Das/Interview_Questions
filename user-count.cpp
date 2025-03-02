#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct DataPoint {
    int nanosecond;
    int user_count;
};

class UserCountList {
private:
    std::vector<DataPoint> values;
    int last_nanosecond = 0;
    int longest_sequence_count = 0;
    int longest_sequence = 0;
    int current_sequence = 0;

public:
    void add(const DataPoint& value) {
        last_nanosecond = value.nanosecond;
        
        if (!values.empty()) {
            if (values.back().user_count == value.user_count) {
                current_sequence++;
                if (longest_sequence < current_sequence) {
                    longest_sequence = current_sequence;
                    longest_sequence_count = value.user_count;
                }
                return;
            }
        }
        values.push_back(value);
        current_sequence = 1;
    }

    int find_first_nanosecond(int user_count) const {
        int start = 0, end = values.size() - 1, index = -1;
        while (start <= end) {
            int midpoint = start + (end - start) / 2;
            if (values[midpoint].user_count >= user_count) {
                index = midpoint;
                end = midpoint - 1;
            } else {
                start = midpoint + 1;
            }
        }
        return (index == -1) ? -1 : values[index].nanosecond;
    }

    int find_count_for_nanosecond(int nanosecond) const {
        int start = 0, end = values.size() - 1, index = -1;
        while (start <= end) {
            int midpoint = start + (end - start) / 2;
            if (values[midpoint].nanosecond > nanosecond) {
                index = midpoint;
                end = midpoint - 1;
            } else {
                start = midpoint + 1;
            }
        }
        return (index == -1 || index == 0) ? -1 : values[index - 1].user_count;
    }

    void print_longest_sequence() const {
        std::cout << "User count " << longest_sequence_count
                  << " starting at nanosecond "
                  << find_first_nanosecond(longest_sequence_count)
                  << " length " << longest_sequence << ".\n";
    }
};

int main() {
    UserCountList ucl;
    ucl.add({1000, 5});
    ucl.add({2000, 5});
    ucl.add({3000, 6});
    ucl.add({4000, 6});
    ucl.add({5000, 6});
    ucl.add({6000, 7});

    ucl.print_longest_sequence();
    return 0;
}
