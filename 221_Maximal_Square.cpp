/*
solution: dp
time: O(mn)
space: O(mn)
*/

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty())
            return 0;
        
        int m = matrix.size(), n = matrix[0].size();
        int res = 0;
        vector<vector<int>> dp (m + 1, vector<int> (n + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
                    res = max(res, dp[i][j]);
                }
            }
        }
        
        return res * res;
    }
};