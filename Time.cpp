class CountDevices {
 // For follow-up question #3 this could be std::map, or a linked hash map.
 std::unordered_map<string, int> events;
 // For follow-up question #2 we could have "time_window_upper_bound" instead.
 const int time_window = ...;
public:
 void AddEvent(const std::string& id, int t) {
 events[id] = t;
 }
 // For original problem.
 int GetCount() {
 int count = 0;
 for (const auto& [id, t] : events) {
 if (t >= time(nullptr) - time_window) {
 ++count;
 }
 }
 return count;
 }
 // For follow-up question 1.
 int GetCount() {
 int count = 0;
 for (auto it = events.begin(); it != events.end();) {
 if (it->second >= time(nullptr) - time_window) {
 ++count;
 ++it;
 } else {
 it = events.erase(it);
 }
 }
 return count;
 }
 // For follow-up question 2.
 int GetCount(int time_window) {
 if (time_window > time_window_upper_bound) {
 // Some error message.
 return -1;
 }
 int count = 0;
 for (auto it = events.begin(); it != events.end();) {
 const int t = it->second;
 if (t >= time(nullptr) - time_window) {
 ++count;
 ++it;
 } else if (t < time(nullptr) - time_window_upper_bound) {
 it = events.erase(it);
 } else {
 ++it;
 }
 }
 return count;
 }
