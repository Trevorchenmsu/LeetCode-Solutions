/*
Solution : Union Find
time: O(m*alpha(n)), Alpah is a certain inverse function of Ackerman. it can be seen as smaller than 4 
space: O(n)
*/

class Solution {
private:
    int find(vector<int> &pre, int node) {
        return pre[node] == node ? node : pre[node] = find(pre, pre[node]);
    }
    
    
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> pre(n + 2);
        
        for (int i = 0; i < n; ++i) {
            pre[i] = i;
        }
        
        int numOfEdges = edges.size();
        for (int i = 0; i < numOfEdges; ++i) {
            int u = edges[i][0], v = edges[i][1];
            int root_u = find(pre, u), root_v = find(pre, v);
            if (root_u != root_v) {
                pre[root_v] = root_u;
            }
        }
        
        int res = 0;
        for (int i = 0; i < n; ++i) {
            if (find(pre, i) == i)
                ++res;
        }
        
        return res;
    }
};