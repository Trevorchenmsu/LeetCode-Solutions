//Given an array nums of distinct integers, return all the possible permutations
//. You can return the answer in any order. 
//
// 
// Example 1: 
// Input: nums = [1,2,3]
//Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// Example 2: 
// Input: nums = [0,1]
//Output: [[0,1],[1,0]]
// Example 3: 
// Input: nums = [1]
//Output: [[1]]
// 
// 
// Constraints: 
//
// 
// 1 <= nums.length <= 6 
// -10 <= nums[i] <= 10 
// All the integers of nums are unique. 
// 
// Related Topics Array Backtracking 
// 👍 7681 👎 151


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs
 * time: O(n*n!)
 * space: O(n*n!)
 *
 * */
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty() || nums.size() == 0) {
            return res;
        }
        vector<int> path;
        backtrack(nums, path, res);

        return res;
    }

    void backtrack(vector<int> &nums, vector<int> path, vector<vector<int>> &res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            auto it = find(path.begin(), path.end(), nums[i]);
            if (it != path.end()) {
                continue;
            }

            path.push_back(nums[i]);
            backtrack(nums, path, res);
            path.pop_back();
        }
    }
};

/*
 * solution 2: dfs, faster
 * time: O(n*n!)
 * space: O(n*n!)
 * */
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty() || nums.size() == 0) {
            return res;
        }
        vector<int> path;
        vector<int> visited(nums.size(), 0);
        backtrack(nums, path, res, visited);

        return res;
    }

    void backtrack(vector<int> &nums, vector<int> path, vector<vector<int>> &res, vector<int> &visited) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] == 1) {
                continue;
            }

            visited[i] = 1;
            path.push_back(nums[i]);
            backtrack(nums, path, res, visited);
            path.pop_back();
            visited[i] = 0;
        }
    }
};

//leetcode submit region end(Prohibit modification and deletion)
