//Given a balanced parentheses string s, compute the score of the string based o
//n the following rule: 
//
// 
// () has score 1 
// AB has score A + B, where A and B are balanced parentheses strings. 
// (A) has score 2 * A, where A is a balanced parentheses string. 
// 
//
// 
//
// Example 1: 
//
// 
//Input: s = "()"
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: s = "(())"
//Output: 2
// 
//
// Example 3: 
//
// 
//Input: s = "()()"
//Output: 2
// 
//
// Example 4: 
//
// 
//Input: s = "(()(()))"
//Output: 6
// 
//
// 
//
// Note: 
//
// 
// s is a balanced parentheses string, containing only ( and ). 
// 2 <= s.length <= 50 
// 
// Related Topics String Stack 
// 👍 2251 👎 70


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int scoreOfParentheses(string s) {
        int res = 0;
        stack<int> Stack;
        for (auto &ch : s) {
            if (ch == '(') {
                Stack.push(res);
                res = 0;
            }
            else {
                res = Stack.top() + max(2 * res, 1);
                Stack.pop();
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
