/*
solution 1: dfs+memo
time: O(n*2^n)
space: O(n*2^n)
*/
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return dfs(s, wordSet, 0);    
    }
    
private:
    unordered_map<int, vector<string>> Map;
    vector<string> dfs(string &s, unordered_set<string> & wordSet, int start) {
        // memo
        if (Map.find(start) != Map.end())
            return Map[start];
        
        vector<string> res;
        if (start == s.size()) 
            res.push_back("");
        
        for (int end = start + 1; end <= s.size(); end++) {
            if (wordSet.find(s.substr(start, end - start)) == wordSet.end()) 
                continue;
            vector<string> path = dfs(s, wordSet, end);
            for (auto p : path) {
                res.push_back(s.substr(start, end - start) + (p == ""? "": " ") + p);
            }
        }
        
        Map[start] = res;
        return res;
    }
};


/*
solution 1: dfs+memo, easier to understand
time: O(n*2^n)
space: O(n*2^n)
*/
class Solution {
public:
    vector<string> wordBreak(string &s, vector<string>& wordDict) {
        unordered_map<int, vector<string>> memo;
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return dfs(s, 0, wordSet, memo);
    }
    
private:
    // dfs + memoization
    vector<string> dfs(string &s, int index, 
                       unordered_set<string> &wordDict,
                       unordered_map<int, vector<string>> &memo) {
        // boundary condition
        if (index == s.size()) {
            memo[index] = {};
            return memo[index];
        }
        // if already computed
        if (memo.find(index) != memo.end()) {
            return memo[index];
        }
        
        // dfs
        vector<string> res;
        for (int i = index; i < s.size(); i++) {
            string s1 = s.substr(index, i - index + 1);
            if (wordDict.find(s1) == wordDict.end())
                continue;
            vector<string> right = dfs(s, i + 1, wordDict, memo);
            if (i == s.size() - 1) {
                res.push_back(s1);
            } else {
                for (string &s2 : right) {
                    res.push_back(s1 + " " + s2);
                }
            }
        }
        memo[index] = res;
        return res;
    }
};