//You are given a network of n nodes, labeled from 1 to n. You are also given ti
//mes, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui 
//is the source node, vi is the target node, and wi is the time it takes for a sig
//nal to travel from source to target. 
//
// We will send a signal from a given node k. Return the time it takes for all t
//he n nodes to receive the signal. If it is impossible for all the n nodes to rec
//eive the signal, return -1. 
//
// 
// Example 1: 
//
// 
//Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
//Output: 2
// 
//
// Example 2: 
//
// 
//Input: times = [[1,2,1]], n = 2, k = 1
//Output: 1
// 
//
// Example 3: 
//
// 
//Input: times = [[1,2,1]], n = 2, k = 2
//Output: -1
// 
//
// 
// Constraints: 
//
// 
// 1 <= k <= n <= 100 
// 1 <= times.length <= 6000 
// times[i].length == 3 
// 1 <= ui, vi <= n 
// ui != vi 
// 0 <= wi <= 100 
// All the pairs (ui, vi) are unique. (i.e., no multiple edges.) 
// 
// Related Topics Depth-First Search Breadth-First Search Graph Heap (Priority Q
//ueue) Shortest Path 
// 👍 3247 👎 261


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: Dijkstra (BFS + min heap)
 * time: O(ElogV + E)
 * space: O(V)
 * */
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<vector<int>>> graph; // O(V)
        for (const auto& t : times) { // O(E)
            graph[t[0]].push_back({t[1], t[2]});
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push({0, k}); // {dist, node}

        while (!min_heap.empty()) {
            auto cur = min_heap.top(); min_heap.pop(); // O(logV)
            int cost = cur[0], node = cur[1];
            for (const auto& child : graph[node]) { // O(E)
                int node_next = child[0], weight = child[1];
                if (dist[node_next] > cost + weight) {
                    dist[node_next] = cost + weight;
                    min_heap.push({dist[node_next], node_next});
                }
            }
        }

        int res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(res, dist[i]);
        }

        return res == INT_MAX ? -1 : res;
    }
};


/*
 * solution 2: Dijkstra (BFS + min heap)，加个visited数组，实际没优化多少
 * time: O(ElogV + E)
 * space: O(V)
 * */
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<vector<int>>> graph;
        for (const auto& t : times) {
            graph[t[0]].push_back({t[1], t[2]});
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        vector<int> visited(n + 1);

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push({0, k}); // {dist, node}

        while (!min_heap.empty()) {
            auto cur = min_heap.top(); min_heap.pop();
            int cost = cur[0], node = cur[1];
            if (visited[node]) continue;
            for (const auto& child : graph[node]) {
                int node_next = child[0], weight = child[1];

                if (visited[node_next]) {
                    continue;
                }

                if (dist[node_next] > cost + weight) {
                    dist[node_next] = cost + weight;
                    min_heap.push({dist[node_next], node_next});
                }
            }
            visited[node] = 1;
        }

        int res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(res, dist[i]);
        }

        return res == INT_MAX ? -1 : res;
    }
};


/*
 * solution 3: Bellman-ford
 * time: O(V*E)
 * space: O(V)
 * */

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int INF = 1e9;
        vector<int> dist(n + 1, INF);
        vector<int> backup(n + 1); // 防止串联

        dist[k] = 0;
        for (int i = 0; i < n; i++) // 松弛N次
        {
            backup = dist;
            for (const auto& t : times) { //更新所有边
                dist[t[1]] = min(dist[t[1]], backup[t[0]] + t[2]);
            }
        }

        int res = *max_element(dist.begin() + 1, dist.end());
        return res == INF ? -1 : res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
