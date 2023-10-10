//Given an integer array nums of length n and an integer target, find three inte
//gers in nums such that the sum is closest to target. 
//
// Return the sum of the three integers. 
//
// You may assume that each input would have exactly one solution. 
//
// 
// Example 1: 
//
// 
//Input: nums = [-1,2,1,-4], target = 1
//Output: 2
//Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
// 
//
// Example 2: 
//
// 
//Input: nums = [0,0,0], target = 1
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 3 <= nums.length <= 1000 
// -1000 <= nums[i] <= 1000 
// -104 <= target <= 104 
// 
// Related Topics Array Two Pointers Sorting 
// 👍 4925 👎 222


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n^2)
 * space: O(log)
 * */
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0, diff = INT_MAX;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (abs(target - sum) < diff)  {
                    diff = abs(target - sum);
                    res = sum;
                }

                if (sum > target) right--;
                else left++;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
