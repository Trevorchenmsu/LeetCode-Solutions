/*
solution 1: stack
time: O(n)
space: O(n)
*/

class Solution {
public:
    int calculate(string s) {
        if (s.empty() || s.size() == 0) {
            return 0;
        }
        
        stack<int> stacks;
        char sign = '+';
        long long num = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == s.size() - 1) {
                if (sign == '+') {
                    stacks.push(num);
                }
                if (sign == '-') {
                    stacks.push(-num);
                }
                if (sign == '*') {
                    int temp = stacks.top();
                    stacks.pop();
                    stacks.push(num * temp);
                }
                if (sign == '/') {
                    int temp = stacks.top();
                    stacks.pop();
                    stacks.push(temp / num);
                }
                sign = s[i];
                num = 0;
            }
        }
        
        long long res = 0;
        while (!stacks.empty()) {
            res += stacks.top();
            stacks.pop();
        }
        return int(res);
    }
};

/*
solution 2: non-stack
time: O(n)
space: O(1)
*/


class Solution {
public:
    /**
     * @param s: the given expression
     * @return: the result of expression
     */
    int calculate(string &s) {
        // Write your code here
        int val = 0, prev_val = 0, operand = 0;
        char op = '+';
        int n = s.size(); 
        if (n == 0) return 0;
        
        int i = 0;
        while (i < n) {
            if (isdigit(s[i])) {
                while (isdigit(s[i])) {
                    operand = operand * 10 + (s[i] - '0');
                    i++;
                }
                if (op == '+') {
                    val += operand;
                    prev_val = operand;
                } else if (op == '-') {
                    val -= operand;
                    prev_val = -operand;
                } else if (op == '*') {
                    val = val - prev_val + prev_val * operand;
                    prev_val *= operand;
                } else if (op == '/') {
                    val = val - prev_val + prev_val / operand;
                    prev_val /= operand;
                }
            } else if (s[i] == ' ') {
                i++;
            } else {
                operand = 0;
                op = s[i];
                i++;
            }
        }
        
        return val;
    }
};