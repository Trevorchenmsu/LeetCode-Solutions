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
/*
 * solution 1: two stacks
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left, star;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                left.push(i);
            }
            else if (s[i] == '*') {
                star.push(i);
            }
            else {
                if (left.empty() && star.empty()) {
                    return false;
                }
                left.empty() ? star.pop() : left.pop();
            }
        }

        while (!left.empty() && !star.empty()) {
            if (left.top() > star.top()) {
                return false;
            }
            left.pop();
            star.pop();
        }

        return left.empty();
    }
};


/*
 * solution 2: two passes
 * time: O(n)
 * space: O(1)
 * */

class Solution {
public:
    bool checkValidString(string s) {
        int left = 0, right = 0, n = s.size();

        for (int i = 0; i < n; i++) {
            if (s[i] == '(' || s[i] =='*') {
                left++;
            }
            else {
                left--;
            }

            if (left < 0) {
                return false;
            }
        }

        if (left == 0) {
            return true;
        }

        /*
            如果能够进入下一个for，表明left大于0。则多余的左括号可能是由星号转变而来或者是本身真实多余的
            左括号。那么就需要下面反向扫描来判定是哪种情况。如果多余情况是由真实多余左括号导致，那么在下面
            遍历时，right就会出现负数的情况，因为左括号偏多。如果下面循环结束后没有返回false，则表示上面
            循环得到的结果是由星号导致的。而星号可为空，不管怎样匹配都行，所以返回true。
        */

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == ')' || s[i] == '*') {
                right++;
            }
            else {
                right--;
            }

            if (right < 0) {
                return false;
            }
        }


        return true;
    }
};


/*
 * solution 3: one pass
 * time: O(n)
 * space: O(1)
 * */
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
