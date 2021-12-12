//Given two strings word1 and word2, return the minimum number of operations req
//uired to convert word1 to word2. 
//
// You have the following three operations permitted on a word: 
//
// 
// Insert a character 
// Delete a character 
// Replace a character 
// 
//
// 
// Example 1: 
//
// 
//Input: word1 = "horse", word2 = "ros"
//Output: 3
//Explanation: 
//horse -> rorse (replace 'h' with 'r')
//rorse -> rose (remove 'r')
//rose -> ros (remove 'e')
// 
//
// Example 2: 
//
// 
//Input: word1 = "intention", word2 = "execution"
//Output: 5
//Explanation: 
//intention -> inention (remove 't')
//inention -> enention (replace 'i' with 'e')
//enention -> exention (replace 'n' with 'x')
//exention -> exection (replace 'n' with 'c')
//exection -> execution (insert 'u')
// 
//
// 
// Constraints: 
//
// 
// 0 <= word1.length, word2.length <= 500 
// word1 and word2 consist of lowercase English letters. 
// 
// Related Topics String Dynamic Programming 
// 👍 6781 👎 84


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 二维dp，匹配型
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.size() == 0) {
            return word2.size();
        }

        if (word2.size() == 0) {
            return word1.size();
        }

        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int> (n + 1));

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        /*
            dp[i][j-1]表示插入的情况，例如下面，末端两个s已经匹配了，此时word1的i不动，word2需要考虑前j-1的情况
            horse, ros->在horse末端插入s->horse s, ro s
                i    j                       i     j-1
            dp[i][j-1]表示删除的情况，例如下面，删除后e后两个s可以匹配，所以j不动，word1则考虑前i-1的情况
            horse, ros->在horse末端删除e->hors , ros
                i    j                       i    j
            dp[i-1][j-1]表示替换的情况。当word1[i]和word2[j]不等时，替换一次即可满足相等。如果相等，无需操作。
        */
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;

                // 在使用匹配型动态规划时，要注意原始单词取下标需要减1。因为dp数组加1了。
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
                }
                else {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                }
            }
        }

        return dp[m][n];
    }
};


/*
 * solution 2: 二维dp，匹配型，滚动数组优化
 * time: O(mn)
 * space: O(n)
 * */
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.size() == 0) {
            return word2.size();
        }

        if (word2.size() == 0) {
            return word1.size();
        }

        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(2, vector<int> (n + 1));

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        /*
            dp[i][j-1]表示插入的情况，例如下面，末端两个s已经匹配了，此时word1的i不动，word2需要考虑前j-1的情况
            horse, ros->在horse末端插入s->horse s, ro s
                i    j                       i     j-1
            dp[i][j-1]表示删除的情况，例如下面，删除后e后两个s可以匹配，所以j不动，word1则考虑前i-1的情况
            horse, ros->在horse末端删除e->hors , ros
                i    j                       i    j
            dp[i-1][j-1]表示替换的情况。当word1[i]和word2[j]不等时，替换一次即可满足相等。如果相等，无需操作。
        */
        for (int i = 1; i <= m; i++) {
            dp[i % 2][0] = i;

            for (int j = 1; j <= n; j++) {
                dp[i % 2][j] = min(dp[(i - 1) % 2][j], dp[i % 2][j - 1]) + 1;

                // 在使用匹配型动态规划时，要注意原始单词取下标需要减1。因为dp数组加1了。
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j - 1]);
                }
                else {
                    dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j - 1] + 1);
                }
            }
        }

        return dp[m % 2][n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
