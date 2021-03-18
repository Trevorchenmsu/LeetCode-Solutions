/*
solution 1: dp
time: O(n*n)
space: O(n)
*/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0 || intervals.size() == 1) return 0;
        
        sort(intervals.begin(), intervals.end());
        int m = intervals.size();
        vector<int> dp(m); // dp[i] represents the previous i non-overlapping intervals
        dp[0] = 1;
        int res = 0;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < i; j++) {
                if (intervals[i][0] >= intervals[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return m - *max_element(dp.begin(), dp.end());
    }
};

/*
solution 2: greedy
time: O(n*n)
space: O(n)
*/
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
        });
        int res = 1, right = intervals[0][1];
        
        for (const auto& interval : intervals) {
            if (interval[0] >= right) {
                res++;
                right = interval[1];
            }
        }
        
        return intervals.size() - res;
    }
};