//Given a string s representing a valid expression, implement a basic calculator
// to evaluate it, and return the result of the evaluation. 
//
// Note: You are not allowed to use any built-in function which evaluates string
//s as mathematical expressions, such as eval(). 
//
// 
// Example 1: 
//
// 
//Input: s = "1 + 1"
//Output: 2
// 
//
// Example 2: 
//
// 
//Input: s = " 2-1 + 2 "
//Output: 3
// 
//
// Example 3: 
//
// 
//Input: s = "(1+(4+5+2)-3)+(6+8)"
//Output: 23
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 3 * 105 
// s consists of digits, '+', '-', '(', ')', and ' '. 
// s represents a valid expression. 
// '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid). 
//
// '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid). 
//
// There will be no two consecutive operators in the input. 
// Every number and running calculation will fit in a signed 32-bit integer. 
// 
// Related Topics Math String Stack Recursion 
// 👍 2960 👎 258


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: stack + recursive，basic calculator的模板，容易记忆，但是空间复杂度大。面试可用这个模板，面试官要优化的话再用解法2
 * time: O(n)，只遍历一次字符串
 * space: O(n)，虽然说进入不同递归会产生递归栈，然后创建新的栈，但是栈中同时存储的最大数量只能是n个数字
 * */
class Solution {
public:
    int i = 0;
    int calculate(string s) {
        int num = 0, res = 0;
        int len = s.length();
        char op = '+'; //这里符号的初始化不用管字符串第一个是否为正还是负，如果是负，开头会被默认用+0处理，如-1+2转为+0-1+2
        stack<int> st;

        while (i < len) {
            char ch = s[i++];
            if ('0' <= ch && ch <= '9') {
                num = num * 10 + (ch - '0');
            }

            if (ch == '(') num = calculate(s);

            /*
             * 这里要额外加一个判定条件')'，因为我们是在遇到下一个数字的符号时才把符号上面的数组压栈
             * 如果没有这个判定条件，就不会把括号内的最后一个元素压栈。它的作用相当于对括号内的操作进行收尾。
             * 括号处理结束后，我们就在下一个if判定中跳出循环，计算括号内的结果
            */
            if (i == len || ch == '+' || ch == '-' || ch == ')') {
                if (op == '+') st.push(num);
                if (op == '-') st.push(-num);
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
 * solution 2: stack + no recursive，优化解法
 * time: O(n)，
 * space: O(n)，
 * */

class Solution {
public:
    int calculate(string s) {
        int sign = 1, res = 0;
        int len = s.length();
        stack<int> st;

        for (size_t i = 0; i < len; i++) {
            if (isdigit(s[i])) {
                int num = s[i] - '0';
                while (i + 1 < len && isdigit(s[i + 1])) {
                    num = num * 10 + (s[i + 1] - '0');
                    i++;
                }
                res += num * sign;
            }
            else if (s[i] == '+') sign = 1;
            else if (s[i] == '-') sign = -1;
            // 跟递归的思想一致，先把前面得到的结果和即将要计算的括号的符号存到栈里面，然后更新res和sign。等到后面括号内的
            // 内容计算结束后，再把这两个存的结果拿出来计算。
            else if (s[i] == '(') {
                st.push(res);
                st.push(sign);
                res = 0;
                sign = 1;
            }
            else if (s[i] == ')') {
                int pre_sign = st.top(); st.pop();
                int pre_res = st.top(); st.pop();
                res = pre_sign * res + pre_res;
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
