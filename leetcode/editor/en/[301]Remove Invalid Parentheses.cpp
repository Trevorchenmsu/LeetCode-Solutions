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
 * time: (2^n)
 * space: (2^n)
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

            for (int i = 0; i < cur.size(); i++) { // O(N)
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


//leetcode submit region end(Prohibit modification and deletion)
