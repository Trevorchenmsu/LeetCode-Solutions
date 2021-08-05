//Given a parentheses string s containing only the characters '(' and ')'. A par
//entheses string is balanced if: 
//
// 
// Any left parenthesis '(' must have a corresponding two consecutive right pare
//nthesis '))'. 
// Left parenthesis '(' must go before the corresponding two consecutive right p
//arenthesis '))'. 
// 
//
// In other words, we treat '(' as openning parenthesis and '))' as closing pare
//nthesis. 
//
// For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" a
//nd "(()))" are not balanced. 
//
// You can insert the characters '(' and ')' at any position of the string to ba
//lance it if needed. 
//
// Return the minimum number of insertions needed to make s balanced. 
//
// 
// Example 1: 
//
// 
//Input: s = "(()))"
//Output: 1
//Explanation: The second '(' has two matching '))', but the first '(' has only 
//')' matching. We need to to add one more ')' at the end of the string to be "(()
//)))" which is balanced.
// 
//
// Example 2: 
//
// 
//Input: s = "())"
//Output: 0
//Explanation: The string is already balanced.
// 
//
// Example 3: 
//
// 
//Input: s = "))())("
//Output: 3
//Explanation: Add '(' to match the first '))', Add '))' to match the last '('.
// 
//
// Example 4: 
//
// 
//Input: s = "(((((("
//Output: 12
//Explanation: Add 12 ')' to balance the string.
// 
//
// Example 5: 
//
// 
//Input: s = ")))))))"
//Output: 5
//Explanation: Add 4 '(' at the beginning of the string and one ')' at the end. 
//The string becomes "(((())))))))".
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 10^5 
// s consists of '(' and ')' only. 
// 
// Related Topics String Stack 
// 👍 327 👎 75


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: greedy
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int minInsertions(string s) {
        int cnt = 0, res = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                cnt++;
            else {
                if (i < s.size() - 1 && s[i + 1] == ')')
                    cnt--, i++;
                else
                    cnt--, res++;
            }
            if (cnt < 0)
                res++, cnt++;
        }

        return res + cnt * 2;
    }
};

/*
 * solution 2: greedy
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int minInsertions(string s) {
        int cnt = 0, res = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                cnt++;
            }
            else {
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    if (cnt > 0) cnt--;
                    else res++;
                    i++;
                }
                else {
                    if (cnt > 0)
                        res++,  cnt--;
                    else res += 2;
                }
            }
        }

        return res + cnt * 2;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
