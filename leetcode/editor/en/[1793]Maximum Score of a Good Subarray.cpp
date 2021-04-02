//You are given an array of integers nums (0-indexed) and an integer k. 
//
// The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., num
//s[j]) * (j - i + 1). A good subarray is a subarray where i <= k <= j. 
//
// Return the maximum possible score of a good subarray. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,4,3,7,4,5], k = 3
//Output: 15
//Explanation: The optimal subarray is (1, 5) with a score of min(4,3,7,4,5) * (
//5-1+1) = 3 * 5 = 15. 
// 
//
// Example 2: 
//
// 
//Input: nums = [5,5,4,5,4,1,1,1], k = 0
//Output: 20
//Explanation: The optimal subarray is (0, 4) with a score of min(5,5,4,5,4) * (
//4-0+1) = 4 * 5 = 20.
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 105 
// 1 <= nums[i] <= 2 * 104 
// 0 <= k < nums.length 
// 
// Related Topics Greedy 
// 👍 225 👎 14


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution： two pointers + sliding window
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int res = nums[k], min_val = nums[k],  n = nums.size();
        int i = k, j = k;

        while (i > 0 or j < n - 1) {
            if ((i > 0 ? nums[i - 1] : 0) < (j < n - 1 ? nums[j + 1] : 0))
                min_val = min(min_val, nums[++j]);
            else
                min_val = min(min_val, nums[--i]);

            res = max(res, min_val * (j - i + 1));
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
