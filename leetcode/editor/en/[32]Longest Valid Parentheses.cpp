//Given a string containing just the characters '(' and ')', find the length of 
//the longest valid (well-formed) parentheses substring. 
//
// 
// Example 1: 
//
// 
//Input: s = "(()"
//Output: 2
//Explanation: The longest valid parentheses substring is "()".
// 
//
// Example 2: 
//
// 
//Input: s = ")()())"
//Output: 4
//Explanation: The longest valid parentheses substring is "()()".
// 
//
// Example 3: 
//
// 
//Input: s = ""
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 0 <= s.length <= 3 * 104 
// s[i] is '(', or ')'. 
// 
// Related Topics String Dynamic Programming 
// 👍 5268 👎 191


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * Solution 1: stack + two pointers + sliding window
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0, res = 0;
        stack<int> st;

        for (int right = 0; right < s.size(); right++) {
            if (s[right] == '(') {
                st.push(right);
            }
            else {
                if (st.empty()){
                    left = right + 1; //检查越界？不需要，因为没有用left作为下标
                }
                else {
                    /*
                     * 卡点：第一个例子中，如何实现相减的长度不考虑第一个左括号的位置？虽然用栈可以实现，
                     * 但是这样的话括号匹配只会找最近的左括号，那么在第二个例子中，就不能找匹配第一个的左括号找到最长的距离
                     * */

                    //错误实现：
//                    int cur = st.top(); st.pop();
//                    int len = right - min(cur, left) + 1;
//                    res = max(res, len);
                    // 修正：
//                    int cur = st.top(); st.pop();
//                    int len = right - left + 1;
//                    res = st.empty() ? max(res, len) : max(res, right - st.top());

                    /* ) ( ) ( ) )
                     * 0 1 2 3 4 5
                     * i=0，右括号且空栈，left=1；i=1，左括号且存1到栈中，left=1；i=2，右括号且非空栈，先弹栈，1被删除，变空栈，
                     * 结果是right-left+1=2-1+1=2，此时是普通的一对括号匹配，因为仍为有效括号，所以left没变化；
                     * i=3，左括号且存3到栈中，left=1；i=4，右括号且非空栈，先弹栈，3被删除被空栈，结果仍然是right-left+1=4-1+1=4，
                     * 也就是说right-left+1求的都是有效括号区间，用打擂台得到最长长度；i=5，left跳到5后，后面就结束了循环。
                     * ( ( )
                     * 0 1 2
                     * i=0, 左括号0入栈；i=1，左括号1入栈；i=2，右括号且非空栈，弹栈1被删除剩下0，非空栈，选择right-st.top()=2-0=2
                     * 为什么这里要用right-st.top()？进入这个if else表明遇到了右括号，当弹栈后仍为非空栈，表明当前这一对左右括号匹配成功后
                     * 还剩下未匹配的左括号，这个未匹配的左括号位置在哪我们不确定，可以是(()()()，也可以是((((()()，每次匹配一对括号，就会删掉
                     * 一个栈中左括号，所以用right-st.top()得到的就是当前情况得到的有效括号长度，而不需要加1，因为加1的情况应用与right和left
                     * 都是有效括号对的区间角标。
                     * */
                    st.pop();
                    res = st.empty()? max(res, right - left + 1) : max(res, right - st.top());
                }
            }
        }

        return res;
    }
};

/*
 * Solution 2: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int longestValidParentheses(string s) {
        int res = 0;
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') st.push(i);
            else {
                st.pop();
                // 如果为空的话表明没有匹配括号，将i加入栈中，表示的是invalid位置，而不是valid，因为valid的index都会被pop掉；
                // 而且，下面采用的是st.top()，所以需要存的是invalid位置
                if (st.empty()) {
                    st.push(i);
                }
                else res = max(res, i - st.top());
            }
        }

        return res;
    }
};

/*
 * Solution 3: two passes
 * time: O(n)
 * space: O(1)
 * */

/*
 * two passes的总思路：括号匹配总共有四种情况：（1）左括号较多不平衡（2）右括号较多不平衡（3）左右括号有效匹配且平衡（4）左右括号一样多但不匹配，如))((
 * 情况（1），如((())，从左到右扫，得不到res更新。但是从右到左扫，就可以得到相匹配的两对括号，所以长度为4
 * 情况（2），如(()))，从左到右扫，可以得到相匹配的两对括号，长度为4；从右到左扫，得不到res更新；
 * 情况（3），如(())，无论是从左到右还是从右到左，都能更新res=4；
 * 情况（4），如))((，由于右括号先出现，所以从左到右时，只要右括号个数大于左括号个数，就置为重新开始算；从右到左扫时，左括号个数大于右括号个数，就重算
 * */
class Solution {
public:
    int longestValidParentheses(string s) {
        // pass 1: 从左到右，分别记录左右括号的个数，如果左右括号个数相等，结果乘2即为res。
        int cntl = 0, cntr = 0, res = 0;
        for (char c : s) {
            if (c == '(') cntl++;
            else cntr++;
            if (cntl == cntr)  res = max(res, 2 * cntl);
            else if (cntr > cntl) cntl = cntr = 0; // 如果右括号先出现，计数器都置0重新开始算
        }

        cntl = cntr = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '(') cntl++;
            else cntr++;
            if (cntl == cntr) res = max(res, 2 * cntl);
            else if (cntl > cntr) cntl = cntr = 0;
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
