//Given an integer array nums, you need to find one continuous subarray that if 
//you only sort this subarray in ascending order, then the whole array will be sor
//ted in ascending order. 
//
// Return the shortest such subarray and output its length. 
//
// 
// Example 1: 
//
// 
//Input: nums = [2,6,4,8,10,9,15]
//Output: 5
//Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the 
//whole array sorted in ascending order.
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3,4]
//Output: 0
// 
//
// Example 3: 
//
// 
//Input: nums = [1]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -105 <= nums[i] <= 105 
// 
//
// 
//Follow up: Can you solve it in O(n) time complexity? Related Topics Array 
// 👍 3904 👎 177


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: brute force
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();

        int curMax = INT_MIN;
        int right_bound = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] < curMax) //出现顺序不对的情况，更新无序子数组右边界
                right_bound = i;
            curMax = max(curMax, nums[i]);//如果递增，每次更新已访问元素最大值
        }

        int curMin = INT_MAX;
        int left_bound = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] > curMin)
                left_bound = i;
            curMin = min(curMin, nums[i]);
        }

        return left_bound >= right_bound ? 0 : right_bound - left_bound + 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
