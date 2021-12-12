//You are in a city that consists of n intersections numbered from 0 to n - 1 wi
//th bi-directional roads between some intersections. The inputs are generated suc
//h that you can reach any intersection from any other intersection and that there
// is at most one road between any two intersections. 
//
// You are given an integer n and a 2D integer array roads where roads[i] = [ui,
// vi, timei] means that there is a road between intersections ui and vi that take
//s timei minutes to travel. You want to know in how many ways you can travel from
// intersection 0 to intersection n - 1 in the shortest amount of time. 
//
// Return the number of ways you can arrive at your destination in the shortest 
//amount of time. Since the answer may be large, return it modulo 109 + 7. 
//
// 
// Example 1: 
//
// 
//Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1]
//,[2,5,1],[0,4,5],[4,6,2]]
//Output: 4
//Explanation: The shortest amount of time it takes to go from intersection 0 to
// intersection 6 is 7 minutes.
//The four ways to get there in 7 minutes are:
//- 0 ➝ 6
//- 0 ➝ 4 ➝ 6
//- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
//- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
// 
//
// Example 2: 
//
// 
//Input: n = 2, roads = [[1,0,10]]
//Output: 1
//Explanation: There is only one way to go from intersection 0 to intersection 1
//, and it takes 10 minutes.
// 
//
// 
// Constraints: 
//
// 
// 1 <= n <= 200 
// n - 1 <= roads.length <= n * (n - 1) / 2 
// roads[i].length == 3 
// 0 <= ui, vi <= n - 1 
// 1 <= timei <= 109 
// ui != vi 
// There is at most one road connecting any two intersections. 
// You can reach any intersection from any other intersection. 
// 
// 👍 138 👎 5


//leetcode submit region begin(Prohibit modification and deletion)

#define ll long long
#define pll pair<ll, ll>
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<vector<pll>> graph(n);//每个节点有多条边，把边和权重用pair存起来
        for (auto &road : roads) {
            ll u = road[0], v = road[1], w = road[2];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        return dijkstra(graph, n, 0);
    }

    int dijkstra(const vector<vector<pll>> &graph, int n, int src) {
        vector<ll> dist(n, LONG_MAX);
        vector<ll> paths(n);
        int MOD = 1e9 + 7;

        paths[src] = 1;
        dist[src] = 0;

        priority_queue<pll, vector<pll>, greater<pll>> minHeap;
        minHeap.push({dist[src], src});

        while (!minHeap.empty()) {
            auto [d, u] = minHeap.top(); minHeap.pop();
            // 当距离dd未更新到最新版本时，直接跳过
            if (d > dist[u]) {
                continue;
            }

            /* dist[v]表示src到v的距离。d表示src到u的距离。w表示u到v的距离。
             所以d + w应为src到v的距离。如果我们发现期间有更短的距离，就会在这里更新
             因为dist初始化为无穷大，所以这里肯定会首先被更新，后面就看路径的分布情况
            */
            for (auto &[v, w] : graph[u]) {
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    paths[v] = paths[u];
                    minHeap.push({dist[v], v});
                }
                else if (d + w == dist[v]){
                    paths[v] = (paths[v] + paths[u]) % MOD;
                }
            }
        }

        return paths[n - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)
