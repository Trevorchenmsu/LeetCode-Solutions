//Given a string s of '(' , ')' and lowercase English characters. 
//
// Your task is to remove the minimum number of parentheses ( '(' or ')', in any
// positions ) so that the resulting parentheses string is valid and return any va
//lid string. 
//
// Formally, a parentheses string is valid if and only if: 
//
// 
// It is the empty string, contains only lowercase characters, or 
// It can be written as AB (A concatenated with B), where A and B are valid stri
//ngs, or 
// It can be written as (A), where A is a valid string. 
// 
//
// 
// Example 1: 
//
// 
//Input: s = "lee(t(c)o)de)"
//Output: "lee(t(c)o)de"
//Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
// 
//
// Example 2: 
//
// 
//Input: s = "a)b(c)d"
//Output: "ab(c)d"
// 
//
// Example 3: 
//
// 
//Input: s = "))(("
//Output: ""
//Explanation: An empty string is also valid.
// 
//
// Example 4: 
//
// 
//Input: s = "(a(b(c)d)"
//Output: "a(b(c)d)"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 10^5 
// s[i] is one of '(' , ')' and lowercase English letters. 
// Related Topics String Stack 
// 👍 2167 👎 50

//Input: s = "(a(b(c)d)"
//Output: "a(b(c)d)"

//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> Stack;
        string res;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                Stack.push(i);
            else if (s[i] == ')') {
                // 右括号先出现，不合理，先保留位置，但置为空。
                if (Stack.empty())
                    s[i] = ' ';
                else
                    Stack.pop(); // match a left parenthesis
            }
        }

        // 当有效的右括号都被匹配完了以后，左括号还有剩余，需要置为空
        while (!Stack.empty()) {
            s[Stack.top()] = ' ';
            Stack.pop();
        }

        for (auto &ch : s)
            if (ch != ' ')
                res.push_back(ch);

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
