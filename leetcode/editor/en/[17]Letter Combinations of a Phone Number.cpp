//Given a string containing digits from 2-9 inclusive, return all possible lette
//r combinations that the number could represent. Return the answer in any order. 
//
//
// A mapping of digit to letters (just like on the telephone buttons) is given b
//elow. Note that 1 does not map to any letters. 
//
// 
//
// 
// Example 1: 
//
// 
//Input: digits = "23"
//Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
// 
//
// Example 2: 
//
// 
//Input: digits = ""
//Output: []
// 
//
// Example 3: 
//
// 
//Input: digits = "2"
//Output: ["a","b","c"]
// 
//
// 
// Constraints: 
//
// 
// 0 <= digits.length <= 4 
// digits[i] is a digit in the range ['2', '9']. 
// 
// Related Topics Hash Table String Backtracking 
// 👍 6997 👎 560


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: backtracing
 * time: O(n*4^n), 4^n for each combination, n times to build this combination.
 * space: O(n), recursion can go deep into n layers
 * */
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.empty() || digits.size() == 0) {
            return res;
        }

        string path = "";
        backtrack(res, digits, path, 0);

        return res;
    }

private:
    unordered_map<char, string> digit2chars = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"},
                                               {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"},
                                               {'8', "tuv"}, {'9', "wxyz"}};
    void backtrack(vector<string> &res, string &digits, string path, int idx) {
        if (path.size() == digits.size()) {
            res.push_back(path);
            return;
        }

        string letters = digit2chars[digits[idx]];
        for (int i = 0; j < letters.size(); i++) {
            path.push_back(letters[i]);
            backtrack(res, digits, path, idx + 1);
            path.pop_back();
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)
