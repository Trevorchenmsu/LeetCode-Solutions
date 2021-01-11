/*
solution 1: DFS + memo
time: O(V+E)
space: O(V+E)
*/
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        unordered_map<int, unordered_set<int>> graph;
        // build graph
        for (auto& dis : dislikes) {
            graph[dis[0]].insert(dis[1]);
            graph[dis[1]].insert(dis[0]);
        }
        
        vector<int> color(N + 1, 0); 
        // color the nodes: blue-1 and red-2
        for (int i = 1; i <= N; ++i) {
            if (color[i] == 0) {
                color[i] = 1;
                dfs(i, 1, graph, color);
                if (!res) return res;
            }
        }
        return res;
    }
private:
    bool res = true;
    void dfs(int id, int col, unordered_map<int, unordered_set<int>>& graph, vector<int>& color) {
        if (!res)
            return;
        int nextColor = col == 1 ? 2 : 1;
        for (int e : graph[id]) {
            if (color[e] == col)
                res = false;
            if (color[e] == 0){
                color[e] = nextColor;
                dfs(e, nextColor, graph, color);
            }
        }
    }
};

/*
solution 2: BFS + memo
time: O(V+E)
space: O(V+E)
*/
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        unordered_map<int, unordered_set<int>> graph;
        // build graph
        for (auto& dis : dislikes) {
            graph[dis[0]].insert(dis[1]);
            graph[dis[1]].insert(dis[0]);
        }
        
        vector<int> color(N + 1, 0); 
        // color the nodes: blue-1 and red-2
        for (int i = 1; i <= N; ++i) {
            if (color[i] == 0) {
                color[i] = 1;
                bfs(i, graph, color);
                if (!res) return res;
            }
        }
        return res;
    }
private:
    bool res = true;
    void bfs(int id, unordered_map<int, unordered_set<int>>& graph, vector<int>& color) {
        queue<int> q;
        q.push(id);
        int nextColor;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            nextColor = color[cur] == 1 ? 2 : 1;
            for (int e : graph[cur]) {
                if (color[e] == color[cur])
                    res = false;
                if (color[e] == 0){
                    color[e] = nextColor;
                    q.push(e);
                }
            }
        }
    }
};

/*
solution 3: union find
time: O(V+E)
space: O(V+E)
*/