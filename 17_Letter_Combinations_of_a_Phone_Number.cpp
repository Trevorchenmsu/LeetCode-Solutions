/*
solution: backtracking
time: O(3^N*4^M), N is the number of digits which has three chars, M is the number of digits wihc has four chars
N+M is the length of the input string
space: O(3^N*4^M)
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty())
            return res;
        string path = "";
        backtrack(digits, res, path, 0);
        return res;
    }
private:
    unordered_map<char, string> digitMap = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, 
                                               {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
                                               {'8', "tuv"}, {'9', "wxyz"}};
    void backtrack(string &digits, vector<string> &res, string &path, int idx) {
        if (path.size() == digits.size()) {
            res.push_back(path);
            return;
        }
        
        string s = digitMap[digits[idx]];
        for (int i = 0; i < s.size(); i++) {
            path.push_back(s[i]);
            backtrack(digits, res, path, idx + 1);
            path.pop_back();
        }
    }
};

