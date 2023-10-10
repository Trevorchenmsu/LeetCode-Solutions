//Given an array of distinct integers candidates and a target integer target, re
//turn a list of all unique combinations of candidates where the chosen numbers su
//m to target. You may return the combinations in any order. 
//
// The same number may be chosen from candidates an unlimited number of times. T
//wo combinations are unique if the frequency of at least one of the chosen number
//s is different. 
//
// It is guaranteed that the number of unique combinations that sum up to target
// is less than 150 combinations for the given input. 
//
// 
// Example 1: 
//
// 
//Input: candidates = [2,3,6,7], target = 7
//Output: [[2,2,3],[7]]
//Explanation:
//2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple ti
//mes.
//7 is a candidate, and 7 = 7.
//These are the only two combinations.
// 
//
// Example 2: 
//
// 
//Input: candidates = [2,3,5], target = 8
//Output: [[2,2,2,2],[2,3,3],[3,5]]
// 
//
// Example 3: 
//
// 
//Input: candidates = [2], target = 1
//Output: []
// 
//
// 
// Constraints: 
//
// 
// 1 <= candidates.length <= 30 
// 1 <= candidates[i] <= 200 
// All elements of candidates are distinct. 
// 1 <= target <= 500 
// 
// Related Topics Array Backtracking 
// 👍 12418 👎 259


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtracking/dfs
 * time: O(n^(T/M+1), n为元素个数，T为target，M为数组中的最小元素
 * space:
 * */
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        sort(candidates.begin(), candidates.end());
        search(candidates, res, path, target, 0);
        return res;
    }

    void search(vector<int> &candidates, vector<vector<int>> &res, vector<int> &path, int target, int idx) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return;

        for (int i = idx; i < candidates.size(); ++i)
        {
            path.push_back(candidates[i]);
            search(candidates, res, path, target - candidates[i], i);
            path.pop_back();
        }
    }
};


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates = sorted(list(candidates))
        res = []
        self.dfs(candidates, target, 0, [], res)
        return res

    def dfs(self, candidates, target, start, combination, res):
        if target < 0:
            return

        if target == 0:
            res.append(list(combination))

        for i in range(start, len(candidates)):
            combination.append(candidates[i])
            self.dfs(candidates, target - candidates[i], i, combination, res)
            combination.pop()
//leetcode submit region end(Prohibit modification and deletion)
