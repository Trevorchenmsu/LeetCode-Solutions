/*
solution: topological sorting
time:O(V+E)=O(n*k + n*k)=O(n*k), n is the array length, k is the average length of thw word
space: O(V+E)=O(n*k + n*k)=O(n*k)
*/
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string res = "";
        if (words.empty() || words.size() == 0) 
            return res;
        
        // build the graph. key-value = node-edge
        unordered_map<char, string> graph;
        
        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                graph[words[i][j]] = "";
            }
        }
        
        for (int i = 0; i < words.size() - 1; ++i) {
            int j = 0;
            int minLen = min(words[i].size(), words[i + 1].size());
            for (; j < minLen; ++j) {
                if (words[i][j] != words[i + 1][j]) {
                    graph[words[i][j]].push_back(words[i + 1][j]);
                    break;
                }
            }
            if(j == minLen && words[i].size() > words[i + 1].size())
                return "";
        }
        
        // get the indegree
        unordered_map<char, int> indegree;
        for (auto& g : graph) {
            if (!indegree.count(g.first)) indegree[g.first] = 0;
            for (auto& e : g.second) {
                ++indegree[e];
            }
        }
        
        // topological sort
        queue<char> q;
        for (auto& ind : indegree) {
            if (ind.second == 0) q.push(ind.first);
        }
        
        while (!q.empty()) {
            char node = q.front(); q.pop();
            res.push_back(node);
            for (auto& e : graph[node]) {
              if (--indegree[e] != 0) 
                continue;
                q.push(e);
            }
        }
        
        return res.size() == indegree.size() ? res : "";
    }
};

