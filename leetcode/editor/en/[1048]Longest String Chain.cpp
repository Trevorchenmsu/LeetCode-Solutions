//You are given an array of words where each word consists of lowercase English 
//letters. 
//
// wordA is a predecessor of wordB if and only if we can insert exactly one lett
//er anywhere in wordA without changing the order of the other characters to make 
//it equal to wordB. 
//
// 
// For example, "abc" is a predecessor of "abac", while "cba" is not a predecess
//or of "bcad". 
// 
//
// A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, w
//here word1 is a predecessor of word2, word2 is a predecessor of word3, and so on
//. A single word is trivially a word chain with k == 1. 
//
// Return the length of the longest possible word chain with words chosen from t
//he given list of words. 
//
// 
// Example 1: 
//
// 
//Input: words = ["a","b","ba","bca","bda","bdca"]
//Output: 4
//Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
// 
//
// Example 2: 
//
// 
//Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
//Output: 5
//Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "p
//cxbc", "pcxbcf"].
// 
//
// Example 3: 
//
// 
//Input: words = ["abcd","dbqca"]
//Output: 1
//Explanation: The trivial word chain ["abcd"] is one of the longest word chains
//.
//["abcd","dbqca"] is not a valid word chain because the ordering of the letters
// is changed.
// 
//
// 
// Constraints: 
//
// 
// 1 <= words.length <= 1000 
// 1 <= words[i].length <= 16 
// words[i] only consists of lowercase English letters. 
// 
// Related Topics Array Hash Table Two Pointers String Dynamic Programming 
// 👍 2514 👎 127


//leetcode submit region begin(Prohibit modification and deletion)

/*
 * solution 0: sort + bottom-up dp, TLE
 * time: O(n^2*L)
 * space: O(n)
 * */
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        int n = words.size(), res = 1;
        sort(words.begin(), words.end(), [](string& a, string &b){
            return a.size() < b.size();
        });
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (words[j].size() + 1 < words[i].size()) break;
                if (words[j].size() == words[i].size()) continue;
                if (helper(words[j], words[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    res = max(res, dp[i]);
                }
            }
        }
        return res;
    }
    bool helper(string word1, string word2) {
        int m = word1.size(), n = word2.size(), i = 0;
        for (int j = 0; j < n; ++j) {
            if (word2[j] == word1[i]) ++i;
        }
        return i == m;
    }
};


/*
 * solution 1: sort + hash table + bottom-up dp
 * time: O(n*(logn+L^2))
 * space: O(n)
 * */
class Solution {
public:
    static bool cmp(const string &s1, const string &s2) {
        return s1.size() < s2.size();
    }

    /*
     * 在上面TLE的解法中，因为多了一层O(N)遍历i前面的所有元素导致TLE。主要优化点就在于不要重复计算这一层，哈希表是如何起到优化效果的？
     * 我们在往后遍历时，目的也只是为了找到基于当前单词长度少一且为当前单词子序列的单词，但是我们没必要去遍历所有。在经历过当前单词之前，
     * 我们已经遍历过它们，所以用哈希表把它们存起来，在遇到当前单词时，删除一个字符，考虑所有子序列，查找它是否在哈希表中，就可以避免多层遍历
     * */
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), cmp); // O(nlogn)
        int res = 1, len = words.size();
        unordered_map<string, int> word2cnt;

        /*
         * 所有单词按长度排序后，遍历每个单词。每个单词在哈希表的起始计数均为1，因为单词本身算是一个序列。
         * 对当前单词的每个字符都进行遍历，并删除这个字符，获得子串，也就是比当前单词长度少1的predecessor。
         * 因为前面单词列表已经按照长度升序排过序了，当前遍历的单词长度减1的结果，如果存在在单词列表中，肯定
         * 是在前面就已经被考虑过，所以哈希表的key肯定能找到这个单词，否则就证明单词列表中没有这个单词。
         * 因此，当哈希表找到这个子串后，就可以进行打擂台更新当前单词的最大长度，同时更新全局变量res。
         * */
        for (auto &word : words) { // O(n*L^2)
            word2cnt[word] = 1;
            for (int j = 0; j < word.size(); j++) {
                string word_new = word.substr(0, j) + word.substr(j + 1);
                auto it = word2cnt.find(word_new);
                if (it != word2cnt.end()) {
                    word2cnt[word] = max(word2cnt[word], word2cnt[word_new] + 1);
                    res = max(res,  word2cnt[word]);
                }
            }
        }

        return res;
    }
};

/*
 * solution 2: dfs + memoization
 * time: O(n*L^2)
 * space: O(n)
 * */

class Solution {
public:
    int longestStrChain(vector<string>& words) {
        unordered_set<string> wordSet(words.begin(), words.end());
        unordered_map<string, int> memo;

        int res = 0;

        for (auto &word : words) {
            res = max(res, dfs(word, wordSet, memo));
        }

        return res;
    }

    int dfs(string s, unordered_set<string> &wordSet, unordered_map<string,int> &memo) {
        if (memo.find(s) != memo.end()) {
            return memo[s];
        }

        int res = 1;
        for (int i = 0; i < s.size(); i++) { // for loop: O(L)
            string word = s.substr(0, i) + s.substr(i + 1);
            if (wordSet.find(word) != wordSet.end()) { // set check: O(L)
                res = max(res, dfs(word, wordSet, memo) + 1);
            }
        }

        memo[s] = res;

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
