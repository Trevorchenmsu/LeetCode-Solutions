//Given a balanced parentheses string s, compute the score of the string based o
//n the following rule: 
//
// 
// () has score 1 
// AB has score A + B, where A and B are balanced parentheses strings. 
// (A) has score 2 * A, where A is a balanced parentheses string. 
// 
//
// 
//
// Example 1: 
//
// 
//Input: s = "()"
//Output: 1
// 
//
// Example 2: 
//
// 
//Input: s = "(())"
//Output: 2
// 
//
// Example 3: 
//
// 
//Input: s = "()()"
//Output: 2
// 
//
// Example 4: 
//
// 
//Input: s = "(()(()))"
//Output: 6
// 
//
// 
//
// Note: 
//
// 
// s is a balanced parentheses string, containing only ( and ). 
// 2 <= s.length <= 50 
// 
// Related Topics String Stack 
// 👍 2251 👎 70


//leetcode submit region begin(Prohibit modification and deletion)

/* 卡点：
 * （1）如何实现两个并列括号分数的相加；
 * （2）如何实现嵌套括号分数的相乘；
 * （3）如何存储得到的临时分数.
 * 按照我原来的思路，是先把左括号的index先存到栈中，然后得到分数后再放到栈中，用于后面嵌套或并列的计算
 * 但是这样在后续的判定中使情况变得复杂多了，因此一直卡在这里。而答案中栈直接存的就是每一层的分数。我的另一个卡点就是不知道
 * 如何跟踪这个并列得到后的分数，以及在低层嵌套得到的分数如果留起来应用到高层。
 * ex：((()()))，（1）每次遇到左括号就把当前的分数入栈后置为0，置为0的目的：因为遇到了一个左括号时，表示我们要进入它的内层去计算
 * 它的括号情况，所以要从0开始。而先把分数入栈就是把前面得到的分数先存起来。所以这两步操作就很好体现了递归的思想：把之前的结果存到栈中，
 * 重新开始计算新的情况。（2）当遇到右括号时，要开始计算分数。因为前面入栈的是之前累积的分数，所以肯定要用栈顶分数来累加。用max来实现
 * 选择并列或者嵌套的情况也是比较tricky的，因为我们在计算嵌套时，肯定是遇到右括号结束时，所以此时的分数是之前更新的分数，用max就可以得到
 * 这个较大值。而当我们想计算并列情况时，因为前面已经先添加了左括号，所以分数已经被置为0了，用max就直接得到1。
 * */

/*
 * solution 1: stack
 * time: O(n)
 * space: O(n)
 * */

class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        stack<int> st;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(score);
                score = 0;
            }
            else {
                score = st.top() + max(1, 2 * score);
                st.pop();
            }
        }

        return score;
    }
};

/*
 * solution 2: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);// 当前分数
        for (auto &ch : s) {
            if (ch == '(') st.push(0);
            else {
                int v = st.top(); st.pop(); // 括号里的值
                int w = st.top(); st.pop(); // 并列括号的值
                st.push(w + max(2 * v, 1));
            }
        }

        return st.top();
    }
};

//leetcode submit region end(Prohibit modification and deletion)
