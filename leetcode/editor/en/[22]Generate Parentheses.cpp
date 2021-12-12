//Given n pairs of parentheses, write a function to generate all combinations of
// well-formed parentheses. 
//
// 
// Example 1: 
// Input: n = 3
//Output: ["((()))","(()())","(())()","()(())","()()()"]
// Example 2: 
// Input: n = 1
//Output: ["()"]
// 
// 
// Constraints: 
//
// 
// 1 <= n <= 8 
// 
// Related Topics String Dynamic Programming Backtracking 
// 👍 9896 👎 395


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: backtrack
 * time: O(4^n/sqrt(n))
 * space: O(4^n/sqrt(n))
 *
 * */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backtrack(n, n, "", res);
        return res;
    }

    void backtrack(int left, int right, string path, vector<string> &res) {
        // 左括号剩余数量多，表示右括号加多了，两者不匹配，返回
        if (left > right) {
            return;
        }

        // 左右括号个数都减少到0，表示path中都包括了他们且匹配，加入结果
        if (left == 0 && right == 0) {
            res.push_back(path);
        }
        else {
            // 左括号还有剩余，优先添加左括号
            if (left > 0) {
                backtrack(left - 1, right, path + "(", res);
            }

            // 添加完左括号后再添加右括号
            if (right > 0) {
                backtrack(left, right - 1, path + ")", res);
            }
        }

    }
};
//leetcode submit region end(Prohibit modification and deletion)
