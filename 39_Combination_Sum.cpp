/*
solution: backtracking
time: O(m^(target/min)), m is the number of elements in candidates that are smaller 
than target, min is the minimum element in candidates.
space: O(m^(target/min)) for solution, O(target/min) for stack space.
*/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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
            subset.push_back(candidates[i]);
            dfs(res, candidates, subset, target - candidates[i], i);
            subset.pop_back();
        }
    }
};