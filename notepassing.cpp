// Calculate risk of moving horizontally
double RiskX(int row) { return 0.9 / MathUtil::IPow(2, row); }
// Calculate risk of moving vertically
double RiskY(int row) { return .5 / MathUtil::IPow(2, row); }
// Calculate risk of moving between two nodes. Sneakiness is used for Q2,3
double Risk(std::pair<int, int> curr, std::pair<int, int> next,
 double sneakiness = 0) {
 double risk;
 if (curr.first == next.first) { // horizontal movement
 risk = RiskX(curr.first);
 } else { // vertical movement
 risk = RiskY(std::min(curr.first, next.first));
 }
 risk *= (1 - sneakiness);
 return risk;
}
// Q1
double probability_fail_q1(const std::vector<std::pair<int, int>>& path) {
 double total_risk = 0;
 for (int i = 0; i < path.size() - 1; i++) {
 const auto& curr = path[i];
 const auto& next = path[i + 1];
 total_risk += (1 - total_risk) * Risk(curr, next);
 }
 return total_risk;
}
// Q2
double probability_fail_q2(
 const std::vector<std::pair<int, int>>& path,
 const std::vector<const std::vector<double>>& sneakiness) {
 double total_risk = 0;
 for (int i = 0; i < path.size() - 1; i++) {
 const auto& curr = path[i];
 const auto& next = path[i + 1];
 total_risk += (1 - total_risk) *
 Risk(curr, next, sneakiness[curr.first][curr.second]);
 }
 return total_risk;
}
// Q3
// Helper struct to organize a student according to their place, their
// sneak_factor, their distance to origin student, and the previous student
// required to get this distance.
struct Student {
 std::pair<int, int> coord;
 double sneak_factor;
 double distance = INFINITY; // risk
 Student* prev = nullptr;
};
// How to order students according to their distance
struct OrderStudents {
 bool operator()(Student* a, Student* b) const {
 return a->distance > b->distance;
 }
};
// If this pairing of students has a lower distance than next's distance, then
// use this distance. Therefore, make next->prev = curr, and then return true.
// Otherwise, return false.
bool MaybeRelaxEdge(Student* curr, Student* next) {
 // new_distance = P(risk_curr) + P(success up to curr) * P(risk_next)
 double new_dist =
 curr->distance +
 (1 - curr->distance) * Risk(curr->coord, next->coord, curr->sneak_factor);
 if (new_dist < next->distance) {
 next->distance = new_dist;
 next->prev = curr;
 return true;
 }
 return false;
}
/**
* Calculate what the safest path is between two students, incl. sneakiness.
* Assumptions: sneakiness, risk, cannot be negative, otherwise there's an inf.
* loop in calculating distance. This uses dijkstra's algorithm to calculate
* path with smallest distance.
*/
std::vector<std::pair<int, int>> safest_path_q3(
 const std::pair<int, int>& start, const std::pair<int, int>& end,
 const std::vector<const std::vector<double>>& sneakiness) {
 std::vector<std::vector<std::unique_ptr<Student>>> student_matrix;
 std::priority_queue<Student*, std::vector<Student*>, OrderStudents> q;
 // Setup
 for (int i = 0; i < sneakiness.size(); i++) {
 student_matrix.push_back({});
 for (int j = 0; j < sneakiness[i].size(); j++) {
 std::pair<int, int> coord = {i, j};
 double distance = INFINITY;
 if (coord == start) {
 distance = 0;
 }
 auto s = std::make_unique<Student>();
 *s = {.coord = coord,
 .sneak_factor = sneakiness[i][j],
 .distance = distance};
 student_matrix[i].push_back(std::move(s));
 }
 }
 // Run dijkstra
 q.push(student_matrix[start.first][start.second].get());
 while (!q.empty()) {
 Student* curr = q.top();
 q.pop();
 if (curr->coord.first > 0) {
 // upwards node exists
 Student* up =
 student_matrix[curr->coord.first - 1][curr->coord.second].get();
 if (MaybeRelaxEdge(curr, up)) {
 q.push(up);
 }
 }
 if (curr->coord.first < student_matrix.size() - 1) {
 // downwards node exists
 Student* down =
 student_matrix[curr->coord.first + 1][curr->coord.second].get();
 if (MaybeRelaxEdge(curr, down)) {
 q.push(down);
 }
 }
 if (curr->coord.second > 0) {
 // left node exists
 Student* left =
 student_matrix[curr->coord.first][curr->coord.second - 1].get();
 if (MaybeRelaxEdge(curr, left)) {
 q.push(left);
 }
 }
 if (curr->coord.second < student_matrix[curr->coord.first].size() - 1) {
 // right node exists
 Student* right =
 student_matrix[curr->coord.first][curr->coord.second + 1].get();
 if (MaybeRelaxEdge(curr, right)) {
 q.push(right);
 }
 }
 }
 // Regenerate path from end to start
 std::vector<std::pair<int, int>> solution;
 Student* curr = student_matrix[end.first][end.second].get();
 while (curr && curr->coord != start) {
 solution.push_back(curr->coord);
 curr = curr->prev;
 }
 solution.push_back(start);
 std::reverse(solution.begin(), solution.end());
 return solution;
}
