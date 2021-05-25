//Given a string s containing only three types of characters: '(', ')' and '*', 
//return true if s is valid. 
//
// The following rules define a valid string: 
//
// 
// Any left parenthesis '(' must have a corresponding right parenthesis ')'. 
// Any right parenthesis ')' must have a corresponding left parenthesis '('. 
// Left parenthesis '(' must go before the corresponding right parenthesis ')'. 
//
// '*' could be treated as a single right parenthesis ')' or a single left paren
//thesis '(' or an empty string "". 
// 
//
// 
// Example 1: 
// Input: s = "()"
//Output: true
// Example 2: 
// Input: s = "(*)"
//Output: true
// Example 3: 
// Input: s = "(*))"
//Output: true
// 
// 
// Constraints: 
//
// 
// 1 <= s.length <= 100 
// s[i] is '(', ')' or '*'. 
// 
// Related Topics String 
// 👍 2412 👎 68


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool checkValidString(string s) {
        int lower=0;
        int upper=0;

        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
            {
                lower++;
                upper++;
            }
            else if (s[i]=='*')
            {
                lower--;
                upper++;
            }
            else if (s[i]==')')
            {
                lower--;
                upper--;
            }

            if (lower<0) lower=0;

            if (upper<0) return false;
        }

        return (lower==0);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
