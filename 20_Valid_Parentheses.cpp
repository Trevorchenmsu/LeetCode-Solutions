/*
solution: stack
time: O(n)
space: O(n)
*/

class Solution {
public:
    bool isValid(string s) {
        if (s.empty()) return false;
        
        stack<char> Stack;
        for (const auto& c : s) {
            if (c == '(')  Stack.push(')');
            else if (c == '[')  Stack.push(']');
            else if (c == '{')  Stack.push('}');
            else if (Stack.empty() || Stack.top() != c) 
                return false;
            else Stack.pop();
        }
        
        return Stack.empty();
    }
};