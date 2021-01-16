/*
solution 1: dfs
time: O(V+E)
space:O(V)
*/
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        if (flights.empty() || flights[0].empty()) 
            return -1;
        
        // build graph
        unordered_map<int, vector<pair<int, int>>> graph; // O(V)/O(n)
        for (auto& flight : flights) { // O(E)
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
        
        dfs(graph, src, dst, K, 0);
        return res == INF? -1 : res;
    }
    
private:
    const int INF = 0x3f3f3f3f;
    int res = INF;
    void dfs( unordered_map<int, vector<pair<int, int>>>& graph, int src, int dst, int K, int cost) {
        if (src == dst) {
            res = min(res, cost);
            return;
        }
        
        if (K < 0) return;
        
        for (auto& neighbor : graph[src]) {
            if (cost + neighbor.second > res) continue;
            dfs(graph, neighbor.first, dst, K - 1, cost + neighbor.second);
        }
        
    }
};

/*
solution 2: bfs
time: O(V+E)
space:O(V)
*/
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        if (flights.empty() || flights[0].empty()) 
            return -1;
        
        // build graph
        unordered_map<int, vector<pair<int, int>>> graph; // O(V)/O(n)
        for (auto& flight : flights) { // O(E)
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
        
        bfs(graph, src, dst, K); // O(V)
        return res == INF? -1 : res;
    }
    
private:
    const int INF = 0x3f3f3f3f;
    int res = INF;
    void bfs(unordered_map<int, vector<pair<int, int>>>& graph, int src, int dst, int K) {
        queue<pair<int, int>> q;
        q.push({src, 0});
        
        int step = 0;
        while (!q.empty() && step <= K) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                pair<int, int> cur = q.front(); q.pop();
                for (auto& neighbor : graph[cur.first]) {
                    if (cur.second + neighbor.second > res) continue;
                    if (neighbor.first == dst)
                        res = min(res, neighbor.second + cur.second);
                    q.push({neighbor.first, neighbor.second + cur.second});
                }
            }
            step++;
        }
    }
};

/*
solution 3: DP
time: O(n*E)
space:O(n*K)
*/
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        if (flights.empty() || flights[0].empty()) 
            return -1;
        
        vector<vector<int>> dp(n, vector<int>(K + 2, INF)); // 经过k个中转到达i
        for(int i = 0; i <= K + 1; i++)
            dp[src][i] = 0;
        for(int i = 1; i <= K + 1; i++){
            for(auto& flight : flights){
                if(dp[flight[0]][i - 1] != INF)
                    dp[flight[1]][i] = min(dp[flight[1]][i], dp[flight[0]][i - 1] + flight[2]);
            }
        }
        res = dp[dst][K + 1];
        
        return res == INF? -1 : res;
    }
    
private:
    const int INF = 0x3f3f3f3f;
    int res = INF;
};