//A peak element is an element that is strictly greater than its neighbors. 
//
// Given an integer array nums, find a peak element, and return its index. If th
//e array contains multiple peaks, return the index to any of the peaks. 
//
// You may imagine that nums[-1] = nums[n] = -∞. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3,1]
//Output: 2
//Explanation: 3 is a peak element and your function should return the index num
//ber 2. 
//
// Example 2: 
//
// 
//Input: nums = [1,2,1,3,5,6,4]
//Output: 5
//Explanation: Your function can return either index number 1 where the peak ele
//ment is 2, or index number 5 where the peak element is 6. 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 1000 
// -231 <= nums[i] <= 231 - 1 
// nums[i] != nums[i + 1] for all valid i. 
// 
//
// 
//Follow up: Could you implement a solution with logarithmic complexity? Related
// Topics Array Binary Search 
// 👍 2737 👎 2622


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] >= nums[mid + 1])
                end = mid;
            else
                start = mid;
        }

        return nums[start] > nums[end] ? start : end;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
