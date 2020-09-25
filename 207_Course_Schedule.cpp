/*
BFS
time: O(m), m is the number of edges
space: O(n), n is the number of vertices
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty() || prerequisites.size () == 0 ||
            prerequisites[0].empty() || prerequisites[0].size() == 0)
            return true;
        
        int res = numCourses;
        vector<int> inDegree(numCourses);
        
        // get the indegree
        for (auto &edge : prerequisites) {
            inDegree[edge[0]]++;
        }
        
        queue<int> q;
        
        // get the nodes with indegree = 0
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0)
                q.push(i);
        }
        
        // BFS
        while (!q.empty()) {
            int node = q.front();q.pop();
            --res;
            for (auto &edge : prerequisites) {
                if (edge[1] == node) {
                    if (--inDegree[edge[0]] == 0) {
                        q.push(edge[0]);
                    }
                }
            }
        }
        
        return res == 0;
    }
};