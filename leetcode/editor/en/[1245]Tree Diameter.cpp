//Given an undirected tree, return its diameter: the number of edges in a longes
//t path in that tree. 
//
// The tree is given as an array of edges where edges[i] = [u, v] is a bidirecti
//onal edge between nodes u and v. Each node has labels in the set {0, 1, ..., edg
//es.length}. 
//
// 
// Example 1: 
//
// 
//
// 
//Input: edges = [[0,1],[0,2]]
//Output: 2
//Explanation: 
//A longest path of the tree is the path 1 - 0 - 2.
// 
//
// Example 2: 
//
// 
//
// 
//Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
//Output: 4
//Explanation: 
//A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
// 
//
// 
// Constraints: 
//
// 
// 0 <= edges.length < 10^4 
// edges[i][0] != edges[i][1] 
// 0 <= edges[i][j] <= edges.length 
// The given edges form an undirected tree. 
// 
// Related Topics Tree Depth-First Search Breadth-First Search 
// 👍 518 👎 11


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: bfs
 * time: O(E + V)
 * space: O(V)
 * */
class Solution {
public:
    vector<vector<int>> adj;
    int V;
    int treeDiameter(vector<vector<int>>& edges) {
        V = edges.size() + 1;
        adj.resize(V);

        for (auto edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // 这里pair存的是路径的终点以及路径长度
        pair<int, int> t1 = bfs(0);
        pair<int, int> t2 = bfs(t1.first);

        return t2.second;
    }

    pair<int, int> bfs(int u) {
        vector<int> dist(V, -1);
        queue<int> q;
        q.push(u);

        dist[u] = 0;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (auto it = adj[cur].begin(); it != adj[cur].end(); it++) {
                int node = *it;
                if (dist[node] == -1) {
                    q.push(node);
                    dist[node] = dist[cur] + 1;
                }
            }
        }

        int max_dist = 0, max_node = 0;
        for (int i = 0; i < V; i++) {
            if (dist[i] > max_dist) {
                max_dist = dist[i];
                max_node = i;
            }
        }

        return make_pair(max_node, max_dist);
    }
};
//leetcode submit region end(Prohibit modification and deletion)
