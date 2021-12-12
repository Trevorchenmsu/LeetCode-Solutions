//Given an input string s and a pattern p, implement regular expression matching
// with support for '.' and '*' where: 
//
// 
// '.' Matches any single character. 
// '*' Matches zero or more of the preceding element. 
// 
//
// The matching should cover the entire input string (not partial). 
//
// 
// Example 1: 
//
// 
//Input: s = "aa", p = "a"
//Output: false
//Explanation: "a" does not match the entire string "aa".
// 
//
// Example 2: 
//
// 
//Input: s = "aa", p = "a*"
//Output: true
//Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, 
//by repeating 'a' once, it becomes "aa".
// 
//
// Example 3: 
//
// 
//Input: s = "ab", p = ".*"
//Output: true
//Explanation: ".*" means "zero or more (*) of any character (.)".
// 
//
// Example 4: 
//
// 
//Input: s = "aab", p = "c*a*b"
//Output: true
//Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, i
//t matches "aab".
// 
//
// Example 5: 
//
// 
//Input: s = "mississippi", p = "mis*is*p*."
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 20 
// 1 <= p.length <= 30 
// s contains only lowercase English letters. 
// p contains only lowercase English letters, '.', and '*'. 
// It is guaranteed for each appearance of the character '*', there will be a pr
//evious valid character to match. 
// 
// Related Topics String Dynamic Programming Recursion 
// 👍 6754 👎 946


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dp, two sequences
 * time: O(mn)
 * space: O(mn)
 *
 * */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool> (n + 1, false));

        s = "#" + s;
        p = "#" + p;

        // dp[i][0]=false, 因为p没有字符和s匹配，dp[0][0]，表示s和p都为空，当然匹配
        dp[0][0] = true;
        // dp[0][j]=?，s没有字符，p不一定得为空才能匹配，但是p必须是模式：x*x*x*x*...，这样可以*可以取0个x
        for (int j = 2; j <= n; j++) {
            if (p[j] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 条件1：p[j]为字母，它一定要等于s[i]，否则不匹配
                if (isalpha(p[j])) {
                    dp[i][j] = (p[j] == s[i]) && dp[i - 1][j - 1];
                }
                    // 条件2：p[j]为'.'，无论s[i]是哪个字符，都能匹配，所以取决于上一步
                else if (p[j] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                    // 条件3：p[j]为'*'时，需要分细节讨论
                else {
                    // 星号匹配上个元素的个数为0时，删掉上个元素及星号，所以j-2
                    bool possible1 = dp[i][j - 2];
                    /*
                       *匹配个数大于0，那么s[i]必须要跟p[j-1]一致，否则上一个元素怎么重复都没用
                       又或者p[j-1]为'.',这样就可以匹配任意s[i]，同时再考虑上一步的情况
                       注意这里时dp[i-1][j]而不是dp[i][j-1]，因为得保证s的前i-1是正确匹配的
                    */
                    bool possible2 = dp[i - 1][j] && (s[i] == p[j - 1] || p[j - 1] == '.');
                    dp[i][j] = possible1 || possible2;
                }
            }
        }

        return dp[m][n];
    }
};

//leetcode submit region end(Prohibit modification and deletion)
