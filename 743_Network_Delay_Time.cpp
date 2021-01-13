/*
solution 1: Dijkstra
time: O(n^2)
space: O(n^2)
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        if (times.empty() || times[0].empty())
            return -1;
        
        const int INF = 0X3f3f3f3f;
        // define adjacent matrix
        vector<vector<int>> adj(n + 1, vector<int> (n + 1, INF));
        for (auto &t : times) {
            adj[t[0]][t[1]] = t[2];
        }
        
        vector<int> dist(n + 1, INF); // shortest distance from start vertex to current vertex;
        vector<bool> visited(n + 1, false); // represent the state of vertices that have been considered.
        
        dist[k] = 0;
        for (int i = 1; i < n; ++i) { // consider n-1 vertices except for the start vertex
            int t = -1;
            // find the vertex closest to the start vertex
            for (int j = 1; j <= n; ++j) {
                if (!visited[j] && (t == -1 || dist[j] < dist[t]))
                    t = j;
            }
            
            // update the distance from t vertex to other vertices
            for (int j = 1; j <= n; ++j) {
                dist[j] =  min(dist[j], dist[t] + adj[t][j]);
            }
            
            visited[t] = true;
        }
        
        int res = *max_element(dist.begin() + 1, dist.end());
        return res == INF ? -1 : res;
    }
};

/*
solution 2: Dijkstra + heap
time: O(nlogn)
space: O(n)
*/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int INF = 0x3f3f3f3f;
        vector<bool> visited(N + 1, false); 
        vector<int> dist(N + 1, INF); // shortest distance array
        typedef pair<int, int> pt; // first is distance, second is vertex
        unordered_map<int, vector<pt>> graph; // adjacent tabel
        priority_queue<pt, vector<pt>, greater<pt>> heap; // mini-heap, closest vertext to start vertex
        
        // define adjacent table
        for (auto &t: times){ 
            graph[t[0]].push_back({t[2],t[1]});
        }
        
        // BFS
        heap.push({0, K});
        dist[K] = 0;
        while(heap.size()){
            auto cur = heap.top(); heap.pop();
            int distance = cur.first, vertex = cur.second;
            if (visited[vertex]) continue; 
            for (auto &p: graph[vertex]){
                if (dist[p.second] > distance + p.first){ // Dijkstra 
                    dist[p.second] = distance + p.first;
                    heap.push({dist[p.second], p.second});
                }
            }
            visited[vertex] = true;
        }
        int res = *max_element(dist.begin()+1, dist.end());
        return res == INF ? -1: res;
    }
};

/*
solution 3: Bellmon-Ford
time: O(mn)
space: O(n)
*/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // Bellmon-Ford
        const int INF = 0x3f3f3f3f;
        vector<int> dist(N + 1, INF); // 到起点的最短距离
        vector<int> backup(N + 1); // 防止串联

        dist[K] = 0;
        for (int i = 0; i <= N; i++){ // 松弛N 次
            backup.assign(dist.begin(), dist.end());
            for (auto &t: times){ // 枚举所有边
                dist[t[1]] = min(dist[t[1]], backup[t[0]] + t[2]); // 更新最短路
            }
        }
        int ans = *max_element(dist.begin() + 1, dist.end());
        return ans > INF/2 ? -1: ans; // INF/2 是因为可能有负权边；这个题没有负权边，可以用INF
    }
};

/*
solution 4: SPFA
time: O(m), worst is O(mn)
space: O(n)
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        //spfa
        const int INF = 0x3f3f3f3f;
        vector<int> dist(N+1, INF); // 保存到起点的距离
        vector<bool> st(N+1, false); // 是否最短
        typedef pair<int, int> PII;
        unordered_map<int, vector<PII>> edges; // 邻接表

        queue<int> q;
        q.push(K);
        dist[K] = 0;
        st[K] = true; // 是否在队列中

        for (auto &t: times){
            edges[t[0]].push_back({t[1], t[2]});
        }

        while (!q.empty()){ // 当没有点可以更新的时候，说明得到最短路
            auto t = q.front();
            q.pop();
            st[t] = false;
            for (auto &e: edges[t]){ // 更新队列中的点出发的 所有边
                int v = e.first, w = e.second;
                if (dist[v] > dist[t] + w){
                    dist[v] = dist[t] + w;
                    if (!st[v]){
                        q.push(v);
                        st[v] = true;
                    }
                }
            }
        }
        int ans = *max_element(dist.begin()+1, dist.end());
        return ans == INF ? -1: ans;
    }
};

/*
solution 5: Floyd
time: O(n^3)
space: O(n)
*/
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int INF = 0x3f3f3f3f;
        vector<vector<int>> d(N + 1, vector<int>(N + 1, INF));
        for (int i = 1; i<= N; i++) d[i][i] = 0;

        for (auto &t: times){
            d[t[0]][t[1]] = min(d[t[0]][t[1]], t[2]);
        }

        for (int k = 1; k<= N; k++){
            for (int i = 1; i<= N; i++){
                for (int j = 1; j<= N; j++){
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
        
        int ans = 0;
        for (int i =1; i<=N; i++){
            ans = max(ans, d[K][i]);
        }
        return ans > INF/2 ? -1: ans;
    }
};


