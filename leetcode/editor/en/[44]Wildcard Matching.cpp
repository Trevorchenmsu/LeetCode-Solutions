//Given an input string (s) and a pattern (p), implement wildcard pattern matchi
//ng with support for '?' and '*' where: 
//
// 
// '?' Matches any single character. 
// '*' Matches any sequence of characters (including the empty sequence). 
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
//Input: s = "aa", p = "*"
//Output: true
//Explanation: '*' matches any sequence.
// 
//
// Example 3: 
//
// 
//Input: s = "cb", p = "?a"
//Output: false
//Explanation: '?' matches 'c', but the second letter is 'a', which does not mat
//ch 'b'.
// 
//
// Example 4: 
//
// 
//Input: s = "adceb", p = "*a*b"
//Output: true
//Explanation: The first '*' matches the empty sequence, while the second '*' ma
//tches the substring "dce".
// 
//
// Example 5: 
//
// 
//Input: s = "acdcb", p = "a*c?b"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 0 <= s.length, p.length <= 2000 
// s contains only lowercase English letters. 
// p contains only lowercase English letters, '?' or '*'. 
// 
// Related Topics String Dynamic Programming Greedy Recursion 
// 👍 3716 👎 163


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 二维dp, 前缀型-字符串匹配型
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp (m + 1, vector<bool> (n + 1, false));

        s = "#" + s;
        p = "#" + p;

        dp[0][0] = true;
        // 当s为空串，只有当p中的前若干个都是星号时才能匹配，否则就跳出
        for (int j = 1; j <= n; j++) {
            if (p[j] != '*') {
                break;
            }
            dp[0][j] = true;
        }

        // 判定取决于p的当前字符
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 如果当前p字符为字母，则s字符必须为相同字符，且上一轮的状态必须为true才能使这一轮状态为true
                if (isalpha(p[j])) {
                    dp[i][j] = (s[i] == p[j]) && dp[i - 1][j - 1];
                }
                // 如果当前p字符为'?'，则s字符可以是任意字符，所以当前状态直接取决于上一轮的状态。
                else if (p[j] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                /*
                如果当前p字符为'*'，它可以匹配当前s在i位置以及之前的任意多个元素（k=0，1，2，...,i），只要其中一种为true即可，
                所以：
                    for (int k=0; k<=i; k++)
                     if (dp[k][j-1]==1) dp[i][j]=1;

                将上式展开：
                dp[i][j] = dp[0][j-1] || dp[1][j-1] || dp[2][j-1] || ... || dp[i-1][j-1] || dp[i][j-1]
                将i用i-1替换，可得
                dp[i-1][j] = dp[0][j-1] || dp[1][j-1] || dp[2][j-1] || ... || dp[i-1][j-1]。
                用第二式替换第一式左边的大部分项，就有dp[i][j] = dp[i-1][j] || dp[i][j-1]
                这一步操作比较tricky，不是很容易想到。
                */
                else {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }
};

/*
 * solution 2: 二维dp, 前缀型-字符串匹配型，滚动数组
 * time: O(mn)
 * space: O(n)
 * */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp (2, vector<bool> (n + 1, false));

        s = "#" + s;
        p = "#" + p;

        dp[0][0] = true;
        for (int j = 1; j <= n; j++) {
            if (p[j] != '*') {
                break;
            }
            dp[0][j] = true;
        }

        for (int i = 1; i <= m; i++) {
            dp[i % 2][0] = false; // 除了求模外，比解法2多加了这一步
            for (int j = 1; j <= n; j++) {
                if (isalpha(p[j])) {
                    dp[i % 2][j] = (s[i] == p[j]) && dp[(i - 1) % 2][j - 1];
                }
                else if (p[j] == '?') {
                    dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
                }
                else {
                    dp[i % 2][j] = dp[i % 2][j - 1] || dp[(i - 1) % 2][j];
                }
            }
        }

        return dp[m % 2][n];
    }
};



/*
 * solution 3: dfs + memo
 * time: O(mn)
 * space: O(mn)
 * */
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> memo(m, vector<int> (n, -1));
        return dfsMemo(s, 0, p, 0, memo);
    }

    bool dfsMemo(string &s, int sIndex, string &p, int pIndex, vector<vector<int>> &memo) {
        if (pIndex == p.size()) {
            return sIndex == s.size();
        }

        if (sIndex == s.size()) {
            return allStar(pIndex, p);
        }

        // 这个放在最前面就会产生栈溢出，为什么？
        if (memo[sIndex][pIndex] != -1) {
            return memo[sIndex][pIndex];
        }

        bool match;
        if (p[pIndex] == '*') {
            match = dfsMemo(s, sIndex, p, pIndex + 1, memo) ||
                    dfsMemo(s, sIndex + 1, p, pIndex, memo);
        }
        else {
            match = charMatch(s[sIndex], p[pIndex]) &&
                    dfsMemo(s, sIndex + 1, p, pIndex + 1, memo);
        }

        memo[sIndex][pIndex] = match;
        return match;
    }

    bool charMatch(char sChar, char pChar) {
        return sChar == pChar || pChar == '?';
    }

    bool allStar(int pIndex, string &p) {
        for (int i = pIndex; i < p.size(); i++) {
            if (p[i] != '*') {
                return false;
            }
        }
        return true;
    }
};


/*
 * solution 4: two pointers, optimal
 * time: O(m)
 * space: O(1)
 * */
class Solution {
public:
    bool isMatch(string s, string p) {
        int sIndex = 0, pIndex = 0;
        int match = 0, star = -1;

        while (sIndex < s.size()) {
            // 当s和p的字符相等或p字符为'?'，两者匹配，各自指针前进
            if (pIndex < p.size() && (s[sIndex] == p[pIndex]) || p[pIndex] == '?') {
                pIndex++;
                sIndex++;
            }
            // 当p为'*'时，用当前位置更新star，同时用s指针标志match起点
            else if (pIndex < p.size() && p[pIndex] == '*') {
                star = pIndex;
                match = sIndex;
                pIndex++;
            }
            else if (star != -1) {
                pIndex = star + 1;
                match++;
                sIndex = match;
            }
            else {
                return false;
            }
        }

        while (pIndex < p.size() && p[pIndex] == '*') {
            pIndex++;
        }

        return pIndex == p.size();
    }
};

//leetcode submit region end(Prohibit modification and deletion)
