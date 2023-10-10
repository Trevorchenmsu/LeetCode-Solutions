//Given a collection of numbers, nums, that might contain duplicates, return all
// possible unique permutations in any order. 
//
// 
// Example 1: 
//
// 
//Input: nums = [1,1,2]
//Output:
//[[1,1,2],
// [1,2,1],
// [2,1,1]]
// 
//
// Example 2: 
//
// 
//Input: nums = [1,2,3]
//Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 8 
// -10 <= nums[i] <= 10 
// 
// Related Topics Array Backtracking 
// 👍 6185 👎 108


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty() || nums.size() == 0) {
            return res;
        }
        vector<int> path, visited(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, path, res, visited);

        return res;
    }

    void backtrack(vector<int> &nums, vector<int> path, vector<vector<int>> &res, vector<int> &visited) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1] && !visited[i-1] || visited[i]) continue;

            visited[i] = 1;
            path.push_back(nums[i]);
            backtrack(nums, path, res, visited);
            path.pop_back();
            visited[i] = 0;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
