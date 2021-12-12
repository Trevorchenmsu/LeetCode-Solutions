//Given an m x n matrix mat, return an array of all the elements of the array in
// a diagonal order. 
//
// 
// Example 1: 
//
// 
//Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
//Output: [1,2,4,7,5,3,6,8,9]
// 
//
// Example 2: 
//
// 
//Input: mat = [[1,2],[3,4]]
//Output: [1,2,3,4]
// 
//
// 
// Constraints: 
//
// 
// m == mat.length 
// n == mat[i].length 
// 1 <= m, n <= 104 
// 1 <= m * n <= 104 
// -105 <= mat[i][j] <= 105 
// 
// Related Topics Array Matrix Simulation 
// 👍 1488 👎 441


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: implementation
 * time: O(m*n)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) {
            return {};
        }

        int m = mat.size(), n = mat[0].size();
        vector<int> res(m * n);
        int dirs[2][2] = {{-1, 1}, {1, -1}};

        int row = 0, col = 0, dir = 0;
        for (int i = 0; i < m * n; i++) {
            res[i] = mat[row][col];
            row += dirs[dir][0], col += dirs[dir][1];

            if (row >= m) {row = m - 1; col += 2; dir = 1 - dir;}
            if (col >= n) {col = n - 1; row += 2; dir = 1 - dir;}
            if (row < 0) {row = 0; dir = 1 - dir;}
            if (col < 0) {col = 0; dir = 1 - dir;}
        }

        return res;

    }
};
//leetcode submit region end(Prohibit modification and deletion)
