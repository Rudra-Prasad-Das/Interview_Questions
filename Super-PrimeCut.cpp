#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>
bool IsPrime(std::int64_t n) {
 if (n < 2) return false;
 // This could be optimized by
 // - keeping a cache of primes
 // - only looping over the primes
 for (auto i = 2; i * i <= n; ++i) {
 if (n % i == 0) return false;
 }
 return true;
}
std::vector<std::int64_t> SpcUpTo(std::int64_t limit) {
 std::vector<std::int64_t> ret;
 std::deque<std::int64_t> candidates;
 auto add = [](std::int64_t value, auto& candidates, std::int64_t limit) {
 if (value <= limit) candidates.push_back(value);
 };
 // Seed SPC's from 1-10
 add(2, candidates, limit);
 add(3, candidates, limit);
 add(5, candidates, limit);
 add(7, candidates, limit);
 while (!candidates.empty()) {
 auto c = candidates.front();
 candidates.pop_front();
 if (IsPrime(c)) {
 ret.push_back(c);
 add(10 * c + 1, candidates, limit);
 add(10 * c + 3, candidates, limit);
 add(10 * c + 7, candidates, limit);
 add(10 * c + 9, candidates, limit);
 }
 }
 return ret;
}
int main() {
 std::int64_t limit = 512000;
 std::cout << "SPC below " << limit << ":\n";
 for (auto spc : SpcUpTo(limit)) {
 std::cout << spc << "\n";
 }
 return 0;
}
