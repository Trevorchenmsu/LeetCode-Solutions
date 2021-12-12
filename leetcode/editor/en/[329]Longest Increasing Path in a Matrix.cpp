//Given an m x n integers matrix, return the length of the longest increasing pa
//th in matrix. 
//
// From each cell, you can either move in four directions: left, right, up, or d
//own. You may not move diagonally or move outside the boundary (i.e., wrap-around
// is not allowed). 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
//Output: 4
//Explanation: The longest increasing path is [1, 2, 6, 9].
// 
//
// Example 2: 
//
// 
//Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
//Output: 4
//Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is
// not allowed.
// 
//
// Example 3: 
//
// 
//Input: matrix = [[1]]
//Output: 1
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 200 
// 0 <= matrix[i][j] <= 231 - 1 
// 
// Related Topics Dynamic Programming Depth-First Search Breadth-First Search Gr
//aph Topological Sort Memoization 
// 👍 3696 👎 62


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs + memo
 * time: O(mn)
 * space: O(mn)
 *
 * */
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo (m, vector<int> (n, 0));
        int res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                res = max(res, dfs(matrix, i, j, memo));
            }
        }

        return res;
    }

private:
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int m, n;
    int dfs(vector<vector<int>> &matrix, int x, int y, vector<vector<int>> &memo) {
        if (memo[x][y] != 0) {
            return memo[x][y];
        }

        int res = 1;
        for (auto &dir : dirs) {
            int nx = x + dir[0], ny = y + dir[1];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }

            if (matrix[x][y] >= matrix[nx][ny]) {
                continue;
            }

            int len = dfs(matrix, nx, ny, memo);
            res = max(res, len + 1);
        }

        memo[x][y] = res;

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
