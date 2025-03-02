#include <iostream>
using namespace std;

bool check(int m, int n, int k, int d) {
    int cnt = (m - 1) / k + 1;
    return (cnt * cnt) >= n;  // Equivalent to (cnt ** d) in Python when d = 2
}

int smallest_size(int n, int k, int d = 2) {
    int l = 1, r = n * k;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (check(m, n, k, d))
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main() {
    int n = 10, k = 3;
    cout << "Smallest size: " << smallest_size(n, k) << endl;
    return 0;
}
