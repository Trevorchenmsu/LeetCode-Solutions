//Given a string containing just the characters '(' and ')', find the length of 
//the longest valid (well-formed) parentheses substring. 
//
// 
// Example 1: 
//
// 
//Input: s = "(()"
//Output: 2
//Explanation: The longest valid parentheses substring is "()".
// 
//
// Example 2: 
//
// 
//Input: s = ")()())"
//Output: 4
//Explanation: The longest valid parentheses substring is "()()".
// 
//
// Example 3: 
//
// 
//Input: s = ""
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 0 <= s.length <= 3 * 104 
// s[i] is '(', or ')'. 
// 
// Related Topics String Dynamic Programming 
// 👍 5268 👎 191


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: stack + two pointers + sliding window
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int longestValidParentheses(string s) {
        int start = 0, res = 0;
        stack<int> Stack;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') Stack.push(i);
            else {
                if (Stack.empty()) start = i + 1;
                else {
                    Stack.pop();
                    res = Stack.empty() ? max(res, i - start + 1) : max(res, i - Stack.top());
                }
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
