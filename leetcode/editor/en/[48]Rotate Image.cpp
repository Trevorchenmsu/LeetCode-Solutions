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
 * solution: matrix manipulation，先转置，再从左到右，两端逐渐交换列
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0)
        {
            return;
        }

        int n = matrix.size();
        transpose(matrix, n);
        swapColumn(matrix, n);
    }

    void transpose(vector<vector<int>> &mat, int n) {
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                swap(mat[i][j], mat[j][i]);
            }
        }
    }

    void swapColumn(vector<vector<int>> &mat, int n) {
        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n / 2; ++col)
            {
                swap(mat[row][col], mat[row][n - 1 - col]);
            }
        }
    }
};

// python解法，先从上到下flip，然后再转置
class Solution:
    def rotate(self, A: List[List[int]]) -> None:

        if A is None or A[0] is None: return

        A.reverse()
        for i in range(len(A)):
            for j in range(i):
                A[i][j], A[j][i] = A[j][i], A[i][j]



//leetcode submit region end(Prohibit modification and deletion)
