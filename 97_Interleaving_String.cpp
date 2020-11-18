class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()){
            return false;
        }
        int m = s1.size();
        int n = s2.size();
        
        vector<vector<bool>> dp(2, vector<bool> (n + 1));
        
        // initialization
        dp[0][0] = true;
        for(int j = 1; j <= n; ++j){
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
        }

        // dp
        for(int i = 1; i <= m; ++i){
            dp[i % 2][0] = dp[(i - 1) % 2][0] && s1[i - 1] == s3[i - 1];
            for(int j = 1; j <= n; ++j){
                dp[i % 2][j] = (s1[i - 1] == s3[i + j - 1] && dp[(i - 1) % 2][j]) || 
                    (s2[j - 1] == s3[i + j -1] && dp[i % 2][j - 1]);
            }
        }
        
        return dp[m % 2][n];
    }
};