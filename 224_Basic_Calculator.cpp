/*
solution: stack
time: O(n), traverse the string
space: O(n), the worst case is to store all the characters
*/

class Solution {
public:
    int calculate(string s) {
        stack<int> stk;
        int sign = 1;
        int res = 0;
        for(int i = 0; i < s.size(); i++){
            if(isdigit(s[i])){
                unsigned int num = s[i] - '0';
                while(i + 1 < s.size() && isdigit(s[i+1])){
                    num = 10 * num + s[i+1] - '0' ;
                    i++;
                }
                res += num * sign;
            }
            else if(s[i] == '+'){
                sign = 1;
            }
            else if(s[i] == '-'){
                sign = -1;
            }
            else if(s[i] == '('){
                stk.push(res);
                stk.push(sign);
                res = 0;
                sign = 1;
            }
            else if(s[i] == ')'){
                int temp1 = stk.top(); stk.pop();
                int temp2 = stk.top(); stk.pop(); 
                res = res * temp1 + temp2;
            }
        }
        return res;
    }
};