/*
solution: recursive
time: O(n)
space: O(n)
*/

class Solution {
public:
    int calculate(string s) {
        int i = 0;
        return parseExpr(s, i);
    }
    
    int parseExpr(string& s, int& i) {
        vector<long long> nums;
        char op = '+';
        for (; i < s.length() && op != ')'; i++) {
            if (s[i] == ' ') continue;
            long long n = s[i] == '(' ? parseExpr(s, ++i) : parseNum(s, i);
            switch(op) {
                case '+' : nums.push_back(n); break;
                case '-' : nums.push_back(-n); break;
                case '*' : nums.back() *= n; break;
                case '/' : nums.back() /= n; break;
            }            
            op = s[i];
        }
        int res = 0;
        for (long long n : nums) res += n;
        return res;
    }
    
    long long parseNum(string& s, int& i) {
        long long n = 0;
        while(i < s.length() && isdigit(s[i]))
            n = s[i++] - '0' + 10 * n;
        return n;
    }
};