//You are given an n x n 2D matrix representing an image, rotate the image by 90
// degrees (clockwise). 
//
// You have to rotate the image in-place, which means you have to modify the inp
//ut 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation. 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
//Output: [[7,4,1],[8,5,2],[9,6,3]]
// 
//
// Example 2: 
//
// 
//Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
//Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
// 
//
// Example 3: 
//
// 
//Input: matrix = [[1]]
//Output: [[1]]
// 
//
// Example 4: 
//
// 
//Input: matrix = [[1,2],[3,4]]
//Output: [[3,1],[4,2]]
// 
//
// 
// Constraints: 
//
// 
// matrix.length == n 
// matrix[i].length == n 
// 1 <= n <= 20 
// -1000 <= matrix[i][j] <= 1000 
// 
// Related Topics Array Math Matrix 
// 👍 6562 👎 399


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * 卡点：
 * 1. 如何存储转换后的元素？会覆盖原始元素？
 * 2. 坐标转换如何实现？
 * */

/*
 * solution: matrix manipulation
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int len = matrix.size();
        transpose(matrix, len); // 转置
        swapCol(matrix, len); // 左列与右列交换，逐渐往中间靠拢
    }

    void transpose(vector<vector<int>>& matrix, int rows)
    {
        for (int i = 0; i < rows; i++) {
            for (int j = i + 1; j < rows; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    void swapCol(vector<vector<int>>& matrix, int rows) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < rows / 2; ++j) {
                swap(matrix[i][j], matrix[i][rows - 1 - j]);
            }
        }
    }

};

//leetcode submit region end(Prohibit modification and deletion)
