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
 * solution: matrix manipulation, python解法同理
 * time: O(mn)
 * space: O(1)
 * */
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix.size() == 0 || matrix[0].empty() || matrix[0].size() == 0)
        {
            return;
        }

        int m = matrix.size(), n = matrix[0].size();
        /*
        flag用来标识第一行或第一列是否存在0。这一步要优先做，因为接下来的矩阵元素中如果有0，
        就要把第一行和第一列对应的元素置为0，如果后面再做这个操作找flag的话，就会有false positive。
        非第一行第一列元素为0时为什么要把第一行和第一列的置为0？目的是用这些0为标杆。元素本身在改行/列的具体
        位置不重要，因为这一整行/列都会被置为0，所以只要我们只要该位置的领头羊是0，那么遍历的时候就可以把整列/行
        都置为0，这也就是为什么我们要把第一行/列的元素置为0，目的就是找出领头羊。
        */

        bool row_flag = false, col_flag = false;
        // 查找第一行是否存在0
        for (int i = 0; i < n; ++i)
        {
            if (matrix[0][i] == 0)
            {
                row_flag = true;
                break;
            }
        }

        // 查找第一列是否存在0
        for (int i = 0; i < m; ++i)
        {
            if (matrix[i][0] == 0)
            {
                col_flag = true;
                break;
            }
        }

        // 用第一行/列竖标杆
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        // 以第一行/列的0为标杆，填充内部满足为0的条件
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // 填充第一行
        if (row_flag)
        {
            for (int i = 0; i < n; ++i)
            {
                matrix[0][i] = 0;
            }
        }

        // 填充第一列
        if (col_flag)
        {
            for (int i = 0; i < m; ++i)
            {
                matrix[i][0] = 0;
            }
        }

    }
};
//leetcode submit region end(Prohibit modification and deletion)
