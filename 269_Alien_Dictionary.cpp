/*
solution: topological sorting
time:O(V+E)=O(n*k + n*k)=O(n*k), n is the array length, k is the average length of thw word
space: O(V+E)=O(n*k + n*k)=O(n*k)
*/

class Solution {
private:
    unordered_map<char, string> buildGraph(vector<string> &words){
        // initialization
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
            
            if(j == minLen && words[i].size() > words[i + 1].size()) {
                return {};
            }
        }
        
        return graph;
    }
    
    unordered_map<char, int> getIndegree(unordered_map<char, string> &graph){
        unordered_map<char, int> inDegree;
        
        for (auto node : graph) {
            inDegree[node.first] = 0;
        }
        
        for (auto node : graph) {
            for (auto edge : node.second) {
                inDegree[edge]++;
            }
        }
        
        return inDegree;
    }
    
    string topoSort(unordered_map<char, string> &graph){
        unordered_map<char, int> inDegree = getIndegree(graph);
        priority_queue<char, vector<char>, greater<char>> pq;
        
        for (auto node : inDegree) {
            if (node.second == 0) {
                pq.push(node.first);
            }
        }
        
        string res;
        
        while (!pq.empty()) {
            char node = pq.top(); pq.pop();
            res.push_back(node);
            
            for (auto edge : graph[node]) {
                if (--inDegree[edge] == 0) {
                    pq.push(edge);
                }
            }
        }
        
        if (res.size() != inDegree.size()) {
            return "";
        }
        
        return res;
        
    }
    
    
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, string> graph = buildGraph(words);
        if (graph.empty()) {
            return "";
        }
        return topoSort(graph);
    }
};