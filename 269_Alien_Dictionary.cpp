/*
solution 1: topological sorting + queue
time:O(V+E)=O(n*k + n*k)=O(n*k), n is the array length, k is the average length of thw word
space: O(V+E)=O(n*k + n*k)=O(n*k)
*/
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string res = "";
        if (words.empty()) return res;
        
        // build graph, map(node, edge)
        unordered_map<char, string> graph;
        
        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                graph[words[i][j]] = "";
            }
        }
        
        for (int i = 1; i < words.size(); i++) {
            int mini_size = min(words[i].size(), words[i - 1].size());
            int j;
            for (j = 0; j < mini_size; j++) {
                if (words[i][j] == words[i - 1][j])
                    continue;
                graph[words[i - 1][j]].push_back(words[i][j]);
                break;
            }
            if (j == mini_size && words[i - 1].size() > words[i].size())
                return "";
        }
        
        // build indegree
        unordered_map<char, int> indegree;
        for (auto& g : graph) {
            if (!indegree.count(g.first)) 
                indegree[g.first] = 0;
            for (auto& e : g.second) {
                ++indegree[e];
            }
        }
        
        queue<char> q;
        for (auto& ind : indegree) {
            if (ind.second == 0)
                q.push(ind.first);
        }
        
        while (!q.empty()) {
            char cur = q.front();
            q.pop();
            res.push_back(cur);
            for (auto& e : graph[cur]) {
                if (--indegree[e] != 0)
                    continue;
                q.push(e);
            }
        }
        
        return res.size() == indegree.size() ? res : "";
    }
};

/*
solution 2: topological sorting + heap
time:O(V+E)=O(n*k + n*k)=O(n*k*logk)?, n is the array length, k is the average length of thw word
space: O(V+E)=O(n*k + n*k)=O(n*k)
*/
class Solution {
public:
    string alienOrder(vector<string>& words) {
        string res = "";
        if (words.empty()) return res;
        
        // build graph, map(node, edge)
        unordered_map<char, string> graph;
        
        for (int i = 0; i < words.size(); ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                graph[words[i][j]] = "";
            }
        }
        
        for (int i = 1; i < words.size(); i++) {
            int mini_size = min(words[i].size(), words[i - 1].size());
            int j;
            for (j = 0; j < mini_size; j++) {
                if (words[i][j] == words[i - 1][j])
                    continue;
                graph[words[i - 1][j]].push_back(words[i][j]);
                break;
            }
            if (j == mini_size && words[i - 1].size() > words[i].size())
                return "";
        }
        
        // build indegree
        unordered_map<char, int> indegree;
        for (auto& g : graph) {
            if (!indegree.count(g.first)) 
                indegree[g.first] = 0;
            for (auto& e : g.second) {
                ++indegree[e];
            }
        }
        
        priority_queue<char, vector<char>, greater<char>> minHeap;
        for (auto& ind : indegree) {
            if (ind.second == 0)
                minHeap.push(ind.first);
        }
        
        while (!minHeap.empty()) {
            char cur = minHeap.top();
            minHeap.pop();
            res.push_back(cur);
            for (auto& e : graph[cur]) {
                if (--indegree[e] != 0)
                    continue;
                minHeap.push(e);
            }
        }
        
        return res.size() == indegree.size() ? res : "";
    }
};