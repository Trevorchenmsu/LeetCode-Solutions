//Given a collection of candidate numbers (candidates) and a target number (targ
//et), find all unique combinations in candidates where the candidate numbers sum 
//to target. 
//
// Each number in candidates may only be used once in the combination. 
//
// Note: The solution set must not contain duplicate combinations. 
//
// 
// Example 1: 
//
// 
//Input: candidates = [10,1,2,7,6,1,5], target = 8
//Output: 
//[
//[1,1,6],
//[1,2,5],
//[1,7],
//[2,6]
//]
// 
//
// Example 2: 
//
// 
//Input: candidates = [2,5,2,1,2], target = 5
//Output: 
//[
//[1,2,2],
//[5]
//]
// 
//
// 
// Constraints: 
//
// 
// 1 <= candidates.length <= 100 
// 1 <= candidates[i] <= 50 
// 1 <= target <= 30 
// 
// Related Topics Array Backtracking 
// 👍 6300 👎 157


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path, visited(candidates.size());
        sort(candidates.begin(), candidates.end());
        search(candidates, res, path, visited, target, 0);
        return res;
    }

    void search(vector<int> &candidates, vector<vector<int>> &res, vector<int> &path, vector<int> &visited, int target, int idx) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return;

        for (int i = idx; i < candidates.size(); ++i)
        {
            if (i - 1 >= 0 && candidates[i-1] == candidates[i] && !visited[i - 1]) continue;
            visited[i] = 1;
            path.push_back(candidates[i]);
            search(candidates, res, path, visited, target - candidates[i], i+1);
            path.pop_back();
            visited[i] = 0;
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
