//You are given a string containing only 4 kinds of characters 'Q', 'W', 'E' and
// 'R'. 
//
// A string is said to be balanced if each of its characters appears n/4 times w
//here n is the length of the string. 
//
// Return the minimum length of the substring that can be replaced with any othe
//r string of the same length to make the original string s balanced. 
//
// Return 0 if the string is already balanced. 
//
// 
// Example 1: 
//
// 
//Input: s = "QWER"
//Output: 0
//Explanation: s is already balanced. 
//
// Example 2: 
//
// 
//Input: s = "QQWE"
//Output: 1
//Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is ba
//lanced.
// 
//
// Example 3: 
//
// 
//Input: s = "QQQW"
//Output: 2
//Explanation: We can replace the first "QQ" to "ER". 
// 
//
// Example 4: 
//
// 
//Input: s = "QQQQ"
//Output: 3
//Explanation: We can replace the last 3 'Q' to make s = "QWER".
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 10^5 
// s.length is a multiple of 4 
// s contains only 'Q', 'W', 'E' and 'R'. 
// 
// Related Topics Two Pointers String 
// 👍 480 👎 105


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: two pointers + sliding window
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int balancedString(string s) {
        if (s.empty()) return 0;
        int len = s.length();
        if (len < 4 || len % 4 != 0) return 0;
        int n = len / 4;
        unordered_map<char, int> cnt_map;

        for (auto& c : s)
            cnt_map[c]++;

        if (cnt_map['Q'] == n && cnt_map['W'] == n && cnt_map['E'] == n && cnt_map['R'] == n )
            return 0;

        int res = len, left = 0, right = 0;
        while (right < len) {
            cnt_map[s[right]]--;
            while (left <= right + 1 && cnt_map['Q'] <= n && cnt_map['W'] <= n &&
                    cnt_map['E'] <= n && cnt_map['R'] <= n ) {
                res = min(res, right - left + 1);
                cnt_map[s[left++]]++;
            }
            right++;
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
