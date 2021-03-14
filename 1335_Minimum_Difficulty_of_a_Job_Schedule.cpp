/*
solution 1: dfs
time: O(n*n*d)
space: O(n*d)
*/
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        
        vector<vector<int>> memo (n, vector<int> (d + 1, -1));
        
        return dfs(d, 0, jobDifficulty, memo, n);
    }
    
private:
    int dfs(int d, int len, vector<int> &jobDifficulty, vector<vector<int>> &memo, int n) {
        if (d == 0 && len == n) return 0;
        if (d == 0 || len == n) return INT_MAX;
        if(memo[len][d] != -1) return memo[len][d];
        
        int curMax = jobDifficulty[len];
        int min_val = INT_MAX;
        for (int i = len; i < n; ++i) {
            curMax = max(curMax, jobDifficulty[i]);
            int temp = dfs(d - 1, i + 1, jobDifficulty, memo, n);
            if (temp != INT_MAX) 
                min_val = min(min_val, temp + curMax);
        }
        
        return memo[len][d] = min_val;
    }
};

/*
solution 2: 2D DP bottom-up 
time: O(n*n*d)
space: O(n*d)
*/

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if (n < d) return -1;
        
        vector<vector<int>> dp (d, vector<int> (n));
        dp[0][0] = jobDifficulty[0];
        
        for (int j = 1; j < n; j++) {
            dp[0][j] = max(jobDifficulty[j], dp[0][j - 1]);
        }
        
        for (int i = 1; i < d; i++) {
            for (int j = i; j < n; j++) {
                int localMax = jobDifficulty[j];
                dp[i][j] = INT_MAX;
                for (int k = j; k >= i; k--) {
                    localMax = max(localMax, jobDifficulty[k]);
                    dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + localMax);
                }
            }
        }
        
        return dp[d- 1][n - 1];
    }

};

/*
solution 3: 1D DP bottom-up 
time: O(n*n*d)
space: O(n)
*/

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size(),  inf = 1e9, maxd;
        if (n < d) return -1;
        
        vector<int> dp(n + 1, inf);
        dp[n] = 0;
        
        for (int i = 1; i <= d; i++) {
            for (int j = 0; j <= n - i; j++) {
                maxd = 0, dp[j] = inf;
                for (int k = j; k <= n - i; k++) {
                    maxd = max(maxd, jobDifficulty[k]);
                    dp[j] = min(dp[j], maxd + dp[k + 1]);
                }
            }
        }
        return dp[0];
    }

};

/*
solution 4: stack
time: O(n*d)
space: O(n)
*/
class Solution {
public:
     int minDifficulty(vector<int>& A, int D) {
        int n = A.size();
        if (n < D) return -1;
        vector<int> dp(n, 1000), dp2(n), stack;
        for (int d = 0; d < D; ++d) {
            stack.clear();
            for (int i = d; i < n; i++) {
                dp2[i] = i ? dp[i - 1] + A[i] : A[i];
                while (stack.size() && A[stack.back()] <= A[i]) {
                    int j = stack.back(); stack.pop_back();
                    dp2[i] = min(dp2[i], dp2[j] - A[j] + A[i]);
                }
                if (stack.size()) {
                    dp2[i] = min(dp2[i], dp2[stack.back()]);
                }
                stack.push_back(i);
            }
            swap(dp, dp2);
        }
        return dp[n - 1];
    }

};




/*
solution 5: monotonous stack
time: O(n*d)
space: O(n)
*/



class Solution {
public:
    int minDifficulty(vector<int>& jobs, int days) {
        const int n = (int)jobs.size();
        if (n < days) return -1;
        vector<int> dp(n), old(n); // new and old dp
        // fill dp for d = 1
        dp[0] = jobs[0];
        for (int i = 1; i < n; i++)
            dp[i] = max(dp[i-1], jobs[i]);
        
        // fill dp for remaining days
        for (int d = 1; d < days; d++) {
            swap(dp, old);    
            // monotonic and minimum stack {oldBest, curMax, bestSoFar}
            vector<array<int,3>> stk = {{1<<30,1<<30,1<<30}};
            for (int i = d; i < n; i++) {
                int oldBest = old[i-1];
                while (stk.back()[1] <= jobs[i]) {
                    oldBest = min(oldBest, stk.back()[0]);
                    stk.pop_back();
                }
                stk.push_back({oldBest, jobs[i], min(oldBest + jobs[i], stk.back()[2])});
                dp[i] = stk.back()[2];
            }
        }
        return dp[n-1];
    }
};