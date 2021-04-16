//There is an integer array nums sorted in non-decreasing order (not necessarily
// with distinct values). 
//
// Before being passed to your function, nums is rotated at an unknown pivot ind
//ex k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1]
//, ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0
//,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,
//2,4,4]. 
//
// Given the array nums after the rotation and an integer target, return true if
// target is in nums, or false if it is not in nums. 
//
// 
// Example 1: 
// Input: nums = [2,5,6,0,0,1,2], target = 0
//Output: true
// Example 2: 
// Input: nums = [2,5,6,0,0,1,2], target = 3
//Output: false
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 5000 
// -104 <= nums[i] <= 104 
// nums is guaranteed to be rotated at some pivot. 
// -104 <= target <= 104 
// 
//
// 
//Follow up: This problem is the same as Search in Rotated Sorted Array, where n
//ums may contain duplicates. Would this affect the runtime complexity? How and wh
//y? Related Topics Array Binary Search 
// 👍 2061 👎 578


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: binary search
 * time: O(n)
 * space: O(1)
 *
 * */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int min_idx = findMinIndex(nums);

        // find target in the right part
        bool res = binarySearch(nums, min_idx, nums.size() - 1, target);

        if (!res)
            res = binarySearch(nums, 0, min_idx, target);
        // find target in the left part

        return res;
    }


private:
    int findMinIndex(vector<int> &nums) {
        int i = 0;

        while (i < nums.size() - 1) {
            if (nums[i + 1] < nums[i])
                break;
            i++;
        }

        return i;
    }

    bool binarySearch(vector<int> &nums, int start, int end, int target) {
        while (start + 1 < end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target)
                end = mid;
            else
                start = mid;
        }

        if (nums[start] == target || nums[end] == target)
            return true;

        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
