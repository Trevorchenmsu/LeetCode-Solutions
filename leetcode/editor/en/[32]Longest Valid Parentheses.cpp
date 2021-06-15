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
                    st.pop();
                    res = st.empty()? max(res, right - left + 1) : max(res, right - st.top());
                }
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
