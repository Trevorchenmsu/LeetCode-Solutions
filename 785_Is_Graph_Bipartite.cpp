/*
solution 1: dfs
time: O(V+E)
space: O(V)
*/

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // 0 for white, 1 for blue, 2 for red
        vector<int> color(n, 0);
        for (int i = 0; i < n; ++i) {
            if (color[i] == 0)
                dfs(graph, color, 1, i); 
        }
        return res;
    }
    
private:
    bool res = true;
    void dfs(vector<vector<int>>& graph, vector<int>& color, int col, int vertex) {
        if (!res) return;
        color[vertex] = col;
        int nextColor = col == 1 ? 2 : 1;
        for (auto &neighbor : graph[vertex]) {
            if (color[neighbor] == col) res = false;
            if (color[neighbor] == 0) {
                color[neighbor] = nextColor;
                dfs(graph, color, nextColor, neighbor);
                if (!res) return;
            }
        }
    }
};

/*
solution 2: bfs
time: O(V+E)
space: O(V+E)
*/
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // 0 for white, 1 for blue, 2 for red
        vector<int> color(n, 0);
        for (int i = 0; i < n; ++i) {
            if (color[i] == 0)
                bfs(graph, color, i, 1); 
        }
        return res;
    }
    
private:
    bool res = true;
    void bfs(vector<vector<int>>& graph, vector<int>& color, int vertex, int col) {
        queue<int> q;
        q.push(vertex);
        color[vertex] = col;
        while (!q.empty()){
            int cur = q.front(); q.pop();
            int nextColor = color[cur] == 1 ? 2 : 1;   
            for (auto &neighbor : graph[cur]) {
                if (color[neighbor] == color[cur]) {
                    res = false;
                    return;
                }
                if (color[neighbor] == 0) {
                    color[neighbor] = nextColor;
                    q.push(neighbor);
                }
            }
        }
    }
};

