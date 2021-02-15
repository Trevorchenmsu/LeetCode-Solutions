/*
Solution 1: backtracking
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

/*
Solution 2: backtracking
time: O(n*2^n)
space: O(n)
*/
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        if (candidates.size() == 0)
            return res;
        vector<int> path;
        vector<int> visited(candidates.size()); // O(n)
        sort(candidates.begin(), candidates.end()); // O(nlogn) 
        backtrack(res, candidates, path, visited, target, 0);
        return res;
    }
    
    void backtrack(vector<vector<int>> &res, vector<int> &candidates, vector<int> &path, vector<int> &visited,
                   int target, int idx) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return;
        
        for (int i = idx; i < candidates.size(); i++) {
            if (i > 0 && candidates[i] == candidates[i - 1] && !visited[i - 1]) continue;
            visited[i] = 1;
            path.push_back(candidates[i]);
            backtrack(res, candidates, path, visited, target - candidates[i], i + 1);
            path.pop_back();
            visited[i] = 0;
        }
    }
};

