class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        if(n <= 1) return n;
        vector<vector<int>> dp(n,vector<int>(n,1000));
        for(int i =0;i<n;i++) dp[i][i] = 1;
        for(int len = 1;len<n;len++){
            for(int i = 0;i+len<n;i++){
                dp[i][i+len] = len+1;
                for(int k = i;k<(i+len);k++){
                    int total = dp[i][k] + dp[k+1][i+len];
                    if(s[k] == s[i+len]) total--;
                    dp[i][i+len] = min(total,dp[i][i+len]);
                }
                
            }
        }
        return dp[0][n-1];
    }
};
