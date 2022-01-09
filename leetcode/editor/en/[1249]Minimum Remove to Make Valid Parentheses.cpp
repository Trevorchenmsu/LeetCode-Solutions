//Given a string s of '(' , ')' and lowercase English characters. 
//
// Your task is to remove the minimum number of parentheses ( '(' or ')', in any
// positions ) so that the resulting parentheses string is valid and return any va
//lid string. 
//
// Formally, a parentheses string is valid if and only if: 
//
// 
// It is the empty string, contains only lowercase characters, or 
// It can be written as AB (A concatenated with B), where A and B are valid stri
//ngs, or 
// It can be written as (A), where A is a valid string. 
// 
//
// 
// Example 1: 
//
// 
//Input: s = "lee(t(c)o)de)"
//Output: "lee(t(c)o)de"
//Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
// 
//
// Example 2: 
//
// 
//Input: s = "a)b(c)d"
//Output: "ab(c)d"
// 
//
// Example 3: 
//
// 
//Input: s = "))(("
//Output: ""
//Explanation: An empty string is also valid.
// 
//
// Example 4: 
//
// 
//Input: s = "(a(b(c)d)"
//Output: "a(b(c)d)"
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 10^5 
// s[i] is one of '(' , ')' and lowercase English letters. 
// Related Topics String Stack 
// 👍 2167 👎 50

//Input: s = "(a(b(c)d)"
//Output: "a(b(c)d)"

//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: BFS, TLE
 * time: O(n!)
 * space: O(n!)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        queue<string> q;
        unordered_set<string> visited;
        q.push(s);
        visited.insert(s);

        while(!q.empty()) {
            string cur = q.front(); q.pop();
            if (isValid(cur)) return cur;
            for (int i = 0; i < cur.size(); i++) {
                string new_str = cur.substr(0, i) + cur.substr(i + 1);
                if (visited.find(new_str) != visited.end()) continue;
                q.push(new_str);
                visited.insert(new_str);
            }
        }

        return "";
    }

    bool isValid(string &s) {
        int cnt = 0;
        for (auto &ch : s) {
            if (ch == '(') cnt++;
            else if (ch == ')') cnt--;

            if (cnt < 0) return false;
        }

        return cnt == 0;
    }
};

/*
 * solution 2: stack
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> Stack;
        string res;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                Stack.push(i);
            else if (s[i] == ')') {
                // 右括号先出现，不合理，先保留位置，但置为空。
                if (Stack.empty())
                    s[i] = ' ';
                else
                    Stack.pop(); // match a left parenthesis
            }
        }

        // 当有效的右括号都被匹配完了以后，左括号还有剩余，需要置为空
        while (!Stack.empty()) {
            s[Stack.top()] = ' ';
            Stack.pop();
        }

        for (auto &ch : s)
            if (ch != ' ')
                res.push_back(ch);

        return res;
    }
};

/*
 * solution 3: stack, same as solution 2
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        if (s.empty() || s.size() == 0) return "";

        stack<int> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') st.push(i);
            if (s[i] == ')') {
                if (st.empty() || s[st.top()] != '(') st.push(i);
                else st.pop();
            }
        }

        while (!st.empty()) {
            s[st.top()] = '+';
            st.pop();
        }

        string res = "";
        for (auto &ch : s) {
            if (ch != '+') res.push_back(ch);

        }

        return res;
    }
};

/*
 * solution 4: two passes, optimal
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        // pass 1: 从左往右删除所有无效')'
        string leftToRight = "";
        int balance = 0;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') balance++;
            if (c == ')') {
                if (balance == 0) continue;
                balance--;
            }
            leftToRight.push_back(c);
        }

        // pass 2: 从右往左删除所有无效'('
        string res = "";
        balance = 0;
        for (int i = leftToRight.size() - 1; i >= 0; i--) {
            char c = leftToRight[i];
            if (c == ')') balance++;
            if (c == '(') {
                if (balance == 0) continue;
                balance--;
            }
            res.push_back(c);
        }

        reverse(res.begin(), res.end());

        return res;
    }
};

/*
 * solution 5: two passes, optimal
 * time: O(n)
 * space: O(1)
 * */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        // pass 1: 从右往左删除所有无效'('
        string str = "";
        int balance = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            char c = s[i];
            if (c == ')') balance++;
            if (c == '(') {
                if (balance == 0) continue;
                balance--;
            }
            str.push_back(c);
        }

        reverse(str.begin(), str.end());

        // pass 2: 从左往右删除所有无效')'
        string res = "";
        balance = 0;
        for (int i = 0; i < str.size(); i++) {
            char c = str[i];
            if (c == '(') balance++;
            if (c == ')') {
                if (balance == 0) continue;
                balance--;
            }
            res.push_back(c);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
