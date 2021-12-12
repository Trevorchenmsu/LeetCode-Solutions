//There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is
// only one way to travel between two different cities (this network form a tree).
// Last year, The ministry of transport decided to orient the roads in one directi
//on because they are too narrow. 
//
// Roads are represented by connections where connections[i] = [ai, bi] represen
//ts a road from city ai to city bi. 
//
// This year, there will be a big event in the capital (city 0), and many people
// want to travel to this city. 
//
// Your task consists of reorienting some roads such that each city can visit th
//e city 0. Return the minimum number of edges changed. 
//
// It's guaranteed that each city can reach city 0 after reorder. 
//
// 
// Example 1: 
//
// 
//Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
//Output: 3
//Explanation: Change the direction of edges show in red such that each node can
// reach the node 0 (capital).
// 
//
// Example 2: 
//
// 
//Input: n = 5, connections = [[1,0],[1,2],[3,2],[3,4]]
//Output: 2
//Explanation: Change the direction of edges show in red such that each node can
// reach the node 0 (capital).
// 
//
// Example 3: 
//
// 
//Input: n = 3, connections = [[1,0],[2,0]]
//Output: 0
// 
//
// 
// Constraints: 
//
// 
// 2 <= n <= 5 * 104 
// connections.length == n - 1 
// connections[i].length == 2 
// 0 <= ai, bi <= n - 1 
// ai != bi 
// 
// Related Topics Depth-First Search Breadth-First Search Graph 
// 👍 923 👎 25


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution: bfs
 * time: O(V+E) = O(n)
 * space: O(n^2)
 * */
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> faceout(n), facein(n);
        vector<int> visited(n);

        for (auto& c : connections) { // O(n)
            faceout[c[0]].push_back(c[1]);
            facein[c[1]].push_back(c[0]);
        }

        queue<int> q;
        q.push(0);
        visited[0] = 1;

        int res = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();

            for (auto& idx : faceout[cur]) {
                if (!visited[idx]) {
                    res++;
                    q.push(idx);
                    visited[idx] = 1;
                }
            }

            for (auto &idx : facein[cur]) {
                if (!visited[idx]) {
                    q.push(idx);
                    visited[idx] = 1;
                }
            }
        }

        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)
