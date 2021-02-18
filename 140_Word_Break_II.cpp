/*
solution 1: dfs+memo
time:
space:
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
