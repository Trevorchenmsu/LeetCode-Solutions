/*
solution 1: dp, top down
time: O(mn)
space: O(mn)
*/
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
solution 2: dp, top down, compression
time: O(mn)
space: O(n)
*/
class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i][j] represents the unique paths from (0,0) to (m, n)
        vector<vector<int>> dp(2, vector<int> (n));
        
        // initialization
        for (int i = 0; i < 2; ++i) {
            dp[i][0] = 1;
        }
        
        for (int j = 0; j < n; ++j) {
            dp[0][j] = 1;
        }
        
        // function
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i % 2][j] = dp[(i - 1) % 2][j] + dp[i % 2][j - 1];
            }
        }
        
        return dp[(m - 1) % 2][n - 1];
    }
};

/*
solution 3: dp, top down, further compression
time: O(mn)
space: O(n)
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i] represents the unique paths from (0,0) to (m, n)
        vector<int> dp(n);
        
        // initialization
        dp[0] = 1;
    
        // function
        for (int i = 0; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        
        return dp[n - 1];
    }
};
