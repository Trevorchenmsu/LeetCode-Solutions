/*
Solution: backtracking
time: O(n*2^n)
space: O(n)
*/

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
         vector<vector<int>> res;
        if (candidates.empty() || candidates.size() == 0)
            return res;
        
        sort(candidates.begin(), candidates.end());
        vector<int> subset;
        dfs(res, candidates, subset, target, 0);
        return res;
    }
    
    void dfs(vector<vector<int>>& res,
             vector<int>& candidates,
             vector<int>& subset,
             int target,
             int index) {
        
        if (target < 0) return;
        if (target == 0) {
            res.push_back(subset);
            return;
        }
        
        for (int i = index; i < candidates.size(); ++i) {
            if (i > index && candidates[i] == candidates[i - 1]) continue;
            subset.push_back(candidates[i]);
            dfs(res, candidates, subset, target - candidates[i], i + 1);
            subset.pop_back();
        }
    }
};
