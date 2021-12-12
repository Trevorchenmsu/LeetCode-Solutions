//Given an m x n matrix, return all elements of the matrix in spiral order. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
//Output: [1,2,3,6,9,8,7,4,5]
// 
//
// Example 2: 
//
// 
//Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
//Output: [1,2,3,4,8,12,11,10,9,5,6,7]
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 10 
// -100 <= matrix[i][j] <= 100 
// 
// Related Topics Array Matrix Simulation 
// 👍 4322 👎 689


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: implementation
 * time:  O(mn)
 * space: O(1)
 * */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;

        int top = 0, bottom = m - 1, left = 0, right = n - 1;

        while (true) {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[top][i]);
            }

            if(++top > bottom) {
                break;
            }

            for (int i = top; i <= bottom; i++) {
                res.push_back(matrix[i][right]);
            }

            if (--right < left) {
                break;
            }

            for (int i = right; i >= left; i--) {
                res.push_back(matrix[bottom][i]);
            }

            if (--bottom < top) {
                break;
            }

            for (int i = bottom; i >= top; i--) {
                res.push_back(matrix[i][left]);
            }

            if (++left > right) {
                break;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
