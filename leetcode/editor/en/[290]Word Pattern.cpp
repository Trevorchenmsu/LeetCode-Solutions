//Given a pattern and a string s, find if s follows the same pattern. 
//
// Here follow means a full match, such that there is a bijection between a lett
//er in pattern and a non-empty word in s. 
//
// 
// Example 1: 
//
// 
//Input: pattern = "abba", s = "dog cat cat dog"
//Output: true
// 
//
// Example 2: 
//
// 
//Input: pattern = "abba", s = "dog cat cat fish"
//Output: false
// 
//
// Example 3: 
//
// 
//Input: pattern = "aaaa", s = "dog cat cat dog"
//Output: false
// 
//
// Example 4: 
//
// 
//Input: pattern = "abba", s = "dog dog dog dog"
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= pattern.length <= 300 
// pattern contains only lower-case English letters. 
// 1 <= s.length <= 3000 
// s contains only lower-case English letters and spaces ' '. 
// s does not contain any leading or trailing spaces. 
// All the words in s are separated by a single space. 
// 
// Related Topics Hash Table String 
// 👍 2271 👎 256


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: hash table
 * time: O(n^2), n is the length of pattern
 * space: O(n)
 * */
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = split(s, ' ');
        if (pattern.size() != words.size()) {
            return false;
        }
        unordered_map<char, string> charTostring;
        for (int i = 0; i < pattern.size(); i++) {
            auto it = charTostring.find(pattern[i]);
            if (it == charTostring.end()) {
                for (auto &cs : charTostring) {
                    if (cs.second == words[i]) {
                        return false;
                    }
                }
                charTostring[pattern[i]] = words[i];
            }
            else {
                if (charTostring[pattern[i]] != words[i]) {
                    return false;
                }
            }
        }

        return true;
    }

    vector<string> split(string &s, char delimit) {
        stringstream ss(s);
        string token = "";
        vector<string> res;
        while (getline(ss, token, delimit)) {
            res.push_back(token);
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
