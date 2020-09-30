/*
Solution 1: BFS
time: O(max(m,n)), n is the number of vertices, m is the number of edges
space: O(n^2)
*/

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        int numOfEdge = edges.size();
        // has a circle
        if (numOfEdge !=  n - 1)
            return false;
        
        // build adjacent matrix
        vector<vector<int>> adjm(n, vector<int> (n));
        for (int i = 0; i < numOfEdge; ++i) {
            int u = edges[i][0], v = edges[i][1]; // u, v are the left and right points on the edge
            adjm[u][v] = adjm[v][u] = 1;
        }
        
        vector<int> visited(n);
        visited[0] = 1;
        int numOfVisit = 1;
        queue<int> q;
        q.push(0);
        
        while (!q.empty()){
            int node = q.front(); q.pop();
            for (int i = 0; i < n; ++i) {
                if (adjm[node][i] != 1) 
                    continue;
                if (!visited[i]) {
                    visited[i] = 1;
                    ++numOfVisit;
                    q.push(i);
                }
            }
            
        }
        
        if (numOfVisit != n)
            return false;
        
        return true;
        
    }
};

/*
Solution 1: Union Find
time: O(m*alpha(n)), Alpah is a certain inverse function of Ackerman. it can be seen as smaller than 4 
space: O(n)
*/

class Solution {
private:
    int find(vector<int> &pre, int node) {
        // find and path compression
        return pre[node] == node ? node : pre[node] = find(pre, pre[node]);
    }
    
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // build prior node array
        vector<int> pre(n + 2);
        
        // initialize pre
        for (int i = 0; i < n; ++i) {
            pre[i] = i;
        }
        
        // check cycle
        int numOfEdge = edges.size();
        for (int i = 0; i < numOfEdge; ++i) {
            int u = edges[i][0], v = edges[i][1];
            int root_u = find(pre, u), root_v = find(pre, v);
            if (root_u == root_v) {
                return false;
            } else {
                pre[root_v] = root_u; // or pre[root_u] = root_v. it doesn't matter as it is undirected
            }
        }
        
        // check how many root nodes
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (find(pre, i) == i)
                ++count;
        }
        
        if (count == 1)
            return true;
        
        return false;
    }
};
