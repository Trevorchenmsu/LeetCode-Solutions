//Given an integer array nums, find three numbers whose product is maximum and r
//eturn the maximum product. 
//
// 
// Example 1: 
// Input: nums = [1,2,3]
//Output: 6
// Example 2: 
// Input: nums = [1,2,3,4]
//Output: 24
// Example 3: 
// Input: nums = [-1,-2,-3]
//Output: -6
// 
// 
// Constraints: 
//
// 
// 3 <= nums.length <= 104 
// -1000 <= nums[i] <= 1000 
// 
// Related Topics Array Math 
// 👍 1556 👎 433


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: math
 * time: O(nlogn)
 * space: O(1)
 * */
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int res = 0;
        if (nums.empty()) return res;

        sort(nums.begin(), nums.end());
        int n = nums.size();
        return max(nums[0] * nums[1] * nums[n - 1], nums[n - 3] * nums[n - 2] * nums[n - 1]);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
