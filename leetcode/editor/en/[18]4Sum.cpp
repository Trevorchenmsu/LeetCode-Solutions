//Given an array nums of n integers, return an array of all the unique quadruple
//ts [nums[a], nums[b], nums[c], nums[d]] such that: 
//
// 
// 0 <= a, b, c, d < n 
// a, b, c, and d are distinct. 
// nums[a] + nums[b] + nums[c] + nums[d] == target 
// 
//
// You may return the answer in any order. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,0,-1,0,-2,2], target = 0
//Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
// 
//
// Example 2: 
//
// 
//Input: nums = [2,2,2,2,2], target = 8
//Output: [[2,2,2,2]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 200 
// -109 <= nums[i] <= 109 
// -109 <= target <= 109 
// 
// Related Topics Array Hash Table Two Pointers 
// 👍 3207 👎 406


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n^3)
 * space: (logn) for sorting
 * */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) return res;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < nums.size() - 2; ++j)
            {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;
                twoSum(res, nums, i, j, target);
            }
        }

        return res;
    }

    void twoSum(vector<vector<int>> &res, vector<int> &nums, int i, int j, int target) {
        int left = j + 1, right = nums.size() - 1;
        int sum = 0, tgt = target - nums[i] - nums[j];
        while (left < right) {
            sum = nums[left] + nums[right];
            if (sum == tgt)
            {
                res.push_back({nums[i], nums[j], nums[left++], nums[right--]});
                while (left < right && nums[left] == nums[left - 1]) ++left;
                while (left < right && nums[right] == nums[right + 1]) --right;
            }
            else if (sum < tgt) ++left;
            else --right;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
