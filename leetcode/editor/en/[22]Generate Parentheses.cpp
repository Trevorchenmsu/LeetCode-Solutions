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
 * time: O(2n*2^2n)，除非用卡特兰数公式计算出确实的复杂度，一般面试情况下很难给出准确的回溯时间复杂度，用这个近似的即可，近似于求全部子集的情况，忽略无效及重复的情况。
 * space: O(2n*2^2n)
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

/*
 * solution 2: backtrack，这个解法path没有采用引用作为参数输入，所以占据更多空间，时间差不多。好处是可以把path的变化直接在语句中变化
 * time: O(4^n/sqrt(n))
 * space: O(4^n/sqrt(n))
 *
 * */

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path = "";
        buildParenthesis(res, path, n, 0, 0);
        return res;
    }

    void buildParenthesis(vector<string> &res, string path, int n, int cnt_left, int cnt_right) {
        if (path.size() == n * 2) {
            res.push_back(path);
            return;
        }

        if (cnt_right > cnt_left) return;

        if (cnt_left < n)
            buildParenthesis(res, path + "(", n, cnt_left + 1, cnt_right);

        if (cnt_right < n)
            buildParenthesis(res, path + ")", n, cnt_left, cnt_right + 1);
    }
};

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []
        path = ""
        self.buildParenthesis(res, path, n, 0, 0)
    return res

    def buildParenthesis(self, res, path, n, left, right):
        if len(path) == 2 * n:
            res.append(path)
            return

        if right > left: return

        if left < n: self.buildParenthesis(res, path + '(', n, left + 1, right)
        if right < n: self.buildParenthesis(res, path + ')', n, left, right + 1)



class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path = "(";
        int left_cnt = 1, right_cnt = 0;
        createParenthesis(res, path, n, left_cnt, right_cnt);
        return res;
    }

    void createParenthesis (vector<string> &res, string path, int n, int left, int right) {
        if (path.size() == n * 2)
        {
            res.push_back(path);
            return;
        }

        if (left < n) createParenthesis(res, path + '(', n, left + 1, right);
        if (right < n && right < left) createParenthesis(res, path + ')', n , left, right + 1);
    }
};


/*
 * solution 3: backtrack， 这个解法path采用引用作为参数输入，所以占据更少空间，时间差不多。稍微繁琐一点就是得采用标准回溯模式，即先加后删除
 * time: O(2n*2^2n)
 * space: O(2n*2^2n)
 *
 * */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path = "";
        buildParenthesis(res, path, n, 0, 0);
        return res;
    }

    void buildParenthesis(vector<string> &res, string &path, int n, int cnt_left, int cnt_right) {
        if (path.size() == n * 2) {
            res.push_back(path);
            return;
        }

        if (cnt_right > cnt_left) return;

        if (cnt_left < n) {
            path.push_back('(');
            buildParenthesis(res, path, n, cnt_left + 1, cnt_right);
            path.pop_back();
        }

        if (cnt_right < n) {
            path.push_back(')');
            buildParenthesis(res, path, n, cnt_left, cnt_right + 1);
            path.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
