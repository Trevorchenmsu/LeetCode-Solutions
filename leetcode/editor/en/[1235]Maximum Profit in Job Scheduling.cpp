//We have n jobs, where every job is scheduled to be done from startTime[i] to e
//ndTime[i], obtaining a profit of profit[i]. 
//
// You're given the startTime, endTime and profit arrays, return the maximum pro
//fit you can take such that there are no two jobs in the subset with overlapping 
//time range. 
//
// If you choose a job that ends at time X you will be able to start another job
// that starts at time X. 
//
// 
// Example 1: 
//
// 
//
// 
//Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
//Output: 120
//Explanation: The subset chosen is the first and fourth job. 
//Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
// 
//
// Example 2: 
//
// 
//
// 
//Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70
//,60]
//Output: 150
//Explanation: The subset chosen is the first, fourth and fifth job. 
//Profit obtained 150 = 20 + 70 + 60.
// 
//
// Example 3: 
//
// 
//
// 
//Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
//Output: 6
// 
//
// 
// Constraints: 
//
// 
// 1 <= startTime.length == endTime.length == profit.length <= 5 * 104 
// 1 <= startTime[i] < endTime[i] <= 109 
// 1 <= profit[i] <= 104 
// 
// Related Topics Array Binary Search Dynamic Programming Sorting 
// 👍 2275 👎 23


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dp + sort + binary search
 * time: O(nlogn)
 * space: O(n)
 * */

class Solution {
    static bool cmp (const vector<int> &v1, const vector<int> &v2) {
        return v1[1] < v2[1];
    }

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;
        for (size_t i = 0; i < startTime.size(); i++) {
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }

        sort(jobs.begin(), jobs.end(), cmp);
        vector<pair<int, int>> dp;
        dp.push_back({-1, 0});
        int res = 0, cur = 0;

        for (auto &job : jobs) {
            cur = res; //相等于dp[i] = dp[i-1]
            // 这里不是在jobs里面二分查找，而是在dp里面，因为我们要找的是dp[j]， 即i之前离i最近的最大收益和
            auto iter = upper_bound(dp.begin(), dp.end(), make_pair(job[0], INT_MAX));
            cur = max(cur, prev(iter, 1)->second + job[2]);//相当于dp[i]=max(dp[i-1], dp[j]+val);
            dp.push_back({job[1], cur});
            res = max(res, cur);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
