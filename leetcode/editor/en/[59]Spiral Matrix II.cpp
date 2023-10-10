//Given a positive integer n, generate an n x n matrix filled with elements from
// 1 to n2 in spiral order. 
//
// 
// Example 1: 
//
// 
//Input: n = 3
//Output: [[1,2,3],[8,9,4],[7,6,5]]
// 
//
// Example 2: 
//
// 
//Input: n = 1
//Output: [[1]]
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 20 
// 
// Related Topics Array Matrix Simulation 
// 👍 3238 👎 172


//leetcode submit region begin(Prohibit modification and deletion)
/* solution: 实现题
 * time: O(n^2)
 * space: O(1)
 * */

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res;
        if (n <= 0) {
            return res;
        }

        res.resize(n, vector<int> (n));

        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int val = 1;

        while (top <= bottom || left <= right) {
            for (int i = left; i <= right; ++i) {
                res[top][i] = val++;
            }

            ++top;

            for (int i = top; i <= bottom; ++i) {
                res[i][right] = val++;
            }

            --right;

            for (int i = right; i >= left; --i) {
                res[bottom][i] = val++;
            }

            --bottom;

            for (int i = bottom; i >= top; --i) {
                res[i][left] = val++;
            }

            ++left;
        }


        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
