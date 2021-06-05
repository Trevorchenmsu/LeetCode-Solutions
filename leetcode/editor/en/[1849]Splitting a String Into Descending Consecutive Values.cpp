//You are given a string s that consists of only digits. 
//
// Check if we can split s into two or more non-empty substrings such that the n
//umerical values of the substrings are in descending order and the difference bet
//ween numerical values of every two adjacent substrings is equal to 1. 
//
// 
// For example, the string s = "0090089" can be split into ["0090", "089"] with 
//numerical values [90,89]. The values are in descending order and adjacent values
// differ by 1, so this way is valid. 
// Another example, the string s = "001" can be split into ["0", "01"], ["00", "
//1"], or ["0", "0", "1"]. However all the ways are invalid because they have nume
//rical values [0,1], [0,1], and [0,0,1] respectively, all of which are not in des
//cending order. 
// 
//
// Return true if it is possible to split s as described above, or false otherwi
//se. 
//
// A substring is a contiguous sequence of characters in a string. 
//
// 
// Example 1: 
//
// 
//Input: s = "1234"
//Output: false
//Explanation: There is no valid way to split s.
// 
//
// Example 2: 
//
// 
//Input: s = "050043"
//Output: true
//Explanation: s can be split into ["05", "004", "3"] with numerical values [5,4
//,3].
//The values are in descending order with adjacent values differing by 1.
// 
//
// Example 3: 
//
// 
//Input: s = "9080701"
//Output: false
//Explanation: There is no valid way to split s.
// 
//
// Example 4: 
//
// 
//Input: s = "10009998"
//Output: true
//Explanation: s can be split into ["100", "099", "98"] with numerical values [1
//00,99,98].
//The values are in descending order with adjacent values differing by 1.
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 20 
// s only consists of digits. 
// 
// Related Topics String Backtracking Recursion 
// 👍 81 👎 46


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtracking, TLE
 * time: O(n^2)
 * space: O(n), stack space
 * */
class Solution {
public:
    bool splitString(string s) {
        if (s.size() <= 1)
            return false;

        for (size_t i = 0; i < s.size() - 1; i++) {
            long long val = stol(s.substr(0, i + 1));
            if (dfs(s, i + 1, val))
                return true;
        }

        return false;
    }
//"050043"
private:
    bool dfs(string &s, int idx, int val) {
        if (idx == s.size())
            return true;

        for (size_t j = idx; j < s.size(); j++) {
            long long num = stol(s.substr(idx, j - idx + 1));
            if (num + 1 == val && dfs(s, j + 1, num))
                return true;
        }

        return false;
    }
};

/*
 * solution 2: backtracking
 * time: O(n^2)
 * space: O(n), stack space
 * */
class Solution {
public:
    bool splitString(string s) {
        return dfs(s, 0);
    }

private:
    long long MAX = 999999999999;
    bool dfs(string &s, long long prev) {
        long long cur = 0;
        for (size_t i = 0; i < s.size(); i++) {
            cur = cur * 10 + s[i] - '0';
            if (cur > MAX) break;
            string next = s.substr(i + 1);
            if (prev == 0 && dfs(next, cur))
                return true;
            else if (cur + 1 == prev && (i == s.size() - 1 || dfs(next, cur)))
                return true;——ra
        }

        return false;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
