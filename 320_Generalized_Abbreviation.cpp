/*
solution 1: backtrack
time: (n*2^n)
space: O(n)
*/
class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> res;
        string path = "";
        backtrack(res, word, path, 0);
        return res;
    }
    
    void backtrack(vector<string> &res, string &word, string path, int pos) {
        if (pos == word.size()) {
            res.push_back(path);
            return;
        }
        
        if (path != "" && isdigit(path[path.size() - 1])) {
            int cnt = path[path.size() - 1] - '0' + 1;
            backtrack(res, word, path.substr(0, path.size() - 1) + to_string(cnt), pos + 1);
        } else {
            backtrack(res, word, path + '1', pos + 1);
        }
        
        backtrack(res, word, path + word[pos], pos + 1);
    }
};
