class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(2, vector<int> (n + 1));
        
        // Initialization
        for(int j = 0; j <= n; ++j){
            dp[0][j] = j;
        }
        
        // dp
        for(int i = 1; i <= m; ++i){
            dp[i % 2][0] = i;
            for(int j = 1; j <= n; ++j){
                if(word1[i - 1] == word2[j - 1]){
                    dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
                } else{
                    dp[i % 2][j] = min(min(dp[(i - 1) % 2][j], dp[i % 2][j - 1]), dp[(i - 1) % 2][j - 1]) + 1;
                }
            }
        }
        
        return dp[m % 2][n];
    }
};