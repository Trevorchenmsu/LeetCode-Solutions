//A parentheses string is valid if and only if: 
//
// 
// It is the empty string, 
// It can be written as AB (A concatenated with B), where A and B are valid stri
//ngs, or 
// It can be written as (A), where A is a valid string. 
// 
//
// You are given a parentheses string s. In one move, you can insert a parenthes
//is at any position of the string. 
//
// 
// For example, if s = "()))", you can insert an opening parenthesis to be "(())
//)" or a closing parenthesis to be "())))". 
// 
//
// Return the minimum number of moves required to make s valid. 
//
// 
// Example 1: 
//
// 
//Input: s = "())"
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: s = "((("
//Output: 3
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 1000 
// s[i] is either '(' or ')'. 
// 
// Related Topics String Stack Greedy 
// 👍 1945 👎 107


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: iteration
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int minAddToMakeValid(string s) {
        int res = 0, cnt = 0;

        for (auto &ch : s) {
            if (ch == '(') cnt++;
            if (ch == ')') cnt--;
            if (cnt < 0) {
                res++;
                cnt++;
            }
        }

        return res + abs(cnt);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
