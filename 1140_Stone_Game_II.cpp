/*
solution 1: dfs
time: O(n)?
space: O(n*n), memorizing array to store the state.
*/

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int len = piles.size();
        vector<int> sum(len);
        sum[len - 1] = piles[len - 1];
        for (int i = len - 2; i >= 0; --i) {
            sum[i] = sum[i + 1] + piles[i];
        }
        vector<vector<int>> memo(len, vector<int> (len, -1));
        return dfs(piles, 0, 1, len, sum, memo);
    }
    
    int dfs(vector<int>& piles, int start, int M, int& len, vector<int>& sum, vector<vector<int>>& memo) {
        if (len - start <= 2 * M) {
            memo[start][M] = sum[start];
            return sum[start];
        }
        if(memo[start][M] != -1) {
            return memo[start][M];
        }
        int res = 0;
        for (int i = 1; i <= 2 * M && i + start <= len; ++i) {
            res = max(res, sum[start] - dfs(piles, start + i, max(M, i), len, sum, memo));
        }
        memo[start][M] = res;
        return res;
    }
};
