/*
solution 1: backtrack
time: O(n*2^n)
space: O(n) + O(n*2^n) stack + solutions
*/

class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> res;
        string path = "";
        backtrack(S, res, path, 0);
        return res;
    }
    
    void backtrack(string& s, vector<string> &res, string path, int idx) {
        if (idx == s.size()) {
            res.push_back(path);
            return;
        }
        
        if (isdigit(s[idx])) {
            backtrack(s, res, path + (char) s[idx], idx + 1);
        } else {
            backtrack(s, res, path + (char) tolower(s[idx]), idx + 1);
            backtrack(s, res, path + (char) toupper(s[idx]), idx + 1);
        }
            
    }
};

/*
solution 2: backtrack + bit manipulation
time: O(n*2^n)
space: O(n) + O(n*2^n) stack + solutions
*/
class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> res;
        backtrack(res, S, 0);
        return res;
    }
private:
    void backtrack(vector<string> &res, string s, int idx) {
        if (idx == s.size()) {
            res.push_back(s);
            return;
        }
        backtrack(res, s, idx + 1);
        if (s[idx] > '9') {
            s[idx] ^= (1 << 5);
            backtrack(res, s, idx + 1);
        }
    }
};


/*
solution 3: backtrack
time: O(n*2^n)
space: O(n) + O(n*2^n) stack + solutions
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