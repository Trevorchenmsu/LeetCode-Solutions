//Given a 2D matrix matrix, handle multiple queries of the following types: 
//
// 
// Update the value of a cell in matrix. 
// Calculate the sum of the elements of matrix inside the rectangle defined by i
//ts upper left corner (row1, col1) and lower right corner (row2, col2). 
// 
//
// Implement the NumMatrix class: 
//
// 
// NumMatrix(int[][] matrix) Initializes the object with the integer matrix matr
//ix. 
// void update(int row, int col, int val) Updates the value of matrix[row][col] 
//to be val. 
// int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the 
//elements of matrix inside the rectangle defined by its upper left corner (row1, 
//col1) and lower right corner (row2, col2). 
// 
//
// 
// Example 1: 
//
// 
//Input
//["NumMatrix", "sumRegion", "update", "sumRegion"]
//[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 
//3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
//Output
//[null, 8, null, 10]
//
//Explanation
//NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 
//0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);
//numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e. sum of the left red rectang
//le)
//numMatrix.update(3, 2, 2);       // matrix changes from left image to right im
//age
//numMatrix.sumRegion(2, 1, 4, 3); // return 10 (i.e. sum of the right red recta
//ngle)
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 200 
// -105 <= matrix[i][j] <= 105 
// 0 <= row < m 
// 0 <= col < n 
// -105 <= val <= 105 
// 0 <= row1 <= row2 < m 
// 0 <= col1 <= col2 < n 
// At most 104 calls will be made to sumRegion and update. 
// 
// Related Topics Binary Indexed Tree Segment Tree 
// 👍 522 👎 66


//leetcode submit region begin(Prohibit modification and deletion)
class NumMatrix
{
private:
    vector<vector<int>> arr, bit;
    int n, m;

    int lowbit(int x)
    {
        return x & (-x);
    }

    int prefixSum(int row, int col)
    {
        int sum = 0;
        for (int i = row + 1; i > 0; i -= lowbit(i))
        {
            for (int j = col + 1; j > 0; j -= lowbit(j))
            {
                sum += bit[i][j];
            }
        }
        return sum;
    }

public:
    NumMatrix(vector<vector<int>> matrix)
    {
        if (!matrix.empty() && !matrix[0].empty()) {
            n = matrix.size();
            m = matrix[0].size();
            arr = vector<vector<int>>(n, vector<int>(m, 0));
            bit = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    update(i, j, matrix[i][j]);
                }
            }
        }
    }

    void update(int row, int col, int val)
    {
        int delta = val - arr[row][col];
        arr[row][col] = val;

        for (int i = row + 1; i <= n; i += lowbit(i))
        {
            for (int j = col + 1; j <= m; j += lowbit(j))
            {
                bit[i][j] += delta;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return (
                prefixSum(row2, col2) -
                prefixSum(row2, col1 - 1) -
                prefixSum(row1 - 1, col2) +
                prefixSum(row1 - 1, col1 - 1));
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */
//leetcode submit region end(Prohibit modification and deletion)
