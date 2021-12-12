//Given an integer array nums of unique elements, return all possible subsets (t
//he power set). 
//
// The solution set must not contain duplicate subsets. Return the solution in a
//ny order. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,2,3]
//Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 
//
// Example 2: 
//
// 
//Input: nums = [0]
//Output: [[],[0]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 10 
// -10 <= nums[i] <= 10 
// All the numbers of nums are unique. 
// 
// Related Topics Array Backtracking Bit Manipulation 
// 👍 6414 👎 118


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtracking
 * time: O(n*2^n), total 2^n states, for each state, we need O(n) time to construct subset
 * space: O(n), maximum temporary array to store the subset
 * */
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> subset;
        backtrack(nums, res, subset, 0);
        return res;
    }

private:
    void backtrack(vector<int> &nums, vector<vector<int>> &res, vector<int> &subset, int idx) {
        res.push_back(subset);

        for (int i = idx; i < nums.size(); i++) {
            subset.push_back(nums[i]);
            backtrack(nums, res, subset, i + 1);
            subset.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
