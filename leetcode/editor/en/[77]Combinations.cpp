//Given two integers n and k, return all possible combinations of k numbers out 
//of the range [1, n]. 
//
// You may return the answer in any order. 
//
// 
// Example 1: 
//
// 
//Input: n = 4, k = 2
//Output:
//[
//  [2,4],
//  [3,4],
//  [2,3],
//  [1,2],
//  [1,3],
//  [1,4],
//]
// 
//
// Example 2: 
//
// 
//Input: n = 1, k = 1
//Output: [[1]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 20 
// 1 <= k <= n 
// 
// Related Topics Backtracking 
// 👍 4733 👎 156


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dfs/backtrack
 * time: O()
 * space: O()
 * */
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        search(res, path, n, k, 1);
        return res;
    }

    void search(vector<vector<int>> &res, vector<int> &path, int n, int k, int idx) {
        if (path.size() == k)
        {
            res.push_back(path);
            return;
        }

        for (int i = idx; i <= n; ++i)
        {
            path.push_back(i);
            search(res, path, n, k, i + 1);
            path.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
