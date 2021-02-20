/*
solution 1: backtrack
time: O(n*2^n)
space: O(n), recursion stack
*/

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if (s.empty()) return res;
        vector<string> path;
        backtrack(res, path, s, 0);
        return res;
    }
    
    void backtrack(vector<vector<string>> &res, vector<string> &path, string &s, int start) {
        if (start == s.size()) {
            res.push_back(path);
            return;
        }
        
        for (int i = start; i < s.size(); i++) {
            string sub = s.substr(start, i - start + 1);
            if (!isPalin(sub)) continue; 
            path.push_back(sub);
            backtrack(res, path, s, i + 1);
            path.pop_back();
        }
    }
    
    bool isPalin(string &s) {
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - 1 - i])
                return false;
        }
        return true;
    }
};