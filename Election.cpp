std::string DetermineWinnerSeparatePass(
 std::vector<std::vector<std::pair<std::string, int>>> election_results) {
 // Assume: district_results ordered by vote count, so last element in
 // the district is the minimum visible vote.
 std::unordered_map<std::string, int> candidate_results;
 // 1st pass: tally the visible votes, O(D*N)
 for (const auto& district_result : election_results) {
 for (const auto& [candidate, votes] : district_result) {
 if (candidate_results.contains(candidate)) {
 candidate_results[candidate] += votes;
 } else {
 candidate_results[candidate] = votes;
 }
 }
 }
 // At this point, `candidate_results` contains the visible vote tallies.
 // Find the candidate with the most votes, O(C)
 std::pair<std::string, int> winner = {"", 0};
 bool tie = false;
 for (const auto& [candidate, votes] : candidate_results) {
 if (votes > winner.second) {
 winner = {candidate, votes};
 tie = false;
 } else if (votes == winner.second) {
 tie = true;
 }
 }
 if (tie) {
 return "";
 }
 // 2nd pass: compute the potential votes for all other candidates, O(C*D*N)
 for (const auto& [candidate, votes] : candidate_results) {
 if (candidate == winner.first) {
 continue;
 }
 int potential = votes;
 for (int i = 0; i < election_results.size(); ++i) {
 bool candidate_in_district = false;
 for (int j = 0; j < election_results[i].size(); ++j) {
 if (election_results[i][j].first == candidate) {
 candidate_in_district = true;
 break;
 }
 }
 if (!candidate_in_district) {
 potential += election_results[i][election_results[i].size() - 1].second;
 }
 }
 if (potential > winner.second) {
 return "";
 }
 }
 return winner.first;
}
Pyt
