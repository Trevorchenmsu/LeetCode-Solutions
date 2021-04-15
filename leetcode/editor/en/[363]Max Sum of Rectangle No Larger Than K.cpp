//Given an m x n matrix matrix and an integer k, return the max sum of a rectang
//le in the matrix such that its sum is no larger than k. 
//
// It is guaranteed that there will be a rectangle with a sum no larger than k. 
//
//
// 
// Example 1: 
//
// 
//Input: matrix = [[1,0,1],[0,-2,3]], k = 2
//Output: 2
//Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and
// 2 is the max number no larger than k (k = 2).
// 
//
// Example 2: 
//
// 
//Input: matrix = [[2,2,-1]], k = 3
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// m == matrix.length 
// n == matrix[i].length 
// 1 <= m, n <= 100 
// -100 <= matrix[i][j] <= 100 
// -105 <= k <= 105 
// 
//
// 
// Follow up: What if the number of rows is much larger than the number of colum
//ns? 
// Related Topics Binary Search Dynamic Programming Queue 
// 👍 1095 👎 80


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: brute force + dp, TLE
 * time: O(m^2*n^2)
 * space: O(mn)
 * */
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size(), res = INT_MIN;

        for (int i1 = 1; i1 <= m; i1++) {
            for (int j1 = 1; j1 <= n; j1++) {
                vector<vector<int>> dp(m + 1, vector<int> (n + 1)); // renew from (i1,j1) to (i2,j2)
                dp[i1][j1] = matrix[i1 - 1][j1 - 1];
                for (int i2 = i1; i2 <= m; i2++) {
                    for (int j2 = j1; j2 <= n; j2++) {
                        dp[i2][j2] = dp[i2 - 1][j2] + dp[i2][j2 - 1]
                                     - dp[i2 - 1][j2 - 1] + matrix[i2 - 1][j2 - 1];
                        if (dp[i2][j2] <= k)
                             res = max(res, dp[i2][j2]);
                    }
                }
            }
        }

        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)
