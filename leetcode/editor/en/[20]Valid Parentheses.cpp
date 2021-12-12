//Given a string s containing just the characters '(', ')', '{', '}', '[' and ']
//', determine if the input string is valid. 
//
// An input string is valid if: 
//
// 
// Open brackets must be closed by the same type of brackets. 
// Open brackets must be closed in the correct order. 
// 
//
// 
// Example 1: 
//
// 
//Input: s = "()"
//Output: true
// 
//
// Example 2: 
//
// 
//Input: s = "()[]{}"
//Output: true
// 
//
// Example 3: 
//
// 
//Input: s = "(]"
//Output: false
// 
//
// Example 4: 
//
// 
//Input: s = "([)]"
//Output: false
// 
//
// Example 5: 
//
// 
//Input: s = "{[]}"
//Output: true
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 104 
// s consists of parentheses only '()[]{}'. 
// 
// Related Topics String Stack 
// 👍 8494 👎 342


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool isValid(string s) {
        if (s.empty() || s.size() == 0) {
            return false;
        }

        stack<char> st;

        for (const auto& ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            }
            else  {
                if (!st.empty() && ch == ')' && st.top() != '(' ) {
                    return false;
                }

                if (!st.empty() && ch == ']' && st.top() != '[') {
                    return false;
                }

                if (!st.empty() && ch == '}' && st.top() != '{') {
                    return false;
                }

                if (st.empty()) {
                    return false;
                }

                st.pop();
            }
        }

        return st.empty();
    }
};

/*
 * solution 2: stack, optimal
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool isValid(string s) {
        if (s.empty()) {
            return false;
        }

        stack<char> Stack;
        for (const auto& c : s) {
            if (c == '(') {
                Stack.push(')');
            }
            else if (c == '[') {
                Stack.push(']');
            }
            else if (c == '{')  {
                Stack.push('}');
            }
            else if (Stack.empty() || Stack.top() != c)
                return false;

            else Stack.pop();
        }

        return Stack.empty();
    }
};
//leetcode submit region end(Prohibit modification and deletion)
