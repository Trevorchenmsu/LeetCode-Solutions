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
    int calculate(string s) {
        int res = 0, prev_val = 0;
        if (s.empty() || s.size() == 0) {
            return res;
        }
        
        long long num = 0;
        char sign = '+';
      
        for (int i = 0; i < s.size(); ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + s[i] - '0';
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == s.size() - 1) {
                if (sign == '+') {
                    res += num;
                    prev_val = num;
                }
                if (sign == '-') {
                    res -= num;
                    prev_val = -num;
                }
                if (sign == '*') {
                    res = res - prev_val + prev_val * num;
                    prev_val *= num;
                }
                if (sign == '/') {
                    res = res - prev_val + prev_val / num;
                    prev_val /= num;
                }
                sign = s[i];
                num = 0;
            }
        }
        
        return res;
    }
};