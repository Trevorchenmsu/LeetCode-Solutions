/*
solution: backtracking
time: O(n*2^n), n is the number of nodes, each time we add a node, the number of path would double.
space: O(n*2^n)
*/
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> res;
        if (graph.empty() || graph.size() == 0 || graph[0].empty() || graph[0].size() == 0)
            return res;
        
        vector<int> path;
        path.push_back(0);
        backtrack(graph, path, res, 0);
        return res;       
    }
    
    void backtrack(vector<vector<int>>& graph, vector<int>& path, vector<vector<int>>& res, int idx) {
        if (idx == graph.size() - 1) {
            res.push_back(path);
            return;
        }
        
        for (int i = 0; i < graph[idx].size(); ++i) {
            path.push_back(graph[idx][i]);
            backtrack(graph, path, res, graph[idx][i]);
            path.pop_back();
        }
    }
};
