/*
solution 1: backtrack
time:
space:
*/

class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        backtrack(S, 0);
        res.push_back(S);
        return res;
    }

private:
    vector<string> res;
    void backtrack(string s, int idx) {
        if (idx == s.size()) return;
        
        if (islower(s[idx])) {
            s[idx] = toupper(s[idx]);
            res.push_back(s);
            backtrack(s, idx + 1);
            s[idx] = tolower(s[idx]);
            backtrack(s, idx + 1);
        } else if (isupper(s[idx])) {
            s[idx] = tolower(s[idx]);
            res.push_back(s);
            backtrack(s, idx + 1);
            s[idx] = toupper(s[idx]);
            backtrack(s, idx + 1);
        } else backtrack(s, idx + 1);
    }
};