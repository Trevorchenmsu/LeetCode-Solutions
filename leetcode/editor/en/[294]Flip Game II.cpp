//You are playing a Flip Game with your friend. 
//
// You are given a string currentState that contains only '+' and '-'. You and y
//our friend take turns to flip two consecutive "++" into "--". The game ends when
// a person can no longer make a move, and therefore the other person will be the 
//winner. 
//
// Return true if the starting player can guarantee a win, and false otherwise. 
//
//
// 
// Example 1: 
//
// 
//Input: currentState = "++++"
//Output: true
//Explanation: The starting player can guarantee a win by flipping the middle "+
//+" to become "+--+".
// 
//
// Example 2: 
//
// 
//Input: currentState = "+"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= currentState.length <= 60 
// currentState[i] is either '+' or '-'. 
// 
//
// 
//Follow up: Derive your algorithm's runtime complexity. Related Topics Math Dyn
//amic Programming Backtracking Memoization Game Theory 
// 👍 491 👎 45


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 暴力dfs
 * time: O(2^n), n为单词长度
 * space: O(2^n)
 * */
class Solution {
public:
    bool canWin(string s) {
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == '+' && s[i - 1] == '+') {
                string word_flip = s;
                word_flip[i] = word_flip[i - 1] = '-';

                if (!canWin(word_flip)) {
                    return true;
                }
            }
        }

        return false;
    }
};

/*
 * solution 2: dfs + memo, backtrack
 * time: O(n^2), n为单词长度
 * space: O(n^2)
 * */

class Solution {
public:
    bool canWin(string s) {
        unordered_map<string, bool> memo;
        return dfsMemo(memo, s);
    }

    bool dfsMemo(unordered_map<string, bool> &memo, string s) {
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }

        bool res = false;
        for (int i = 0; i < s.size() - 1; i++)  {
            if (s[i] == s[i + 1] && s[i] == '+') {
                s[i] = s[i + 1] = '-';
                res = dfsMemo(memo, s);
                s[i] = s[i + 1] = '+';
                /* 为什么这里回溯后要判定res=false才能实现先手必胜？
                    能够进来这个if条件，肯定是存在先手可以操作的，否则会直接遍历完for循环然后返回false
                    既然先手可以操作，在当前情况下先手操作了一次，然后就进行回溯了，别管回溯递归到什么内容，
                    只要最终返回这个的res是false，那肯定是第二手的操作无法完成。所以才需要在下面进行非res的
                    判定。
                 */
                if (!res) {
                    memo[s] = true;
                    return true;
                }
            }
        }

        memo[s] = false;
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
