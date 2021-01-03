/*
Solution 1: Topological Sort
time: O(|E|*|V|), E is the number of edges, V is the number of vertices
space: O(|E|+|V|)
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty() || prerequisites[0].empty())
            return true;
        
        int res = numCourses;
        
        // calculate the in-degree for classes which have prerequisites
        vector<int> inDegree(numCourses);
        for (auto& edge : prerequisites) {
            ++inDegree[edge[0]];
        }
        
        // add the courses that are already taken, inDegree=0
        queue<int> q;
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0) 
                q.push(i);
        }
        
        while (!q.empty()) {
            int node = q.front(); q.pop();
            --res;
            for (auto& edge : prerequisites) {
                if (edge[1] == node) {
                    if (--inDegree[edge[0]] != 0) 
                        continue;
                    q.push(edge[0]);
                }
            }
        }
        
        return res == 0;
    }
};


/*
Solution 2: Optimized Topological Sort
time: O(|E|+|V|), E is the number of edges, V is the number of vertices
space: O(|E|+|V|)
*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty() || prerequisites[0].empty())
            return true;
        
        int res = numCourses;
        
        unordered_map<int, vector<int>> neighbors;    
        // calculate the in-degree for classes which have prerequisites
        vector<int> inDegree(numCourses);
        for (auto& edge : prerequisites) {
            ++inDegree[edge[0]];
            neighbors[edge[1]].push_back(edge[0]);
        }
        
        // add the courses that are already taken, inDegree=0
        queue<int> q;
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0) 
                q.push(i);
        }
        
        while (!q.empty()) {
            int node = q.front(); q.pop();
            --res;
            for (auto& neighbor : neighbors[node]) {
                if (--inDegree[neighbor] != 0) 
                    continue;
                q.push(neighbor);
            }
        }
        
        return res == 0;
    }
};