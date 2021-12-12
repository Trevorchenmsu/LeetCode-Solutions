//You are given an m x n integer matrix mat and an integer target. 
//
// Choose one integer from each row in the matrix such that the absolute differe
//nce between target and the sum of the chosen elements is minimized. 
//
// Return the minimum absolute difference. 
//
// The absolute difference between two numbers a and b is the absolute value of 
//a - b. 
//
// 
// Example 1: 
//
// 
//Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
//Output: 0
//Explanation: One possible choice is to:
//- Choose 1 from the first row.
//- Choose 5 from the second row.
//- Choose 7 from the third row.
//The sum of the chosen elements is 13, which equals the target, so the absolute
// difference is 0.
// 
//
// Example 2: 
//
// 
//Input: mat = [[1],[2],[3]], target = 100
//Output: 94
//Explanation: The best possible choice is to:
//- Choose 1 from the first row.
//- Choose 2 from the second row.
//- Choose 3 from the third row.
//The sum of the chosen elements is 6, and the absolute difference is 94.
// 
//
// Example 3: 
//
// 
//Input: mat = [[1,2,9,8,7]], target = 6
//Output: 1
//Explanation: The best choice is to choose 7 from the first row.
//The absolute difference is 1.
// 
//
// 
// Constraints: 
//
// 
// m == mat.length 
// n == mat[i].length 
// 1 <= m, n <= 70 
// 1 <= mat[i][j] <= 70 
// 1 <= target <= 800 
// 
// 👍 87 👎 42


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs+memo
 * time: O(m*n*k)
 * space: O(m*k)
 * */
class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> memo(m, vector<int>(target + 1, INT_MAX));
        vector<int> minSum(m + 1, 0);

        for(int i = m - 1; i >= 0; i--){
            int minVal = *min_element(mat[i].begin(), mat[i].end());
            minSum[i] = minSum[i+1] + minVal;
        }

        return dfs(mat, 0, target, minSum, memo);
    }
private:
    int dfs(const vector<vector<int>>& mat, int i, int val, const vector<int>& minSum, vector<vector<int>>& memo){
        if(i >= mat.size()){
            return abs(val);
        }

        if(val <= 0){
            return abs(val - minSum[i]);
        }

        if(memo[i][val] != INT_MAX){
            return memo[i][val];
        }

        int res = INT_MAX;

        for(int j = 0; j < mat[0].size(); j++){
            res = min(res, dfs(mat, i + 1, val - mat[i][j], minSum, memo));
        }

        return memo[i][val] = res;
    }
};

/*
 * solution 2: backpack dp, compression
 * time: O(m*n*k)
 * space: O(2*k)
 * */

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size();
        int n = mat[0].size();

        int dp[2][target + 1];
        memset(dp, 0, sizeof(dp));

        for(int i = 0; i < m; i++) {
            for(int j = 0; j <= target; j++) {
                dp[(i + 1) % 2][j] = 1e5;
                for(int k = 0; k < n; k++) {
                    int curr = mat[i][k] + dp[i % 2][max(0, j - mat[i][k])];
                    if(abs(j - curr) < abs(j - dp[(i + 1) % 2][j])) {
                        dp[(i + 1) % 2][j] = curr;
                    }
                }
            }
        }

        return abs(dp[m % 2][target] - target);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
