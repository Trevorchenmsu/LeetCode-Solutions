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
        vector<int> k{};
        return res.size() == numCourses ? res : k;
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
        vector<int> degrees(numCourses, 0);
        unordered_map<int, vector<int>> m;
        
        for (vector<int> &pq: prerequisites)
        {
            degrees[pq[0]]++;
            m[pq[1]].push_back(pq[0]);
        }
        
        vector<int> result;
        queue<int> q;
        for (int i = 0; i < degrees.size(); i++)
        {
            if (!degrees[i])
                q.push(i);
        }
        
        while (!q.empty())
        {
            int lo = q.front();
            q.pop();
            result.push_back(lo);
            auto &lst = m[lo];
            for (int &hi: lst)
            {
                if (!--degrees[hi])
                {
                    q.push(hi);
                }
            }
        }
        for (int n: degrees)
        {
            if (n)
            {
                return {};
            }
        }
        return result;
    }
};