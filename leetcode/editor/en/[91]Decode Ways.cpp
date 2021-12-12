//A message containing letters from A-Z can be encoded into numbers using the fo
//llowing mapping: 
//
// 
//'A' -> "1"
//'B' -> "2"
//...
//'Z' -> "26"
// 
//
// To decode an encoded message, all the digits must be grouped then mapped back
// into letters using the reverse of the mapping above (there may be multiple ways
//). For example, "11106" can be mapped into: 
//
// 
// "AAJF" with the grouping (1 1 10 6) 
// "KJF" with the grouping (11 10 6) 
// 
//
// Note that the grouping (1 11 06) is invalid because "06" cannot be mapped int
//o 'F' since "6" is different from "06". 
//
// Given a string s containing only digits, return the number of ways to decode 
//it. 
//
// The answer is guaranteed to fit in a 32-bit integer. 
//
// 
// Example 1: 
//
// 
//Input: s = "12"
//Output: 2
//Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
// 
//
// Example 2: 
//
// 
//Input: s = "226"
//Output: 3
//Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2
// 6).
// 
//
// Example 3: 
//
// 
//Input: s = "0"
//Output: 0
//Explanation: There is no character that is mapped to a number starting with 0.
//
//The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20", neither of whi
//ch start with 0.
//Hence, there are no valid ways to decode this since all digits need to be mapp
//ed.
// 
//
// Example 4: 
//
// 
//Input: s = "06"
//Output: 0
//Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is 
//different from "06").
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 100 
// s contains only digits and may contain leading zero(s). 
// 
// Related Topics String Dynamic Programming 
// 👍 5515 👎 3600


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: dfs + memo
 * time: O(n)
 * space: O(n)
 * */

/*
这道题的corner case比较tricky，20只能是20，不能是2和0，已经限定了在1-26之间。
对于0在起点和中间的情况，都不是通路，如909，会产生9，09，所以无效。
*/
class Solution {
public:
    int numDecodings(string s) {
        unordered_map<int, int> memo;
        return dfsMemo(0, s, memo);
    }

    int dfsMemo(int idx, string &s, unordered_map<int, int> &memo) {
        if (memo.find(idx) != memo.end()) {
            return memo[idx];
        }

        if (idx == s.size()) {
            return 1;
        }

        if (s[idx] == '0') {
            return 0;
        }

        if (idx == s.size() - 1) {
            return 1;
        }

        // 因为只考虑了一个字符，所以不用管有没有heading zero。
        int res = dfsMemo(idx + 1, s, memo);

        if (stoi(s.substr(idx, 2)) <= 26) {
            res += dfsMemo(idx + 2, s, memo);
        }

        memo[idx] = res;
        return res;
    }
};

/*
 * solution 2: dp，前缀划分型
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s.size() == 0) {
            return 0;
        }

        int n = s.size();

        // dp[i]表示在i时所得到的解码总数。为了dp后续计算有效，这里设定dp[0]=1，
        // 例如'10'有一种解码方式，dp[2]=dp[0]*1+dp[1]*0 （因为拆成'1'和'0‘是非法的），所以这里只有设dp[0]=1才有效
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = decodeOK(s[0]);

        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] * decodeOK(s.substr(i - 1, 1)) +
                    dp[i - 2] * decodeOK(s.substr(i - 2, 2));
        }

        return dp[n];
    }

    int decodeOK(string s) {
        int num = stoi(s), len = s.size();
        if (len == 1 && num <= 9 && num >= 1) {
            return 1;
        }

        if (len == 2 && num <= 26 && num >= 10) {
            return 1;
        }

        return 0;
    }
};

/*
 * solution 3: dp，滚动数组优化
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s.size() == 0) {
            return 0;
        }

        int n = s.size();

        vector<int> dp(3);
        dp[0] = 1;
        dp[1] = decodeOK(s.substr(0, 1));

        for (int i = 2; i <= n; i++) {
            dp[i % 3] = dp[(i - 1) % 3] * decodeOK(s.substr(i - 1, 1)) +
                        dp[(i - 2) % 3] * decodeOK(s.substr(i - 2, 2));
        }

        return dp[n % 3];
    }

    int decodeOK(string s) {
        int num = stoi(s), len = s.size();
        if (len == 1 && num <= 9 && num >= 1) {
            return 1;
        }

        if (len == 2 && num <= 26 && num >= 10) {
            return 1;
        }

        return 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
