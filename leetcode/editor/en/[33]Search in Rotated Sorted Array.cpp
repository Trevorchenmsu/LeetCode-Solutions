//There is an integer array nums sorted in ascending order (with distinct values
//). 
//
// Prior to being passed to your function, nums is rotated at an unknown pivot i
//ndex k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+
//1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, 
//[0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2]. 
//
// Given the array nums after the rotation and an integer target, return the ind
//ex of target if it is in nums, or -1 if it is not in nums. 
//
// 
// Example 1: 
// Input: nums = [4,5,6,7,0,1,2], target = 0
//Output: 4
// Example 2: 
// Input: nums = [4,5,6,7,0,1,2], target = 3
//Output: -1
// Example 3: 
// Input: nums = [1], target = 0
//Output: -1
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 5000 
// -104 <= nums[i] <= 104 
// All values of nums are unique. 
// nums is guaranteed to be rotated at some pivot. 
// -104 <= target <= 104 
// 
//
// 
//Follow up: Can you achieve this in O(log n) time complexity? Related Topics Ar
//ray Binary Search 
// 👍 7418 👎 650


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int min_idx = findMinIndex(nums);

        // find target in the right part
        int res = binarySearch(nums, min_idx, nums.size() - 1, target);

        if (res == -1)
            res = binarySearch(nums, 0, min_idx, target);
        // find target in the left part

        return res;
    }

private:
    int findMinIndex(vector<int> &nums) {
        int start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] > nums[end])
                start = mid;
            else
                end = mid;
        }

        return nums[start] < nums[end] ? start : end;
    }

    int binarySearch(vector<int> &nums, int start, int end, int target) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
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
