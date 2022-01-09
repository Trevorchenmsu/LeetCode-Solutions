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

// 卡点：
// （1）遇到星号怎么处理？（2）把它跟左括号一起存到栈中还是用另外一个栈单独存星号？
// （3）如果同时存在栈中，遇到右括号时，如何知道啥时候用星号，啥时候用左括号？有时候也可以是右括号

// 思路一：分开存。先正常处理正常配对的括号。如果右括号出现后，左括号栈为空，开始考虑星号栈，看它的位置是否在右括号前。
// 如果结束后左括号栈为不空，开始考虑星号栈的位置跟左括号匹配。

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
 * solution 1: two stacks, another form
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left_stack, star_stack;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') left_stack.push(i);
            else if (s[i] == '*') star_stack.push(i);
            else {
                if (!left_stack.empty()) left_stack.pop();
                else if (!star_stack.empty()) star_stack.pop();
                else return false;
            }
        }

        while (!left_stack.empty() && !star_stack.empty()) {
            if (left_stack.top() < star_stack.top()) {
                left_stack.pop();
                star_stack.pop();
            }
            else return false;
        }

        // if (left_stack.empty()) return true;
        // else if (star_stack.empty()) return false;
        // return true;

        return left_stack.empty();
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
        int cnt = 0, right = 0, n = s.size();

        // pass one: 从左到右，遇到括号和星号计数器都加一，遇到右括号计数器加一，如果计数器小于0，表明先遇到右括号，不满足要求返回false
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
            遍历时，right就会出现负数的情况，因为左括号偏多，所以无法匹配，返回false。如果下面循环结束后没有返回false，则表示上面
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
        int lower = 0, upper = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                lower++;
                upper++;
            }
            else if (s[i] == '*')
            {
                lower--;
                upper++;
            }
            else if (s[i] == ')')
            {
                lower--;
                upper--;
            }

            if (lower < 0) lower = 0;

            if (upper < 0) return false;
        }

        return lower == 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
