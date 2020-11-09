class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        int n = stones.size();
        if(n <= 1) return 0;
        if((n - 1) % (K - 1)) return -1;

        vector<int> prefixSum(n + 1, 0);
        for(int i = 1;i <= n; ++i) prefixSum[i] = prefixSum[i - 1] + stones[i - 1]; 

        int dp[n][n]; 
        for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            dp[i][j]=0;
        for(int r = 0; r < n; ++r) {
            for(int l = r - K + 1; l >= 0; --l) { 
                int minNum = INT_MAX;

                for(int p = r; p > l; p -= (K - 1)) { 
                    minNum = min(minNum, dp[l][p - 1] + dp[p][r]); 
                }
                dp[l][r] = minNum; 

                if((r - l) % (K - 1) == 0) dp[l][r] += (prefixSum[r + 1] - prefixSum[l]); 
            }
        }
        return dp[0][n - 1];
    }
};

