//Given an array of integers nums sorted in ascending order, find the starting a
//nd ending position of a given target value. 
//
// If target is not found in the array, return [-1, -1]. 
//
// You must write an algorithm with O(log n) runtime complexity. 
//
// 
// Example 1: 
// Input: nums = [5,7,7,8,8,10], target = 8
//Output: [3,4]
// Example 2: 
// Input: nums = [5,7,7,8,8,10], target = 6
//Output: [-1,-1]
// Example 3: 
// Input: nums = [], target = 0
//Output: [-1,-1]
// 
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 105 
// -109 <= nums[i] <= 109 
// nums is a non-decreasing array. 
// -109 <= target <= 109 
// 
// Related Topics Array Binary Search 
// 👍 7462 👎 242


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: binary search, twice
 * time: O(logn)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        if (nums.empty() || nums.size() == 0)
            return res;

        int start, end, mid;

        // binary search for the left part
        start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            mid = (end - start) / 2 + start;
            if (nums[mid] < target)
                start = mid;
            else
                end = mid;
        }

        if (nums[start] == target)
            res[0] = start;
        else if (nums[end] == target)
            res[0] = end;

        // binary search for the right part
        start = 0, end = nums.size() - 1;
        while (start + 1 < end) {
            mid = (end - start) / 2 + start;
            if (nums[mid] <= target)
                start = mid;
            else
                end = mid;
        }

        if (nums[end] == target)
            res[1] = end;
        else if (nums[start] == target)
            res[1] = start;

        return res;
    }
};

/*
 * solution 2: binary search
 * time: O(logn)
 * space: O(1)
 * */

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res = {-1, -1};
        if (nums.empty() || nums.size() == 0)
            return res;

        auto left = binarySearch(nums, target - 0.5);
        if (nums[left[0]] == target) {
            res[0] = left[0];
        }
        else if (nums[left[1]] == target) {
            res[0] = left[1];
        }

        auto right = binarySearch(nums, target + 0.5);
        if (nums[right[1]] == target) {
            res[1] = right[1];
        }
        else if (nums[right[0]] == target) {
            res[1] = right[0];
        }

        return res;
    }

private:
    vector<int> binarySearch(vector<int>& nums, double target){
        int start = 0, end = nums.size() - 1;
        while(start + 1 < end){
            int mid = start + (end - start) / 2;
            if(nums[mid] > target){
                end = mid;
            }
            else {
                start = mid;
            }
        }
        return {start, end};
    }
};
//leetcode submit region end(Prohibit modification and deletion)
