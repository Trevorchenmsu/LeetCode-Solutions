/*
solution 1: backtracking
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

/*
solution 2: backtracking
time: O(m^(target/min)), m is the number of elements in candidates that are smaller 
than target, min is the minimum element in candidates.
space: O(m^(target/min)) for solution, O(target/min) for stack space.
*/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.empty()) return res;
        
        vector<int> path;
        sort(res.begin(), res.end());
        int sum = 0;
        backtrack(res, candidates, path, target, sum,0);
        return res;
    }
     
    void backtrack(vector<vector<int>> &res, vector<int>& candidates, vector<int> &path, 
                   int &target, int &sum, int idx) {
        if (sum == target) {
            res.push_back(path);
            return;
        }
        
        if (sum > target) 
            return;
        
        for (int i = idx; i < candidates.size(); i++) {
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtrack(res, candidates, path, target, sum, i);
            path.pop_back();
            sum -= candidates[i];
        }
    }
};
