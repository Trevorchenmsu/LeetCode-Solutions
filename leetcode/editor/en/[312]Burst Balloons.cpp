//You are given n balloons, indexed from 0 to n - 1. Each balloon is painted wit
//h a number on it represented by an array nums. You are asked to burst all the ba
//lloons. 
//
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1
//] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if 
//there is a balloon with a 1 painted on it. 
//
// Return the maximum coins you can collect by bursting the balloons wisely. 
//
// 
// Example 1: 
//
// 
//Input: nums = [3,1,5,8]
//Output: 167
//Explanation:
//nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
//coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167 
//
// Example 2: 
//
// 
//Input: nums = [1,5]
//Output: 10
// 
//
// 
// Constraints: 
//
// 
// n == nums.length 
// 1 <= n <= 500 
// 0 <= nums[i] <= 100 
// 
// Related Topics Array Dynamic Programming 
// 👍 4315 👎 121


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: 二维dp，区间型
 * time: O(n^3)
 * space: O(n^2)
 * */
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        int n = nums.size();
        vector<vector<int>> dp (n, vector<int> (n));

        for (int len = 3; len <= n; len++) {
            for (int start = 0; start <= n - len; start++) {
                int end = start + len - 1;
                for (int mid = start + 1; mid < end; mid++) {
                    dp[start][end] = max(dp[start][end], dp[start][mid] + dp[mid][end] +
                                         nums[start] * nums[mid] * nums[end]);
                }
            }
        }

        return dp[0][n - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
