/*
solution 1: dp, bottom up
time: O(n*m), n is the row of triangle, m is the column of the triangle
space: O(n*m)
*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() == 0 || triangle[0].size() == 0)
            return 0;

        int m = triangle.size();
        int n = triangle[m - 1].size();

        // initilize dp matrix
        vector<vector<int>> dp;
        for(int i = 0; i < m; ++i){
            dp.push_back(vector<int>());
            for(int j = 0; j < triangle[i].size(); ++j){
                dp[i].push_back(0);
            }
        }

        // initialize last row
        dp[m - 1] = triangle[m - 1];

        // bottom up
        for(int i = m - 2; i >= 0; --i){
            for(int j = 0; j < dp[i].size(); ++j){
                dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + triangle[i][j];
            }
        }
        
        return dp[0][0];
    }
};


/*
solution 2: dp, top down
time: O(n*m)
space: O(n*m)
*/

class Solution {

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() == 0 || triangle[0].size() == 0)
            return 0;
        
   		// initilize dp matrix
        vector<vector<int>> dp;
        for(int i = 0; i < triangle.size(); ++i){
            dp.push_back(vector<int>());
            for(int j = 0; j < triangle[i].size(); ++j){
                dp[i].push_back(0);
            }
        }
        
        dp[0] = triangle[0];
                                           
        // boundary : two edges of the triangle
        for(int i = 1; i < dp.size(); ++i){
            dp[i][0] = dp[i - 1][0] + triangle[i][0]; 
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        }
                                           
        // top down
        for(int i = 1; i < dp.size(); ++i){
            for(int j = 1; j < dp[i].size() - 1; ++j){
                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }
                                           
        // get the min
        int res = INT_MAX;
        for(int i = 0; i < dp[m - 1].size(); ++i){
            res = min(res, dp[m - 1][i]);
        }

        return res;
    }
};

/*
solution 3: dp + compression, bottom up
time: O(n*n)
space: O(n)
*/

class Solution {
//  from bottom to top, dp + compression
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;
        int m = triangle.size();
        int n = triangle[m - 1].size();
        int dp[n];
        
        // initialize last row
        for (int j = 0; j < triangle[m-1].size(); ++j) {
            dp[j] = triangle[m - 1][j];
        }
        
        // bottom up
        for (int i = m - 2; i >= 0; --i) {
            for(int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        
        return dp[0];
    }
};


/*
solution 4: dfs + memo
time: O(n*n)
space: O(n*n)
*/
class Solution {
private:
    int dfs(int x, int y, vector<vector<int>>& triangle, vector<vector<int>>& memo){
        if(x >= triangle.size()){
            return 0;
        }
        
        if(memo[x][y] != INT_MAX){
            return memo[x][y];
        }
        
        memo[x][y] = min(dfs(x + 1, y, triangle, memo), dfs(x + 1, y + 1, triangle, memo)) + triangle[x][y];
             				  
        return memo[x][y];
    }
    
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size() == 0 || triangle[0].size() == 0)
            return -1;
        
        vector<vector<int>> memo;
      
      	// initialization, triangle memo
        for(int i = 0; i < triangle.size(); ++i){
            memo.push_back(vector<int>());
            for(int j = 0; j < triangle[i].size(); ++j){
                memo[i].push_back(INT_MAX);
            }
        }
        
        return dfs(0, 0, triangle, memo);
    }
};