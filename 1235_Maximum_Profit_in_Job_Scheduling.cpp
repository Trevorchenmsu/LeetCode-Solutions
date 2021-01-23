/*
solution: dp + binary search
time: O(nlogn)
space: O(n)
*/
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        
        for (int i = 0; i < n; i++) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        
        sort(jobs.begin(), jobs.end(), cmp);
        // dp: (endTime, profit_sum)
        vector<pair<int, int>> dp;
        dp.push_back({-1, 0}); // in case out of boundary
        int res = 0;
        
        for (auto& job : jobs) {
            int cur = res; // dp[i-1]
            // binary search to get the interval larger than the starttime of current interval
            auto iter = upper_bound(dp.begin(), dp.end(), make_pair(job[0], INT_MAX));
            // iterator move 1 to get the range samller or equal to current starttime.
            // prev(iter, 1)->second = dp[j], job[2] = val[i];
            // state equation: dp[i] = max(dp[i-1], dp[j] + val[i])
            cur = max(cur, prev(iter, 1)->second + job[2]);
            // update dp state
            dp.push_back({job[1], cur});
            // update final result
            res = max(res, cur);
        }
        
        return res;
    }
};