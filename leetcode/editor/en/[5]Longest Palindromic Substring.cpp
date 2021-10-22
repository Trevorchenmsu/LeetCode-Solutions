//Given a string s, return the longest palindromic substring in s. 
//
// 
// Example 1: 
//
// 
//Input: s = "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
// 
//
// Example 2: 
//
// 
//Input: s = "cbbd"
//Output: "bb"
// 
//
// Example 3: 
//
// 
//Input: s = "a"
//Output: "a"
// 
//
// Example 4: 
//
// 
//Input: s = "ac"
//Output: "a"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// s consist of only digits and English letters (lower-case and/or upper-case), 
//
// Related Topics String Dynamic Programming 
// 👍 10484 👎 679


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: two pointers
 * time: O(n^2)
 * space: O(1)
 * */
class Solution {
public:
    string longestPalindrome(string s) {
        string res = "";

        for (int i = 0; i < s.size(); i++) {
            // when the length of palindrome is odd
            string oddPalindrome = getPalindrome(s, i, i);
            res = res.size() > oddPalindrome.size() ? res : oddPalindrome;

            // when the length of palindrome is even
            string evenPalindrome = getPalindrome(s, i, i + 1);
            res = res.size() > evenPalindrome.size() ? res : evenPalindrome;
        }

        return res;
    }
private:

    string getPalindrome(string &s, int left, int right) {
        while (left >= 0 && right < s.size()) {
            if (s[left] != s[right])
                break;
            left--, right++;
        }

        return s.substr(left + 1, right - 1 - left);
    }
};


/*
 * solution 2: dp，区间型dp，先循环区间长度，再循环区间起点
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        int dp[n][n];

        // initialize: one character string and empty string
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            if (i > 0)
                dp[i][i - 1] = 1; // empty string is also palindrome
        }

        int start = 0, len = 1; // start from one character
        for (int length = 2; length <= n; length++) {
            for (int left = 0; left + length <= n; left++) {
                int right = left + length - 1;
                dp[left][right] = dp[left + 1][right - 1] && s[left] == s[right];
                if (dp[left][right] == 1 && length > len) {
                    len = length;
                    start = left;
                }
            }
        }

        return s.substr(start, len);
    }

};



/*
 * solution 3: dp, optimal
 * time: O(n^2)
 * space: O(n^2)
 * */
class Solution {
public:
    string longestPalindrome(string s) {
        int start = 0, len = 1, n = s.size();
        int dp[n][n];

        for (int right = 0; right < n; right++) {
            dp[right][right] = 1;
            for (int left = 0; left < right; left++) {
                dp[left][right] = (dp[left + 1][right - 1] || right - left < 2) && s[left] == s[right];
                if (dp[left][right] && len < right - left + 1) {
                    len = right - left + 1;
                    start = left;
                }
            }
        }

        return s.substr(start, len);
    }

};
//leetcode submit region end(Prohibit modification and deletion)
