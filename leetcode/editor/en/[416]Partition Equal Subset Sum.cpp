//Given a non-empty array nums containing only positive integers, find if the ar
//ray can be partitioned into two subsets such that the sum of elements in both su
//bsets is equal. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,5,11,5]
//Output: true
//Explanation: The array can be partitioned as [1, 5, 5] and [11].
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,5]
//Output: false
//Explanation: The array cannot be partitioned into equal sum subsets.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 200 
// 1 <= nums[i] <= 100 
// 
// Related Topics Array Dynamic Programming 
// 👍 6308 👎 102


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: backtrack, TLE
 * time: O(2^n)
 * space: O(n)
 * */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        bool res = false;
        vector<int> path;
        dfs(nums, res, 0, 0, sum, path);
        return res;
    }

    void dfs(vector<int> &nums, bool &res, int idx, int curSum, int totalSum, vector<int> path) {
        if (path.size() > nums.size() - 1) return;
        if (curSum * 2 == totalSum) {
            res = true;
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            curSum += nums[i];
            path.push_back(nums[i]);
            dfs(nums, res, i + 1, curSum, totalSum, path);
            if (res) return;
            curSum -= nums[i];
            path.pop_back();
        }
    }
};

/*
 * solution 2: prefixSum, WA
 * time: O(n)
 * space: O(n)
 * test case 过不了:[2,2,1,1]
 * */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n), right(n), prefixSum(n + 2);
        for (int i = 1; i <= n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
        }
        for (int i = 0; i < n; i++) {
            int val1 = prefixSum[i];
            int val2 = prefixSum[n] - prefixSum[i + 1];
            if (val1 + nums[i] == val2 || val2 + nums[i] == val1 || val1 + val2 == nums[i])
                return true;
        }

        return false;
    }
};

/*
 * solution 3 : dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int target = sum >> 1;
        if (sum & 1) return false;
        vector<bool> dp(target + 1);
        dp[0] = true;
        for (int num : nums) {
            for (int i = target; i >= num; i--) {
                dp[i] = dp[i] || dp[i - num];
            }
        }

        return dp[target];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
