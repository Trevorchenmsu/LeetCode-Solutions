class Solution {
private:
    int dfs(string& text1, string& text2, vector<vector<int>>& memo, int m, int n){
        if(memo[m][n] != -1)  return memo[m][n];
        
        if(m == 0 || n == 0){
            memo[m][n] = 0;
            return 0;
        } 
        
        if(text1[m - 1] != text2[n - 1]){
            memo[m][n] = max(dfs(text1, text2, memo, m, n - 1), dfs(text1, text2, memo, m - 1, n));
            
        } else{
            memo[m][n] = max(memo[m][n], dfs(text1, text2, memo, m - 1, n - 1) + 1);
        }
        return memo[m][n];
    }
    
    
public:
    int longestCommonSubsequence(string text1, string text2) {
        if(text1.empty() || text2.empty()) return 0;
        
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> memo(m + 1, vector<int> (n + 1, -1));
        return dfs(text1, text2, memo, m, n);
    }
};