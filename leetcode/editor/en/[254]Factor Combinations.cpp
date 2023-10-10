//Numbers can be regarded as the product of their factors. 
//
// 
// For example, 8 = 2 x 2 x 2 = 2 x 4. 
// 
//
// Given an integer n, return all possible combinations of its factors. You may 
//return the answer in any order. 
//
// Note that the factors should be in the range [2, n - 1]. 
//
// 
// Example 1: 
//
// 
//Input: n = 1
//Output: []
// 
//
// Example 2: 
//
// 
//Input: n = 12
//Output: [[2,6],[3,4],[2,2,3]]
// 
//
// Example 3: 
//
// 
//Input: n = 37
//Output: []
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 107 
// 
// Related Topics Array Backtracking 
// 👍 955 👎 56


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: backtrack
 * time:
 * space:
 * */
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        vector<int> path;
        getCombination(res, path, n, 2);
        return res;
    }

    void getCombination (vector<vector<int>> &res, vector<int> &path, int n, int idx)
    {
        if (n == 1)
        {
            if (path.size() > 1) res.push_back(path);
            return;
        }

        for (int i = idx; i <= n; ++i)
        {
            if (n % i != 0) continue;
            path.push_back(i);
            getCombination(res, path, n / i, i);
            path.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
