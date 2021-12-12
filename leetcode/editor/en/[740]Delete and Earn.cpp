//You are given an integer array nums. You want to maximize the number of points
// you get by performing the following operation any number of times: 
//
// 
// Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must d
//elete every element equal to nums[i] - 1 and every element equal to nums[i] + 1.
// 
// 
//
// Return the maximum number of points you can earn by applying the above operat
//ion some number of times. 
//
// 
// Example 1: 
//
// 
//Input: nums = [3,4,2]
//Output: 6
//Explanation: You can perform the following operations:
//- Delete 4 to earn 4 points. Consequently, 3 is also deleted. nums = [2].
//- Delete 2 to earn 2 points. nums = [].
//You earn a total of 6 points.
// 
//
// Example 2: 
//
// 
//Input: nums = [2,2,3,3,3,4]
//Output: 9
//Explanation: You can perform the following operations:
//- Delete a 3 to earn 3 points. All 2's and 4's are also deleted. nums = [3,3].
//
//- Delete a 3 again to earn 3 points. nums = [3].
//- Delete a 3 once more to earn 3 points. nums = [].
//You earn a total of 9 points. 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 2 * 104 
// 1 <= nums[i] <= 104 
// 
// Related Topics Array Hash Table Dynamic Programming 
// 👍 1802 👎 135


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dp
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        /* 计算相同数字的累积和，这里采用哈希表也是同样的意思。但是，能用vector就不用vector，
         * 因为哈希表中因为哈希函数的作用，会导致赋值时间和内存存储更大。
         * 用这种方式计算累积和很聪明，因为当选择一个元素，而且它有多个相同值，我们就会多次删除它，
         * 所以还不如直接就计算这些相同元素的总和。
         */
        vector<int> gain(10001, 0);
        for (auto &num : nums) {
            gain[num] += num;
        }

        // dp[i]表示删除数为i时所得到的最大分数，在i之前的删除值的累加值已经被算在这个dp[i]里面了。
        // 因为dp[1]前面除了dp[0]就没其他累加值了，所以直接让dp[1]等于gain[1]
        vector<int> dp(10001, 0);
        dp[1] = gain[1];

        /* dp[i]的结果只能来自dp[i-2]和dp[i-1]。因为dp[i-2]中取的是i-2的累积和
         * 所以删除的是i-3和i-1，在i的时候又可以获取累积和，所以当dp[i]来自dp[i-2]时，结果
         * 是dp[i-2]+gain[i]。而当dp[i]来自dp[i-1]时，i是i-1的相邻位，是被删除的位置，因此
         * 我们不会在dp[i-1]加上这个gain[i]。题目要求的是最大值，所以我们需要从这两个路径中选较大值
         * */
        for (int i = 2; i < 10001; i++) {
            dp[i] = max(dp[i - 2] + gain[i], dp[i - 1]);
        }

        // 这里为什么要返回dp数组最后一个数？因为dp值是通过前面的值不断累加过来的，所以这是最终的总和
        // 同时因为在计算每个dp时，都是挑选最大的，所以累加值也将会是最大的。
        return dp[10000];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
