/*
solution 1: bfs
time: O(n*n), n is the length of the string
space: O(n*n)
*/
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        if (s.size() == 0) {
            res.push_back("");
            return res;
        }
        
        queue<string> queue;
        set<string> set;
        queue.push(s);
        set.insert(s);
        bool flag = false;
        
        // bfs
        while (!queue.empty()) {
            string cur = queue.front();
            queue.pop();
            if (validString(cur)) {
                res.push_back(cur);
                flag = true;
            }
            if (flag) {
                continue;
            }
            
            for (int i = 0; i < cur.size(); ++i) {
                if (cur[i] != '(' && cur[i] != ')') {
                    continue;
                }
                string str1 = cur.substr(0, i);
                string str2 = cur.substr(i + 1);
                string str3 = str1 + str2;
                int size = set.size();
                set.insert(str3);
                if (size != set.size()) {
                    queue.push(str3);
                }
            }
        }
        return res;
    }
    
private:
    bool validString(string &s){
        if (s.size() == 0) {
            return true;
        }
        int count = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++count;
            }
            if (s[i] == ')') {
                --count;
            }
            if (count < 0) {
                return false;
            }
        }
        return count == 0;
    }
};

/*
solution 2: slow dfs
time: ?
space: ?
*/

class Solution {
public:
    vector<string> removeInvalidParentheses(string &s) {
        vector<string> res;
        int numOpen = 0, numClose = 0;
        
        for (char ch : s) {
            if (ch == '(') {
                ++numOpen;
            }
            if (ch == ')') {
                numOpen > 0 ? --numOpen : ++numClose;
            }
        }
        
        dfs(res, s, numOpen, numClose, 0);
        return res;
    }
private:
    void dfs(vector<string>& res, string& s, int numOpen, int numClose, int index) {
        if (numOpen == 0 && numClose == 0) {
            if (isValid(s)) {
                res.push_back(s);
            }
            return;
        }
        for (int i = index; i < s.size(); ++i) {
            if (i > index && s[i-1] == s[i]) {
                continue;
            } 
            string new_str = s.substr(0, i) + s.substr(i + 1);
            if (s[i] == '(' && numOpen > 0) {
                dfs(res, new_str, numOpen - 1, numClose, i);
            }
            if (s[i] == ')' && numClose > 0) {
                dfs(res, new_str, numOpen, numClose - 1, i);
            }
        }
    }
    
    bool isValid(string s) {
        int count = 0;
        for (char ch : s) {
            if (ch == '(') {
                ++count;
            }
            if (ch == ')' && --count < 0) {
                return false; 
            }
        } 
        return count == 0;
    }
};


/*
solution 3: fast dfs
time: ?
space: ?
*/
class Solution {
public:
    void dfs(vector<string>& res, string s, int si, int sj, char open, char close) {
        int numOpen = 0, numClose = 0;
        for (int i = si; i < s.size(); ++i) {
            if (s[i] == open)
                ++numOpen;
            if (s[i] == close)
                ++numClose;
            
            // imbalance
            if (numClose > numOpen) {
                for (int j = sj; j <= i; ++j) {
                    if (s[j] == close && (j == sj || s[j - 1] != close))
                        dfs(res, s.substr(0, j) + s.substr(j + 1), i, j, open, close);
                }
                return;
            }
        }
        reverse(s.begin(), s.end());
        if (open == '(')
            dfs(res, s, 0, 0, ')', '(');
        else
            res.push_back(s);
    }
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        dfs(res, s, 0, 0, '(', ')');
        return res;
    }
};