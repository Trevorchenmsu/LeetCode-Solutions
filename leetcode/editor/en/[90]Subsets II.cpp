//Given an integer array nums that may contain duplicates, return all possible s
//ubsets (the power set). 
//
// The solution set must not contain duplicate subsets. Return the solution in a
//ny order. 
//
// 
// Example 1: 
// Input: nums = [1,2,2]
//Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
// Example 2: 
// Input: nums = [0]
//Output: [[],[0]]
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 10 
// -10 <= nums[i] <= 10 
// 
// Related Topics Array Backtracking Bit Manipulation 
// 👍 6060 👎 171


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dfs/backtrack
 * time: O(n*2^n)
 * space: O(n*2^n)
 * */
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path, visited(nums.size());
        sort(nums.begin(), nums.end());
        search(res, nums, path, visited, 0);
        return res;
    }

    void search(vector<vector<int>> &res, vector<int> &nums, vector<int> &path, vector<int> &visited, int idx) {
        res.push_back(path);

        for (int i = idx; i < nums.size(); ++i)
        {
            if (i > 0 && nums[i - 1] == nums[i] && !visited[i-1]) continue;
            visited[i] = 1;
            path.push_back(nums[i]);
            search(res, nums, path, visited, i+1);
            path.pop_back();
            visited[i] = 0;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
