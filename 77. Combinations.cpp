/*
solution 1: backtracking
time: O(k*C(n, k)), the number of combinations * each solution to traverse k number
space: O(C(n, k)), the number of combinations
*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(res, subset, n, k, 1);
        return res;
    }
    
    void dfs(vector<vector<int>>& res,
             vector<int>& subset,
             int n,
             int k,
             int index){
        if (subset.size() == k) {
            res.push_back(subset);
            return;
        }
        
        for (int i = index; i <= n; ++i) {
            subset.push_back(i);
            dfs(res, subset, n, k, i + 1);
            subset.pop_back();
        }
    }
};

/*
solution 2: optimized backtracking
time: O(k*C(n, k)), the number of combinations * each solution to traverse k number
space: O(C(n, k)), the number of combinations
optimization: the range of for loop. exp: n=5, k=4, size=1, we only need 4-1=3 more.
if i=4, we only add 4 and 5 to the subset, and size=1+2=3, it is less than 4. Thus,
i is not necessary to increase to 4. i=3 is enough. so the range becomes:
n - (k - subset.size() - 1)
*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> subset;
        dfs(res, subset, n, k, 1);
        return res;
    }
    
    void dfs(vector<vector<int>>& res,
             vector<int>& subset,
             int n,
             int k,
             int index){
        if (subset.size() == k) {
            res.push_back(subset);
            return;
        }
        
        for (int i = index; i <= n - (k - subset.size() - 1); ++i) {
            subset.push_back(i);
            dfs(res, subset, n, k, i + 1);
            subset.pop_back();
        }
    }
};

/*
solution 3: iteration
time: O(k*C(n, k)), the number of combinations * each solution to traverse k number
space: O(C(n, k)), the number of combinations
*/
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> subset(k, 0);
        
        int i = 0;
        while (i >= 0) {
            subset[i] += 1;
            // return to previous level
            if (subset[i] > n) --i;
            // reach the subset length
            else if (i == k - 1) res.push_back(subset);
            else {
                ++i;
                // similar to backtracking
                subset[i] = subset[i - 1];
            }
        }
        return res;
    }
};