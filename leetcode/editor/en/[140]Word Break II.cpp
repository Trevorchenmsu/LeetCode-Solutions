//Given a string s and a dictionary of strings wordDict, add spaces in s to cons
//truct a sentence where each word is a valid dictionary word. Return all such pos
//sible sentences in any order. 
//
// Note that the same word in the dictionary may be reused multiple times in the
// segmentation. 
//
// 
// Example 1: 
//
// 
//Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
//Output: ["cats and dog","cat sand dog"]
// 
//
// Example 2: 
//
// 
//Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","p
//ineapple"]
//Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
//Explanation: Note that you are allowed to reuse a dictionary word.
// 
//
// Example 3: 
//
// 
//Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
//Output: []
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 20 
// 1 <= wordDict.length <= 1000 
// 1 <= wordDict[i].length <= 10 
// s and wordDict[i] consist of only lowercase English letters. 
// All the strings of wordDict are unique. 
// 
// Related Topics Hash Table String Dynamic Programming Backtracking Trie Memoiz
//ation 
// 👍 3849 👎 454


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: dfs + memo
 * time: O(n^3)?
 * space: O(n^3)
 *
 * */
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return dfsMemo(s, 0, wordSet, memo);
    }
    /*
    memo记录的是从当前index得到对应的后续的字符串数组。下面dfs中的for循环是这样搜索的：
    如catsanddog, index从0开始，i从index开始，所以word会逐个字符扩大。c,ca不符合，走到了cat才符合。
    此时这个word=cat，需要保留起来等下计算答案。因此剩下的部分进行递归去考虑剩余的子串，从index+1开始。
    */
    vector<string> dfsMemo(string &s, int index, unordered_set<string> &wordSet,
                           unordered_map<int, vector<string>> &memo) {
        // visited index
        if (memo.find(index) != memo.end()) {
            return memo[index];
        }

        // dfs
        vector<string> res;
        for (int i = index; i < s.size(); i++) {
            string word = s.substr(index, i - index + 1);
            auto it = wordSet.find(word);
            if (it == wordSet.end()) {
                continue;
            }

            vector<string> words = dfsMemo(s, i + 1, wordSet, memo);
            // 此时word在字典中，但是i走到了s尽头，表明它是最后一个单词，不需要加空格
            if (i == s.size() - 1) {
                res.push_back(word);
            }
            else {
                for (auto &w : words) {
                    res.push_back(word + " " + w);
                }
            }
        }

        memo[index] = res;
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
