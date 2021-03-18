/*
solution : greedy
time: O(nlogn)
space: O(1)
*/

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(intervals.begin(), intervals.end(), [](const auto& v1, const auto& v2) {
           return v1[0] == v2[0] ? v2[1] < v1[1] : v1[0] < v2[0]; 
        });
        
        int cnt = 0, end = 0, pre_end = 0;
        for (const auto& interval : intervals) {
            end = interval[1];
            
            if (pre_end < end) {
                cnt++;
                pre_end = end;
            }
        }
        
        return cnt;
    }
};

