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
例子:3+2*2，默认第一个为整数，所以有+3+2*2
初始sign='+'，num=0，res=0，遇到第一个3后，num=3，继续前进遇到加号，此时开始计算前面的结果
res=num + res=3，放入栈中，num置为0，用新的加号替换之前初始加号。继续前进遇到2，更新num=2，继续前进遇到乘号
开始处理前面结果。当前char为*，sign为+。res=stack.top+num=5，再更新栈。num置为0，sign置为*号。
继续前进到2，走完公式，得到num=2.开始处理结果，当前sign为*，用num乘以stack.top肯定不对，需要栈顶值减去之前的3才是正确值。
问题来了，如何跟进前面的数2以及2前面的符号+？我的思路是添加另外两个变量跟进上一个数和符号，技术上可行，更好的方式是把上一个数带着正号或者符号存入栈，在乘除的时候再计算。

如果是3/2*2？按顺序结果是2，后面先算再除前面，结果是0，如何处理？只有加减号才弹出然后逆运算，乘除的时候不需要，按照顺序处理即可
*/

/*
 * solution 1: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int calculate(string s) {
        char sign = '+';
        long long num = 0;
        stack<int> st;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') continue;
            if (isdigit(s[i]))
            {
                while (i < s.size() && isdigit(s[i])) num = num * 10 + s[i++] - '0';
            }
            if (sign == '+') st.push(num);
            if (sign == '-') st.push(-num);
            if (sign == '*') {
                int val = st.top() * num; st.pop();
                st.push(val);
            }
            if (sign == '/') {
                int val = st.top() / num; st.pop();
                st.push(val);
            }
            num = 0;
            sign = s[i];
        }

        int res = 0;
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
        char sign = '+';
        long long num = 0;
        int res = 0, pre = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == ' ') continue;

            if (isdigit(s[i]))
            {
                while (i < s.size() && isdigit(s[i]))
                    num = num * 10 + s[i++] - '0';
            }

            if (sign == '+') {
                res += num;
                pre = num;
            }
            if (sign == '-') {
                res -= num;
                pre = -num;
            }
            if (sign == '*') {
                res -= pre;
                res += pre * num;
                pre = pre * num;
            }
            if (sign == '/') {
                res -= pre;
                res += pre / num;
                pre = pre / num;
            }

            num = 0;
            sign = s[i]; //这里i=s.size()时仍然能够通过，这是因为字符串最后一个字符是以0/存在的，所以不是空的，对于python就不行了
        }

        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)
