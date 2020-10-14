/*
solution: DP
time: O(n*m*m), n is the size of words array, m is the maximum length of the words.
space: O(m)

*/

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> res;
        if (words.empty() || words.size() == 0) {
            return res;
        }
        
        unordered_set<string> wordSet(words.begin(), words.end());
        
        for (string word : words) {
            int n = word.size();
            vector<bool> dp(n + 1);
            dp[0] = true;
            for (int i = 0; i < n; ++i) {
                if (dp[i] == 0) {
                    continue;
                }
                
                for (int j = i + 1; j <= n; ++j) {
                    if (j - i < n && wordSet.count(word.substr(i, j - i))) {
                        dp[j] = true;
                    }
                }
                if (dp[n]) {
                    res.push_back(word);
                    break;
                }
            }
        }
        return res;
    }
};