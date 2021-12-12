//Given a string s that contains parentheses and letters, remove the minimum num
//ber of invalid parentheses to make the input string valid. 
//
// Return all the possible results. You may return the answer in any order. 
//
// 
// Example 1: 
//
// 
//Input: s = "()())()"
//Output: ["(())()","()()()"]
// 
//
// Example 2: 
//
// 
//Input: s = "(a)())()"
//Output: ["(a())()","(a)()()"]
// 
//
// Example 3: 
//
// 
//Input: s = ")("
//Output: [""]
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 25 
// s consists of lowercase English letters and parentheses '(' and ')'. 
// There will be at most 20 parentheses in s. 
// 
// Related Topics Depth-first Search Breadth-first Search 
// 👍 3432 👎 160


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: BFS + pruning
 * time: O(2^n)
 * space: O(2^n)
 * */
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        if (s.empty()) return res;

        queue<string> q;
        q.push(s);
        unordered_set<string> visited;
        visited.insert(s);
        bool flag = false;

        while (!q.empty()) {
            string cur = q.front(); q.pop();

            if (isValid(cur)) { // O(n)
                res.push_back(cur);
                flag = true;
            }

            if (flag) continue;

            for (int i = 0; i < cur.size(); i++) { // O(L^2)
                if (isalpha(cur[i])) continue;
                string neighbor = cur.substr(0, i) + cur.substr(i + 1);

                if (visited.count(neighbor))  continue;

                q.push(neighbor);
                visited.insert(neighbor);
            }
        }

        return res;
    }


private:
    bool isValid(string &s) {
        int cnt = 0;
        for (auto &ch : s) {
            if (ch == '(')
                cnt++;

            if (ch == ')')
                cnt--;

            if (cnt < 0)
                return false;
        }

        return cnt == 0;
    }
};


/*
 * solution 2: DFS
 * time: O(2^n)
 * space: O(n)
 * */
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        if (s.empty()) return res;

        //先求出不平衡的左右括号各有多少个，后面dfs逐渐一个个消除看
        int numOfOpen = 0, numOfClose = 0;
        for (auto &ch : s) { //O(n)
            numOfOpen += (ch == '(');
            if (numOfOpen == 0)
                numOfClose += (ch == ')');
            else
                numOfOpen -= (ch == ')');
        }

        dfs(s, res, 0, numOfOpen, numOfClose);
        return res;
    }

    void dfs(string s, vector<string> &res, int start, int numOfOpen, int numOfClose) {
        if (numOfOpen == 0 && numOfClose == 0) {
            if (isValid(s)) { // O(n)
                res.push_back(s);
            }
            return;
        }

        for (int i = start; i < s.size(); i++) { // O(n)
            // 去重，对于连续括号的情况如)))，当处理完第一个后，后面两个不需要再处理，因为结果一样
            if (i != start && s[i] == s[i - 1]) continue;
            string substr = s.substr(0, i) + s.substr(i + 1);
            // 用dfs往两个方向递减括号
            if (numOfOpen > 0 && s[i] == '(')
                dfs(substr, res, i, numOfOpen - 1, numOfClose);
            if (numOfClose > 0 && s[i] == ')')
                dfs(substr, res, i, numOfOpen, numOfClose - 1);
        }
    }

    bool isValid(string &s) {
        int cnt = 0;
        for (auto &ch : s) {
            if (ch == '(')
                cnt++;
            if (ch == ')')
                cnt--;
            if (cnt < 0)
                return false;
        }

        return cnt == 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
