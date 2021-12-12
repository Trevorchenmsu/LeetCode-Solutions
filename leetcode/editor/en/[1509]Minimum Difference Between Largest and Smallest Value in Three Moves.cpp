//Given an array nums, you are allowed to choose one element of nums and change 
//it by any value in one move. 
//
// Return the minimum difference between the largest and smallest value of nums 
//after perfoming at most 3 moves. 
//
// 
// Example 1: 
//
// 
//Input: nums = [5,3,2,4]
//Output: 0
//Explanation: Change the array [5,3,2,4] to [2,2,2,2].
//The difference between the maximum and minimum is 2-2 = 0. 
//
// Example 2: 
//
// 
//Input: nums = [1,5,0,10,14]
//Output: 1
//Explanation: Change the array [1,5,0,10,14] to [1,1,0,1,1]. 
//The difference between the maximum and minimum is 1-0 = 1.
// 
//
// Example 3: 
//
// 
//Input: nums = [6,6,0,1,1,4,6]
//Output: 2
// 
//
// Example 4: 
//
// 
//Input: nums = [1,5,6,14,15]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 10^5 
// -10^9 <= nums[i] <= 10^9 
// Related Topics Array Greedy Sorting 
// 👍 766 👎 105


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: sorting
 * time: O(nlogn)
 * space: O(logn)
 * */
class Solution {
public:
    int minDifference(vector<int>& nums) {
        if (nums.empty() || nums.size() == 0 || nums.size() <= 4) {
            return 0;
        }

        sort(nums.begin(), nums.end());
        int n = nums.size();
        // remove 3 smallest
        int diff_1 = nums[n - 1] - nums[3];
        // remove 3 largest
        int diff_2 = nums[n - 4] - nums[0];
        // remove 1 smallest and 2 largest
        int diff_3 = nums[n - 3] - nums[1];
        // remove 2 smallest and 1 largest
        int diff_4 = nums[n - 2] - nums[2];

        int res = min({diff_1, diff_2, diff_3, diff_4});

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
