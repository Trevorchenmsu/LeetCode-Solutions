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
        int n = nums.size();

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;

                twoSum(nums, j + 1, n - 1, i, j, target, res);
            }
        }

        return res;
    }


private:
   void twoSum(vector<int> &nums, int left, int right, int i, int j, int target, vector<vector<int>> &res) {
        while (left < right) {
            int sum = nums[left] + nums[right] + nums[i] + nums[j];
            if (sum == target) {
                res.push_back({nums[i], nums[j], nums[left++], nums[right--]});
                while (left < right && nums[left] == nums[left - 1]) left++;
                while (left < right && nums[right] == nums[right + 1]) right--;
            }
            else if (sum > target)
                right--;
            else
                left++;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
