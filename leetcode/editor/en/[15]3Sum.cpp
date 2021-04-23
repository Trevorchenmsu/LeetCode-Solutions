//Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k
//]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0. 
//
// Notice that the solution set must not contain duplicate triplets. 
//
// 
// Example 1: 
// Input: nums = [-1,0,1,2,-1,-4]
//Output: [[-1,-1,2],[-1,0,1]]
// Example 2: 
// Input: nums = []
//Output: []
// Example 3: 
// Input: nums = [0]
//Output: []
// 
// 
// Constraints: 
//
// 
// 0 <= nums.length <= 3000 
// -105 <= nums[i] <= 105 
// 
// Related Topics Array Two Pointers 
// 👍 10220 👎 1051


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers
 * time: O(n^2)
 * space: O(1)
 *
 * */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;

        sort(nums.begin(), nums.end()); // O(nlogn)

        for (int i = 0; i < nums.size(); i++) { // O(n^2)
            if (nums[0] > 0)
                break;

            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int target = -nums[i];
            int left = i + 1, right = nums.size() - 1;

            twoSum(nums, left, right, target, res);
        }

        return res;
    }

private:
    void twoSum(vector<int> &nums, int left, int right, int target, vector<vector<int>> &res) {
        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == target) {
                res.push_back({nums[left++], nums[right--], -target});
                while (left < right && nums[left] == nums[left - 1])
                    left++;
                while (left < right && nums[right] == nums[right + 1])
                    right--;
            }
            else if (sum > target)
                right--;
            else
                left++;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
