//Given two strings text1 and text2, return the length of their longest common s
//ubsequence. If there is no common subsequence, return 0. 
//
// A subsequence of a string is a new string generated from the original string 
//with some characters (can be none) deleted without changing the relative order o
//f the remaining characters. 
//
// 
// For example, "ace" is a subsequence of "abcde". 
// 
//
// A common subsequence of two strings is a subsequence that is common to both s
//trings. 
//
// 
// Example 1: 
//
// 
//Input: text1 = "abcde", text2 = "ace" 
//Output: 3  
//Explanation: The longest common subsequence is "ace" and its length is 3.
// 
//
// Example 2: 
//
// 
//Input: text1 = "abc", text2 = "abc"
//Output: 3
//Explanation: The longest common subsequence is "abc" and its length is 3.
// 
//
// Example 3: 
//
// 
//Input: text1 = "abc", text2 = "def"
//Output: 0
//Explanation: There is no such common subsequence, so the result is 0.
// 
//
// 
// Constraints: 
//
// 
// 1 <= text1.length, text2.length <= 1000 
// text1 and text2 consist of only lowercase English characters. 
// 
// Related Topics String Dynamic Programming 
// 👍 3937 👎 44


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 二维DP
 * time：O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        int m = text1.size(), n = text2.size();
        // dp[i][j]表示text1在指针i，text2在指针j时所取得到的LCS
        // 如果把dp设为(m,n)，在下面循环从1开始时就无法考虑第一个字符，所以(m+1,n+1)
        vector<vector<int>> dp(m + 1, vector<int> (n + 1));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - 1][j - 1]);
                }
            }
        }

        return dp[m][n];
    }
};

/*
 * solution 2: 二维DP + 滚动数组
 * time：O(mn)
 * space: O(min(m, n)
 * */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        int m = text1.size(), n = text2.size();
        if (m > n) {
            return longestCommonSubsequence(text2, text1);
        }

        // dp[i][j]表示text1在指针i，text2在指针j时所取得到的LCS
        // 如果把dp设为(m,n)，在下面循环从1开始时就无法考虑第一个字符，所以(m+1,n+1)
        vector<vector<int>> dp(2, vector<int> (n + 1));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i % 2][j] = max(dp[(i - 1) % 2][j], dp[i % 2][j - 1]);

                if (text1[i - 1] == text2[j - 1]) {
                    dp[i % 2][j] = max(dp[i % 2][j], 1 + dp[(i - 1) % 2][j - 1]);
                }
            }
        }

        return dp[m % 2][n];
    }
};


/*
 * solution 3: dfs + memo
 * time：O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            return 0;
        }

        int m = text1.size(), n = text2.size();

        vector<vector<int>> memo(m + 1, vector<int> (n + 1));

        return dfsMemo(text1, text2, memo, m, n);
    }

    int dfsMemo(string &s1, string &s2,  vector<vector<int>> &memo, int m, int n) {
        if (memo[m][n] != 0) {
            return memo[m][n];
        }

        if(m == 0 || n == 0){
            return 0;
        }

        if (s1[m - 1] != s2[n - 1]) {
            memo[m][n - 1] = dfsMemo(s1, s2, memo, m, n - 1);
            memo[m - 1][n] = dfsMemo(s1, s2, memo, m - 1, n);
            memo[m][n] = max(memo[m][n - 1], memo[m - 1][n] );
        }
        else {
            memo[m - 1][n - 1] = dfsMemo(s1, s2, memo, m - 1, n - 1);
            memo[m][n] = 1 + memo[m - 1][n - 1];
        }

        return memo[m][n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
