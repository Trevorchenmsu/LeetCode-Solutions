//Given a string s and a dictionary of strings wordDict, return true if s can be
// segmented into a space-separated sequence of one or more dictionary words. 
//
// Note that the same word in the dictionary may be reused multiple times in the
// segmentation. 
//
// 
// Example 1: 
//
// 
//Input: s = "leetcode", wordDict = ["leet","code"]
//Output: true
//Explanation: Return true because "leetcode" can be segmented as "leet code".
// 
//
// Example 2: 
//
// 
//Input: s = "applepenapple", wordDict = ["apple","pen"]
//Output: true
//Explanation: Return true because "applepenapple" can be segmented as "apple pe
//n apple".
//Note that you are allowed to reuse a dictionary word.
// 
//
// Example 3: 
//
// 
//Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
//Output: false
// 
//
// 
// Constraints: 
//
// 
// 1 <= s.length <= 300 
// 1 <= wordDict.length <= 1000 
// 1 <= wordDict[i].length <= 20 
// s and wordDict[i] consist of only lowercase English letters. 
// All the strings of wordDict are unique. 
// 
// Related Topics Hash Table String Dynamic Programming Trie Memoization 
// 👍 8179 👎 379


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: 1D dp
 * time: O(n^2*L)
 * space: O(n)
 * */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty() || wordDict.size() == 0) {
            return false;
        }

        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int len = s.size();
        vector<bool> dp(len + 1, false);
        dp[0] = true;
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j < i; j++) {
                dp[i] = dp[j] && check(s.substr(j, i - j), wordSet);
                if (dp[i] == true) {
                    break;
                }
            }
        }

        return dp[len];
    }

    bool check(string s, unordered_set<string> &wordSet) {
        auto it = wordSet.find(s);
        if (it == wordSet.end()) {
            return false;
        }
        return true;
    }
};

/*
 * solution 2: 1D dp, optimal
 * time: O(n*L^2)
 * space: O(n)
 * */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty() || wordDict.size() == 0) {
            return false;
        }

        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int len = s.size();

        int maxLen = 0;
        for (auto &word : wordDict) {
            int length = word.length();
            maxLen = max(maxLen, length);
        }

        vector<bool> dp(len + 1, false);
        dp[0] = true;

        for (int i = 1; i <= len; i++) {
            for (int l = 1; l <= maxLen; l++) {
                if (i < l) {
                    break;
                }

                if (!dp[i - l]) {
                    continue;
                }

                auto it = wordSet.find(s.substr(i - l, l));
                if (it != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[len];
    }
};



/*
 * solution 3: dfs + memo
 * time: O(n^2*L)
 * space: O(n)
 * */

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<int> memo(s.length(), -1);
        return wordBreakMemo(s, wordSet, memo, 0);
    }

    /*
    为什么可以用记忆化搜索？例如leetcode，当我们从l开始，然后递归搜索eetcode的情况，在eetcode的第二层递归会搜索etcode。
     当l搜索结束后，我们从l下一个字符e开始新的所有，则又要搜索etcode，这个搜索前面已经执行过了，所以要在这里把已经搜索过的记录下来，避免重复搜索。
    */

    bool wordBreakMemo(string &s, unordered_set<string> &wordSet, vector<int> &memo, int start) {
        if (start == s.length()) {
            return true;
        }

        if (memo[start] != -1) {
            return memo[start];
        }

        // 注意点：end的左右边界，这里可以等于s.length()，目的是进入最后一层递归时在递归出口返回true
        for (int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            // 这个判定表示：如果由start~end（不包括end）的子串在wordSet里面，同时从end出发的剩余字符串也有效
            if (wordSet.find(word) != wordSet.end() && wordBreakMemo(s, wordSet, memo, end)) {
                memo[start] = true;
                return memo[start];
            }
        }

        memo[start] = false;
        return memo[start];
    }
};


/*
 * solution 3: bfs
 * time: O(n^2*L)
 * space: O(n)
 * */

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        queue<int> q;
        vector<bool> visited(s.length(), false);
        q.push(0);
        while (!q.empty()) {
            int start = q.front();
            q.pop();
            if (visited[start]) {
                continue;
            }
            for (int end = start + 1; end <= s.length(); end++) {
                if (wordSet.find(s.substr(start, end - start)) !=  wordSet.end()) {
                    q.push(end);
                    if (end == s.length()) {
                        return true;
                    }
                }
            }
            visited[start] = true;
        }
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
