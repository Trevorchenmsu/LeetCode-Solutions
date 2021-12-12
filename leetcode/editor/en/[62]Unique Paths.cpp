//A robot is located at the top-left corner of a m x n grid (marked 'Start' in t
//he diagram below). 
//
// The robot can only move either down or right at any point in time. The robot 
//is trying to reach the bottom-right corner of the grid (marked 'Finish' in the d
//iagram below). 
//
// How many possible unique paths are there? 
//
// 
// Example 1: 
//
// 
//Input: m = 3, n = 7
//Output: 28
// 
//
// Example 2: 
//
// 
//Input: m = 3, n = 2
//Output: 3
//Explanation:
//From the top-left corner, there are a total of 3 ways to reach the bottom-righ
//t corner:
//1. Right -> Down -> Down
//2. Down -> Down -> Right
//3. Down -> Right -> Down
// 
//
// Example 3: 
//
// 
//Input: m = 7, n = 3
//Output: 28
// 
//
// Example 4: 
//
// 
//Input: m = 3, n = 3
//Output: 6
// 
//
// 
// Constraints: 
//
// 
// 1 <= m, n <= 100 
// It's guaranteed that the answer will be less than or equal to 2 * 109. 
// 
// Related Topics Math Dynamic Programming Combinatorics 
// 👍 6493 👎 259


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 坐标型-二维dp
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i][j] represents the unique paths from (0,0) to (m, n)
        vector<vector<int>> dp(m, vector<int> (n));

        // initialization
        for (int i = 0; i < m; ++i) {
            dp[i][0] = 1;
        }

        for (int j = 0; j < n; ++j) {
            dp[0][j] = 1;
        }

        // function
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};


/*
 * solution 1: 坐标型-二维dp，optimal
 * time: O(mn)
 * space: O(n)
 * */
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // dp[i]表示在当前i列时的方案总数
        vector<int> dp(n, 0);
        // 初始化第一列方案为1，先默认没有障碍物
        dp[0] = 1;

        for(int i = 0; i < m; ++i){
            // 不管是哪一行，只有某一行有障碍物，第一列无法通路，设为0
            if(grid[i][0] == 1){
                dp[0] = 0;
            }

            for(int j = 1; j < n; ++j){
                // 方程右边的dp[j]表示上一行j列的情况，j-1表示左边列的情况
                // 所以当前列用这两个更新，相当于考虑上节点和左节点
                if(grid[i][j] == 0){
                    dp[j] = dp[j] + dp[j - 1];
                }
                    // 如果当前点为障碍物，表明此路不同，所以j列为0
                else{
                    dp[j] = 0;
                }
            }
        }

        return dp[n - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
