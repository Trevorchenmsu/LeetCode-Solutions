//Given an array of integers nums which is sorted in ascending order, and an int
//eger target, write a function to search target in nums. If target exists, then r
//eturn its index. Otherwise, return -1. 
//
// You must write an algorithm with O(log n) runtime complexity. 
//
// 
// Example 1: 
//
// 
//Input: nums = [-1,0,3,5,9,12], target = 9
//Output: 4
//Explanation: 9 exists in nums and its index is 4
// 
//
// Example 2: 
//
// 
//Input: nums = [-1,0,3,5,9,12], target = 2
//Output: -1
//Explanation: 2 does not exist in nums so return -1
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 104 
// -104 < nums[i], target < 104 
// All the integers in nums are unique. 
// nums is sorted in ascending order. 
// 
// Related Topics Array Binary Search 
// 👍 10916 👎 217


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1;
        int mid;
        while (start + 1 < end) {
            mid = (end - start) / 2 + start;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                end = mid;
            else
                start = mid;
        }

        if (nums[start] == target)
            return start;
        if (nums[end] == target)
            return end;

        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
