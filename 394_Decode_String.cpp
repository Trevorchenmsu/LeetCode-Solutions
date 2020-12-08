/*
solution 1: Stack
time:O(maxK⋅n), where maxK is the maximum value of k in the string s. 
    Example, for s = 1000[a200[b]], maxK is 1000
space: O(maxK⋅n), where maxK is the maximum value of k in the string s. 
        As we are pushing each decodedString to stack k times, 
        the maximum stack space required could be O(maxK⋅n).
*/
class Solution {
public:
    string decodeString(string s) {
        string res = "";
        if (s.empty() || s.size() == 0) 
            return res;
        
        stack<char> STACK;       
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ']') {
                // get the string in the bracket
                string decodeString = "";
                while (STACK.top() != '[') {
                    decodeString += STACK.top(); STACK.pop();
                }
                
                // remove '[' from the stack
                STACK.pop();
                
                // get the number in front of the bracket
                int k = 0, base = 1;
                while (!STACK.empty() && isdigit(STACK.top())) {
                    k += (STACK.top() - '0') * base; STACK.pop();
                    base *= 10;
                }
                
                // get the repeated string
                for (int i = 0; i < k; ++i) {
                    for (int j = decodeString.size() - 1; j >= 0; --j) {
                        STACK.push(decodeString[j]);
                    }
                } 
            } else STACK.push(s[i]);
        }
        
        // get the results from stack
        int size = STACK.size();
        for (int i = 0; i < size; ++i) {
            res = STACK.top() + res; STACK.pop();
        }

        return res;
    }
};



/*
solution 2: DFS
time:O(maxK⋅n), where maxK is the maximum value of k in the string s. 
    Example, for s = 1000[a200[b]], maxK is 1000
space: O(n), This is the space used to store the internal call stack used for recursion. 
             As we are recursively decoding each nested pattern, the maximum depth of recursive call stack 
             would not be more than n
*/
class Solution {
public:
    string decodeString(string s) {
        int index = 0;
        return dfs(s, index);
    }
    string dfs(const string& s, int& index) {
        string result;
        
        while (index < s.length() && s[index] != ']') {
            if (!isdigit(s[index]))
                result += s[index++];
            else {
                int k = 0;
                // build k until next character is a digit
                while (index < s.length() && isdigit(s[index]))
                    k = k * 10 + s[index++] - '0';  
                
                // ignore the opening bracket '['    
                ++index;
                string decodedString = dfs(s, index);
                
                // ignore the closing bracket ']'
                ++index;        
                while (k-- > 0)
                    result += decodedString;
            }
        }
        
        return result;
    }
};
