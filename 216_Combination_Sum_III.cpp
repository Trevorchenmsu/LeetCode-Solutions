/*
Solution: backtracking
time: O(k*C(9,k))
space: O(k) for stack space
*/
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(res, subset, k, n, 1);
        return res;
    }
    
    void dfs(vector<vector<int>>& res,
             vector<int>& subset,
             int k, 
             int n,
             int index) {
        
        if (n < 0) return;
        if (k == 0 && n == 0) {
            res.push_back(subset);
            return;
        }
        
        for (int i = index; i <= 9; ++i) {
            subset.push_back(i);
            dfs(res, subset, k - 1, n - i, i + 1);
            subset.pop_back();
        }
    }
};