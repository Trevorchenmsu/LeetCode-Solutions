/*
solution: topological sort
time:O((V+E)*P)?
space:O((V+E)*P)?
*/

class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> res(queries.size());
        if (prerequisites.empty() || prerequisites[0].size() == 0)
            return res;
        
        vector<int> inDegree(n);
        unordered_map<int, vector<int>> neighbors;    
        vector<unordered_set<int>> path(n, unordered_set<int>());
        
        // calculate the in-degree
        for (auto& edge : prerequisites) {
            ++inDegree[edge[1]];
            neighbors[edge[0]].push_back(edge[1]);
        }
        
        // add the courses inDegree=0
        queue<int> q;
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0) 
                q.push(i);
        }
        
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (auto neighbor : neighbors[node]) {
                // include all the path nodes from previous node
                for (auto p : path[node]) {
                    path[neighbor].insert(p);    
                }
                // include previous node
                path[neighbor].insert(node);
                
                if (--inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }
        
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = (path[queries[i][1]].count(queries[i][0]) != 0);
        }
        
        return res;
    }
};