//There are n cities connected by some number of flights. You are given an array
// flights where flights[i] = [fromi, toi, pricei] indicates that there is a fligh
//t from city fromi to city toi with cost pricei. 
//
// You are also given three integers src, dst, and k, return the cheapest price 
//from src to dst with at most k stops. If there is no such route, return -1. 
//
// 
// Example 1: 
//
// 
//Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k =
// 1
//Output: 200
//Explanation: The graph is shown.
//The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as mar
//ked red in the picture.
// 
//
// Example 2: 
//
// 
//Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k =
// 0
//Output: 500
//Explanation: The graph is shown.
//The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as mar
//ked blue in the picture.
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 100 
// 0 <= flights.length <= (n * (n - 1) / 2) 
// flights[i].length == 3 
// 0 <= fromi, toi < n 
// fromi != toi 
// 1 <= pricei <= 104 
// There will not be any multiple flights between two cities. 
// 0 <= src, dst, k < n 
// src != dst 
// 
// Related Topics Dynamic Programming Depth-First Search Breadth-First Search Gr
//aph Heap (Priority Queue) Shortest Path 
// 👍 3932 👎 160


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: bfs + min heap, TLE
 * time: O((VlogV)^(k+1))
 * space: O(V)
 * */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if (flights.empty() || flights.size() == 0) {
            return -1;
        }

        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto f : flights) { // O(E)
            graph[f[0]].push_back(make_pair(f[1], f[2]));
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push({0, src, k + 1}); // {cost, city, steps}

        while (!min_heap.empty()) { // O(VlogV + V*E)
            auto cur = min_heap.top();
            min_heap.pop(); // O(logV)
            int cost = cur[0], city = cur[1], steps = cur[2];
            if (city == dst) {
                return cost;
            }

            if (steps <= 0) {
                continue;
            }

            for (auto child : graph[city]) { // O(E)
                int neighbor = child.first, weight = child.second;
                min_heap.push({cost + weight, neighbor, steps - 1});
            }
        }

        return -1;
    }
};

/*
 * solution 2: bfs + queue, TLE
 * time: O(V^(k+1))
 * space: O(V)
 * */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if (flights.empty() || flights.size() == 0) {
            return -1;
        }

        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto f : flights) { // O(E)
            graph[f[0]].push_back(make_pair(f[1], f[2]));
        }

        bfs(graph, src, dst, k);
        return res == INF? -1 : res;
    }

    const int INF = 0x3f3f3f3f;
    int res = INF;
    void bfs(unordered_map<int, vector<pair<int, int>>>& graph, int src, int dst, int K) {
        queue<pair<int, int>> q;
        q.push({src, 0}); // {city, cost}

        int step = 0;
        while (!q.empty() && step <= K) {
            int len = q.size();
            while (len--) {
                auto cur = q.front(); q.pop();
                int city = cur.first, cost = cur.second;
                for (auto& neighbor : graph[city]) {
                    if (cost + neighbor.second > res) {
                        continue;
                    }

                    // 整个解法中最关键的一点：当抵达终点后不能马上返回，因为k没还有达到
                    // 提交抵达dst的路径不一定是题目要求的。
                    if (neighbor.first == dst) {
                        res = min(res, neighbor.second + cost);
                    }

                    q.push({neighbor.first, neighbor.second + cost});
                }
            }
            step++;
        }
    }
};

/*
 * solution 3: dfs, TLE
 * time: O(V^(k+1))
 * space: O(V)
 * */
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
 * solution 4: Dijkstra (BFS + queue + dist), pass
 * time: O(V*E)，因为队列中的点不止访问一次，最差情况是访问V次，每次都考虑对应的E条边
 * space: O(V)
 * */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if (flights.empty() || flights[0].empty())
            return -1;

        // 建图
        unordered_map<int, vector<pair<int, int>>> graph; // O(V)
        for (auto& flight : flights) { // O(E)
            graph[flight[0]].push_back({flight[1], flight[2]});
        }

        // 定义Dijkstra数组和初始化
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // bfs
        queue<pair<int, int>> q{{{src, 0}}}; // {city, price}
        k++;
        while (!q.empty()) {
            int len = q.size();
            k--;
            if (k < 0) break;
            while (len--) {
                auto cur = q.front(); q.pop();
                int city = cur.first, price = cur.second;
                for (auto neighbor : graph[city]) {
                    int city_next = neighbor.first, price_next = neighbor.second;
                    if (dist[city_next] > price + price_next) {
                        dist[city_next] = price + price_next;
                        q.push({city_next, dist[city_next]});
                    }
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};


/*
 * solution 5: Dijkstra (BFS + heap + dist), pass
 * time: O(V*(logV+E))
 * space: O(V)
 * */

class Solution {
public:

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if (flights.empty() || flights[0].empty())
            return -1;

        // 建图
        unordered_map<int, vector<pair<int, int>>> graph; // O(V)
        for (auto& flight : flights) { // O(E)
            graph[flight[0]].push_back({flight[1], flight[2]});
        }

        return getCheapestPath(src, dst, graph, k, n);
    }

    int getCheapestPath(int src, int dst, unordered_map<int, vector<pair<int,int>>>& graph, int k, int n) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push({0, src, 0}); // {cost, city, stop}

        vector<int> dist(n, INT_MAX), currstops(n, INT_MAX), prev(n, -1);
        dist[src] = 0;
        currstops[src] = 0;

        while(!min_heap.empty()) {
            auto cur = min_heap.top(); min_heap.pop();
            int cost = cur[0], city = cur[1], stop = cur[2];

            if(city == dst){
                return cost;
            }

            if(stop == k + 1)  {
                continue;
            }

            for (auto &child : graph[city]) {
                int city_next = child.first, cost_next = child.second;
                if (dist[city_next] > cost + cost_next) {
                    dist[city_next] = cost + cost_next;
                    prev[city_next] = city;
                    min_heap.push({dist[city_next], city_next, stop + 1});
                }
                else if (stop < currstops[city_next]) {
                    min_heap.push({cost + cost_next, city_next, stop + 1});
                }

                currstops[city_next] = stop;
            }

        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};


/*
 * solution 6: 二维dp, bellman-ford, pass
 * time: O(kE)
 * space: O(kV)
 * */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        if (flights.empty() || flights[0].empty())
            return -1;

        const int INF = 0x3f3f3f3f;
        int res = INF;

        // dp[i][j]表示经过j次中转到达i位置的最少价格
        vector<vector<int>> dp(n, vector<int>(K + 2, INF));
        for(int i = 0; i <= K + 1; i++)
            dp[src][i] = 0; // 因为是起点，所以不管多少次航班，价格都是0

        // Bellman-ford的主体思想：遍历V-1次（这里用K次代替），每一次遍历所有边并更新，循环结束后从dist数组选取目标点的价格
        for(int i = 1; i <= K + 1; i++){
            for(auto& f : flights){
                dp[f[1]][i] = min(dp[f[1]][i], dp[f[0]][i - 1] + f[2]);
            }
        }

        return dp[dst][K + 1] == INF? -1 : dp[dst][K + 1];
    }
};


/*
 * solution 7: 一维dp, bellman-ford, pass
 * time: O(kE)
 * space: O(V)
 * */
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int MAX = 1e9;
        vector<int> dist(n, MAX);
        dist[src] = 0;
        int res = MAX;

        for (int i = 0; i <= k; i++) {
            auto cur = dist;
            for (auto f : flights) {
                cur[f[1]] = min(cur[f[1]], dist[f[0]] + f[2]);
            }
            res = min(res, cur[dst]);
            dist = cur;
        }

        return res == MAX ? -1 : res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
