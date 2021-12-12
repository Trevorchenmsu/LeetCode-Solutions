//Given an m x n integer matrix matrix, if an element is 0, set its entire row a
//nd column to 0's, and return the matrix. 
//
// You must do it in place. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
//Output: [[1,0,1],[0,0,0],[1,0,1]]
// 
//
// Example 2: 
//
// 
//Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
//Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[0].length 
// 1 <= m, n <= 200 
// -231 <= matrix[i][j] <= 231 - 1 
// 
//
// 
// Follow up: 
//
// 
// A straightforward solution using O(mn) space is probably a bad idea. 
// A simple improvement uses O(m + n) space, but still not the best solution. 
// Could you devise a constant space solution? 
// 
// Related Topics Array Hash Table Matrix 
// 👍 4751 👎 421


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: matrix manipulation
 * time: O(mn)
 * space: O(1)
 * */
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 这两个flag主要用来确定初始矩阵中第一行和第一列是否有0
        bool rowFlag = false, colFlag = false;

        // 检测第一列是否有0
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                colFlag = true;
                break;
            }
        }

        // 检测第一行是否有0
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                rowFlag = true;
                break;
            }
        }

        // 这里只能先把i，j位置对应的第一行和第一列的元素置为0，而不能把整个十字交叉的元素马上置为0，否则
        // 会在后面遍历的时候把原来不是0的元素当作是0，然后将更多的元素置为0
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // 现在才是正式替换0的时刻：只有被第一行/列0元素对上的元素才会被置为0
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 第一行/第一列的元素必须最后才修改，否则会在遍历的时候影响结果，因为会先产生0覆盖其它元素。
        if (rowFlag) {
            for (int i = 0; i < n; ++i){
                matrix[0][i] = 0;
            }
        }

        if (colFlag) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }

    }
};
//leetcode submit region end(Prohibit modification and deletion)
