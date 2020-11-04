/*
Solution 1: without using hashmap, slower
time: O(n), n is the number of edges
space: O(m), m is the number of vertices
*/


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        vector<int> inDegree(numCourses);
        
        // get the indegree
        for (auto &edge : prerequisites) {
            inDegree[edge[0]]++;
        }
        
        queue<int> q;
        
        // get the nodes with indegree=0
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0) 
                q.push(i);
        }
        
        // BFS
        while (!q.empty()) {
            int node = q.front(); q.pop();
            res.push_back(node);
            
            for (auto &edge : prerequisites) {
                if (node != edge[1]) {
                    continue;
                }
                if(--inDegree[edge[0]] == 0) {
                    q.push(edge[0]);
                }
            }
        }
        return res.size() == numCourses ? res : vector<int> {};
    }
};

/*
Solution 2: using hashmap, faster
time: O(n), n is the number of edges
space: O(m), m is the number of vertices
*/
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> res;
        vector<int> inDegree(numCourses);
        // define a hashmap to store the neighbors
        unordered_map<int, vector<int>> edgeMap;
        
        // get the indegree
        for (auto &edge : prerequisites) {
            inDegree[edge[0]]++;
            edgeMap[edge[1]].push_back(edge[0]);
        }
        
        queue<int> q;
        
        // get the nodes with indegree=0
        for (int i = 0; i < inDegree.size(); ++i) {
            if (!inDegree[i]) 
                q.push(i);
        }
        
        // BFS
        while (!q.empty())
        {
            int node = q.front(); q.pop();
            res.push_back(node);
            
            for (auto& neighbor: edgeMap[node])
            {
                if(--inDegree[neighbor] == 0) q.push(neighbor);
            }
        }

        return res.size() == numCourses ? res : vector<int> {};
    }
};