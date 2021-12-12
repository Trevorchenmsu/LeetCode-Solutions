//Implement a basic calculator to evaluate a simple expression string. 
//
// The expression string contains only non-negative integers, '+', '-', '*', '/'
// operators, and open '(' and closing parentheses ')'. The integer division shoul
//d truncate toward zero. 
//
// You may assume that the given expression is always valid. All intermediate re
//sults will be in the range of [-231, 231 - 1]. 
//
// Note: You are not allowed to use any built-in function which evaluates string
//s as mathematical expressions, such as eval(). 
//
// 
// Example 1: 
//
// 
//Input: s = "1+1"
//Output: 2
// 
//
// Example 2: 
//
// 
//Input: s = "6-4/2"
//Output: 4
// 
//
// Example 3: 
//
// 
//Input: s = "2*(5+5*2)/3+(6/2+8)"
//Output: 21
// 
//
// Example 4: 
//
// 
//Input: s = "(2+6*3+5-(3*14/7+2)*5)+3"
//Output: -12
// 
//
// Example 5: 
//
// 
//Input: s = "0"
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 1 <= s <= 104 
// s consists of digits, '+', '-', '*', '/', '(', and ')'. 
// s is a valid expression. 
// 
// Related Topics Math String Stack Recursion 
// 👍 696 👎 236


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack + recursion
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int i = 0;
    int calculate(string s) {
        int num = 0, res = 0;
        int len = s.length();
        char op = '+';
        stack<int> st;

        while (i < len) {
            char ch = s[i++];
            if ('0' <= ch && ch <= '9') {
                num = num * 10 + (ch - '0');
            }

            if (ch == '(') num = calculate(s);

            if (i == len || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')') {
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

            if (ch == ')') break;
        }

        while (!st.empty()) {
            res += st.top();
            st.pop();
        }

        return res;
    }
};


/*
 * solution 2: recursion，虽然节省了空间，但是还是推荐用解法1
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    int calculate(string s) {
        int n = s.length(), num = 0, curRes = 0, res = 0;
        char op = '+';

        for (int i = 0; i < n; ++i) {
            char c = s[i];

            if (c >= '0' && c <= '9') {
                num = num * 10 + c - '0';
            }
            else if (c == '(') {
                int j = i, cnt = 0;
                for (; i < n; ++i) {
                    if (s[i] == '(') ++cnt;
                    if (s[i] == ')') --cnt;
                    if (cnt == 0) break;
                }
                num = calculate(s.substr(j + 1, i - j - 1));
            }

            if (c == '+' || c == '-' || c == '*' || c == '/' || i == n - 1) {
                switch (op) {
                    case '+': curRes += num; break;
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }

                if (c == '+' || c == '-' || i == n - 1) {
                    res += curRes;
                    curRes = 0;
                }

                op = c;
                num = 0;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
