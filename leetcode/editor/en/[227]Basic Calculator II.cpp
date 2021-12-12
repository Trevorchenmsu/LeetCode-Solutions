//Given a string s which represents an expression, evaluate this expression and 
//return its value. 
//
// The integer division should truncate toward zero. 
//
// You may assume that the given expression is always valid. All intermediate re
//sults will be in the range of [-231, 231 - 1]. 
//
// Note: You are not allowed to use any built-in function which evaluates string
//s as mathematical expressions, such as eval(). 
//
// 
// Example 1: 
// Input: s = "3+2*2"
//Output: 7
// Example 2: 
// Input: s = " 3/2 "
//Output: 1
// Example 3: 
// Input: s = " 3+5 / 2 "
//Output: 5
// 
// 
// Constraints: 
//
// 
// 1 <= s.length <= 3 * 105 
// s consists of integers and operators ('+', '-', '*', '/') separated by some n
//umber of spaces. 
// s represents a valid expression. 
// All the integers in the expression are non-negative integers in the range [0,
// 231 - 1]. 
// The answer is guaranteed to fit in a 32-bit integer. 
// 
// Related Topics Math String Stack 
// 👍 3037 👎 444


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int calculate(string s) {
        int num = 0, res = 0;
        int len = s.length();
        char op = '+';
        stack<int> st;

        for (size_t i = 0; i < len; i++) {
            char ch = s[i];
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
            }

            if (i == len - 1 || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (op == '+') st.push(num);
                if (op == '-') st.push(-num);
                if (op == '*') {
                    int val = st.top(); st.pop();
                    st.push(val * num);
                }
                if (op == '/') {
                    int val = st.top(); st.pop();
                    st.push(val / num);
                }

                num = 0;
                op = ch;
            }
        }

        while (!st.empty()) {
            res += st.top(); st.pop();
        }

        return res;
    }
};

/*
 * solution 2: no stack
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int calculate(string s) {
        int num = 0, res = 0;
        int pre = 0, len = s.length();
        char op = '+';

        for (size_t i = 0; i < len; i++) {
            char ch = s[i];
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + (ch - '0');
            }

            if (i == len - 1 || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (op == '+') {
                    res += num;
                    pre = num;
                }
                if (op == '-') {
                    res -= num;
                    pre = -num;
                }
                if (op == '*') {
                    res = res - pre + pre * num;
                    pre *= num;
                }
                if (op == '/') {
                    res = res - pre + pre / num;
                    pre /= num;
                }

                num = 0;
                op = ch;
            }
        }

        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
