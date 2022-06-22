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
 * solution 0: hash table, failed, cannot pass case: "jquery", "jquery"
 * time: O(n)
 * space: O(n)
 * */
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = split(s, ' ');
        unordered_map<char, vector<int>> pat_map;
        unordered_map<string, vector<int>> word_map;
        unordered_set<char> visited;

        int n = words.size();
        for (int i = 0; i < n; ++i)
        {
            pat_map[pattern[i]].push_back(i);
            word_map[words[i]].push_back(i);
        }

        for (int i = 0; i < n; ++i)
        {
            if (visited.count(pattern[i])) continue;
            visited.insert(pattern[i]);
            if (pat_map[pattern[i]] == word_map[words[i]])
                continue;
            else return false;
        }

        return true;
    }

    vector<string> split(string &s, char delimit)
    {
        stringstream ss(s);
        string token;
        vector<string> res;

        while (getline(ss, token, delimit))
        {
            res.push_back(token);
        }

        return res;
    }
};


/*
 * solution: hash table
 * time: O(n^2), n is the length of pattern
 * space: O(n)
 * */
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = split(s, ' ');
        if (words.size() != pattern.size())
            return false;
        unordered_map<char, string> pat_word;

        int n = words.size();
        for (int i = 0; i <n; ++i)
        {
            auto it = pat_word.find(pattern[i]);
            if (it == pat_word.end())
            {
                for (auto &pw : pat_word)
                {
                    if (pw.second == words[i])
                    {
                        return false;
                    }
                }
                pat_word[pattern[i]] = words[i];
            }
            else if (pat_word[pattern[i]] != words[i])
            {
                return false;
            }
        }

        return true;
    }

    vector<string> split(string &s, char delimit)
    {
        vector<string> res;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delimit))
            res.push_back(token);
        return res;
    }
};


class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        words = s.split(' ')
        if len(words) != len(pattern): return False
        pat_word = {}

        for i in range(len(words)):
            if pattern[i] not in pat_word.keys():
                if words[i] in pat_word.values():
                    return False
                pat_word[pattern[i]] = words[i]
            elif pat_word[pattern[i]] != words[i]:
                return False
        return True
//leetcode submit region end(Prohibit modification and deletion)
