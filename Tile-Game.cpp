// Below is a solution following 1C approach.
// Check there are no diagonally connected cells, this ensures there are no
// - tiles touching in an L-shape
// - tiles touching in a T-shape
// - tiles touching at corners
bool CheckShapes(const bool board[10][10]) {
 for (int i = 0; i < 10 - 1; ++i) {
 for (int j = 0; j < 10; ++j) {
 if (board[i][j] && ((j + 1 < 10 && board[i + 1][j + 1]) ||
 (j - 1 >= 0 && board[i + 1][j - 1]))) {
 return false;
 }
 }
 }
 return true;
}
// Detect sizes of the tiles, subtract from `tileTypes`.
// This detects tiles that might be touching end-to-end
// See the doc for ValidateField for an explanation of tileTypes
bool CheckSizes(const bool board[10][10],
 std::map</*size*/ int, /*count*/ int>& tileTypes) {
 bool visited[10][10] = {{}};
 for (int i = 0; i < 10; ++i) {
 for (int j = 0; j < 10; ++j) {
 if (board[i][j] && !visited[i][j]) {
 int size = 1;
 // Check vertically
 for (int k = i + 1; k < 10 && board[k][j]; ++k) {
 visited[k][j] = true;
 ++size;
 }
 // Check horizontally
 for (int k = j + 1; k < 10 && board[i][k]; ++k) {
 visited[i][k] = true;
 ++size;
 }
 if (--tileTypes[size] < 0) {
 return false;
 }
 }
 }
 }
 return true;
}
// The main validation method
// Uses the above CheckShapes and CheckSizes methods
// tileTypes is the expected frequencies of each tile of some length K
// tileTypes = {5: 1, 4: 1, 3: 2, 2: 1} means
// - There should be 1 tile of length 5
// - There should be 1 tile of length 4
// - There should be 2 tiles of length 3
// - There should be 1 tile of length 2
bool ValidateField(const bool board[10][10],
 const std::map</*size*/ int, /*count*/ int>& tileTypes) {
 if (!CheckShapes(board)) return false;
 auto usedTypes = tileTypes;
 if (!CheckSizes(board, usedTypes)) return false;
 // Ensures that every expected tile is placed on the board
 return std::all_of(
 usedTypes.begin(), usedTypes.end(),
 [](const std::map<int, int>::value_type p) { return p.second == 0; });
}
