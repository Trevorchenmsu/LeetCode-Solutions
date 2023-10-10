//Given an n x n array of integers matrix, return the minimum sum of any falling
// path through matrix. 
//
// A falling path starts at any element in the first row and chooses the element
// in the next row that is either directly below or diagonally left/right. Specifi
//cally, the next element from position (row, col) will be (row + 1, col - 1), (ro
//w + 1, col), or (row + 1, col + 1). 
//
// 
// Example 1: 
//
// 
//Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
//Output: 13
//Explanation: There are two falling paths with a minimum sum as shown.
// 
//
// Example 2: 
//
// 
//Input: matrix = [[-19,57],[-40,-5]]
//Output: -59
//Explanation: The falling path with a minimum sum is shown.
// 
//
// 
// Constraints: 
//
// 
// n == matrix.length == matrix[i].length 
// 1 <= n <= 100 
// -100 <= matrix[i][j] <= 100 
// 
// Related Topics Array Dynamic Programming Matrix 
// 👍 2846 👎 97


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs + memo
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution {
public:
    int dirs[3][2] = {{1, -1}, {1, 0}, {1, 1}};
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), res = INT_MAX;
        vector<vector<int>> memo (n, vector<int> (n));
        for (int i = 0; i < n; ++i)
        {
            int sum = dfs(matrix, memo, 0, i, n);
            res = min(res, sum);
        }

        return res;
    }

    int dfs(vector<vector<int>>& matrix, vector<vector<int>>& memo, int row, int col, int n)
    {
        if (memo[row][col]) return memo[row][col];
        int res = INT_MAX;

        for (auto &dir : dirs)
        {
            int row_next = row + dir[0];
            int col_next = col + dir[1];
            if (row_next < 0 || row_next >= n || col_next < 0 || col_next >= n)
                continue;

            res = min(res, dfs(matrix, memo, row_next, col_next, n));

        }

        memo[row][col] = res == INT_MAX ? matrix[row][col]: res +  matrix[row][col];

        return memo[row][col];
    }
};

/*
 * solution 2: dp, top down
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), res = INT_MAX;
        vector<vector<int>> dp(n, vector<int> (n, INT_MAX));


        for (int i = 0; i < n; ++i)
            dp[0][i] = matrix[0][i];

        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (row + 1 < n)
                {
                    dp[row+1][col] = min(dp[row+1][col], dp[row][col] + matrix[row+1][col]);
                    if (col - 1 >= 0){
                        dp[row+1][col] = min(dp[row+1][col], dp[row][col-1] + matrix[row+1][col]);
                    }

                    if (col + 1 < n) {
                        dp[row+1][col] = min(dp[row+1][col], dp[row][col+1] + matrix[row+1][col]);
                    }
                }
            }
        }

        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};

/*
 * solution 3: dp, top down
 * time: O(n^2)
 * space: O(1)
 * */

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), res = INT_MAX;

        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (row + 1 < n)
                {
                    int pre = matrix[row][col];
                    if (col - 1 >= 0)
                        pre = min(pre, matrix[row][col-1] );

                    if (col + 1 < n)
                        pre = min(pre, matrix[row][col+1]);

                    matrix[row+1][col] += pre;
                }
            }
        }

        return *min_element(matrix[n-1].begin(), matrix[n-1].end());
    }
};


/*
 * solution 4: dp, top down, optimal
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(), res = INT_MAX;

        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (row + 1 < n)
                {
                    int pre = matrix[row][col];
                    if (col - 1 >= 0)
                        pre = min(pre, matrix[row][col-1] );

                    if (col + 1 < n)
                        pre = min(pre, matrix[row][col+1]);

                    matrix[row+1][col] += pre;
                }
                else res = min(res, matrix[row][col]);
            }
        }

        return res;
    }
};

/*
 * solution 4: dp, top down
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        if (matrix.size() == 1) return matrix[0][0];
        int n = matrix.size(), res = INT_MAX;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int pre = matrix[i - 1][j];
                if (j > 0) pre = min(pre, matrix[i - 1][j - 1]);
                if (j < n - 1) pre = min(pre, matrix[i - 1][j + 1]);
                matrix[i][j] += pre;
                if (i == n - 1) res = min(res, matrix[i][j]);
            }
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
