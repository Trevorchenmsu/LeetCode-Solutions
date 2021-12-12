//You have an undirected, connected graph of n nodes labeled from 0 to n - 1. Yo
//u are given an array graph where graph[i] is a list of all the nodes connected w
//ith node i by an edge. 
//
// Return the length of the shortest path that visits every node. You may start 
//and stop at any node, you may revisit nodes multiple times, and you may reuse ed
//ges. 
//
// 
// Example 1: 
//
// 
//Input: graph = [[1,2,3],[0],[0],[0]]
//Output: 4
//Explanation: One possible path is [1,0,2,0,3]
// 
//
// Example 2: 
//
// 
//Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
//Output: 4
//Explanation: One possible path is [0,1,4,2,3]
// 
//
// 
// Constraints: 
//
// 
// n == graph.length 
// 1 <= n <= 12 
// 0 <= graph[i].length < n 
// graph[i] does not contain i. 
// If graph[a] contains b, then graph[b] contains a. 
// The input graph is always connected. 
// 
// Related Topics Dynamic Programming Bit Manipulation Breadth-First Search Grap
//h Bitmask 
// 👍 1166 👎 94


//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();

        // 假如有4个节点，最后要访问到的情况是它们的位都变成1，所以final state的位表示位1111
        int finalState = 0;
        for (int i = 0; i < n; i++) {
            finalState = finalState | (1 << i);
        }

        queue<pair<int, int>> q;
        vector<vector<bool>> visited (n, vector<bool> (finalState));

        // q中存的是初始的每个节点及其位状态：0->0001,1->0010,2->0100,3->1000
        for (int i = 0; i < n; i++) {
            q.push({i, (1 << i)});
            visited[i][(1 << i)] = true;
        }

        // 模板bfs分层遍历求最短路径
        int step = -1;
        while (!q.empty()) {
            step++;
            int len = q.size();
            while (len--) {
                int node = q.front().first;
                int state = q.front().second;
                q.pop();

                for (int next : graph[node]) {
                    // next为下一个邻居，用它跟当前状态state求或，目的是为了合并有1的状态
                    // 如果最终合并后的结果满足1111，表示四个节点都被访问了，所以在这里返回step+1
                    // 因为要算入这个next这一层
                    int nextState = (state | 1 << next);
                    if (nextState == finalState)
                        return step + 1;

                    if (visited[next][nextState])
                        continue;

                    q.push({next, nextState});
                    visited[next][nextState] = true;
                }
            }
        }
        return 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
