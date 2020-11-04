/*
solution: dp+memo
time:
space:
*/

class Solution {
public:
    int minScoreTriangulation(vector<int>& A) {
        int dp[50][50];
        
        memset(dp, 0, sizeof(dp));
        for(int j = 2; j < A.size(); j++){
            for(int i = j - 2; i>= 0; i--){
                for(int m = i + 1; m < j; m++){
                    if(dp[i][j] == 0){
                        dp[i][j] = A[i] * A[j] * A[m] + dp[i][m] + dp[m][j];
                    }else{
                        dp[i][j] = min(dp[i][j], A[i] * A[j] * A[m] + dp[i][m] + dp[m][j]);
                    }        
                }
            }
        }
        return dp[0][A.size()-1];
    }
};