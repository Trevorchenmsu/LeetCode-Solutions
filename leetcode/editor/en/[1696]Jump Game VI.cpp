//You are given a 0-indexed integer array nums and an integer k. 
//
// You are initially standing at index 0. In one move, you can jump at most k st
//eps forward without going outside the boundaries of the array. That is, you can 
//jump from index i to any index in the range [i + 1, min(n - 1, i + k)] inclusive
//. 
//
// You want to reach the last index of the array (index n - 1). Your score is th
//e sum of all nums[j] for each index j you visited in the array. 
//
// Return the maximum score you can get. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,-1,-2,4,-7,3], k = 2
//Output: 7
//Explanation: You can choose your jumps forming the subsequence [1,-1,4,3] (und
//erlined above). The sum is 7.
// 
//
// Example 2: 
//
// 
//Input: nums = [10,-5,-2,4,0,3], k = 3
//Output: 17
//Explanation: You can choose your jumps forming the subsequence [10,4,3] (under
//lined above). The sum is 17.
// 
//
// Example 3: 
//
// 
//Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length, k <= 105 
// -104 <= nums[i] <= 104 
// 
// Related Topics Dequeue 
// 👍 384 👎 23


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs, TLE
 * time: O(nk)
 * space: (k^n)
 * */
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int res = 0;
        dfs(nums, 0, res, 0, k);
        return res;
    }

    void dfs(vector<int> &nums, int idx, int &res, int sum, int k) {
        if (idx >= nums.size())
            return;

        if (idx == nums.size() - 1) {
            res = max(res, sum + nums[idx]);
            return;
        }

        for (int i = 1; i <= k; i++)
            dfs(nums, idx + i, res, sum + nums[idx], k);
    }
};

/*
 * solution 2: sliding window + monotonic stack
 * time: O(n)
 * space: (n)
 * */
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        deque<pair<int, int>> dq;
        dq.push_back({nums[0], 0});

        for (int i = 1; i < n; i++) {
            while (!dq.empty() && i - dq.front().second > k)
                // larger than the window size k, delete the front
                dq.pop_front();

            // current step, add current value
            int curSteps = dq.front().first + nums[i];

            while (!dq.empty() && curSteps > dq.back().first)
                dq.pop_back();

            dq.push_back({curSteps, i});
        }

        return dq.back().first;
    }


};
//leetcode submit region end(Prohibit modification and deletion)
